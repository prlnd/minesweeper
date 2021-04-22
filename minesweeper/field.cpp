#include "field.h"

#include <QTextStream>
#include <QDebug>

Field::Field(int row, int col, int mines, QWidget *parent)
    : QGridLayout(parent)
    , rows(row)
    , cols(col)
    , mines(mines)
    , unrevealed(row * col - mines)
    , status(Status::CONTINUES)
{
    setSpacing(0);
    init();
    generateMines();
    connect(this, &Field::over, this, &Field::finish);
}

QString Field::print() const
{
    QString buf;
    QTextStream ts {&buf};
    ts << ' ';
    for (int j = 0; j < cols; ++j) {
        ts << '_' << j;
    }
    ts << '\n';
    for (int i = 0; i < rows; ++i) {
        ts << i << '|';
        for (int j = 0; j < cols; ++j) {
            int count {cellAt(i, j)->mineCount};
            if (count < 0)
                ts << '*' << ' ';
            else
                ts << count << ' ';
        }
        ts << '\n';
    }
    return buf;
}

Cell *Field::cellAt(int row, int col) const
{
    auto widget = itemAtPosition(row, col)->widget();
    return qobject_cast<Cell*>(widget);
}

void Field::init()
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            auto cell {new Cell(i, j)};
            connect(cell, &Cell::leftClicked, this, &Field::reveal);
            connect(cell, &Cell::leftClicked, this, &Field::clicked);
            connect(cell, &Cell::rightClicked, this, &Field::flag);
            connect(cell, &Cell::rightClicked, this, &Field::clicked);
            connect(cell, &Cell::flagged, this, &Field::flagged);
            addWidget(cell, i, j);
        }
    }

//    qDebug().noquote() << print();
}

void Field::generateMines()
{
    std::srand(time(nullptr));

    for (int i = 0; i < mines; ++i) {
        int row, col;
        do {
            row = rand() % rows;
            col = rand() % cols;
        } while (cellAt(row, col)->isMine());
        setMine(row, col);
    }
    qDebug().noquote() << print();
}

void Field::setMine(int row, int col)
{
    for (auto &pos : adj) {
        int i = row + pos.first;
        int j = col + pos.second;
        if (isValid(i, j)) {
            auto cell = cellAt(i, j);
            if (!cell->isMine())
                ++cell->mineCount;
        }
    }
    cellAt(row, col)->mineCount = -1;
}

bool Field::isValid(int row, int col) const
{
    return 0 <= row && row < rows
            && 0 <= col && col < cols;
}

void Field::reveal(int row, int col)
{
    if (status != Status::CONTINUES)
        return;
    auto cell {cellAt(row, col)};
    if (cell->isFlagged)
        return;
    cell->reveal();
    if (--unrevealed == 0) {
        qDebug() << "Win";
        status = Status::WON;
        emit won();
        emit over();
    } else if (cell->isMine()) {
        qDebug() << "Lose";
        status = Status::LOST;
        emit over();
        emit lost();
    } else if (cell->isEmpty()) {
        for (auto &pos : adj) {
            int i = row + pos.first;
            int j = col + pos.second;
            if (isValid(i, j) && !cellAt(i, j)->isRevealed) {
                reveal(i, j);
            }
        }
    }
}

void Field::flag(int row, int col)
{
    if (status == Status::CONTINUES) {
        cellAt(row, col)->flag();
    }
}

void Field::finish()
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            auto cell {cellAt(i, j)};
            if (cell->isMine()) {
                switch (status) {
                case Status::WON:
                    cell->forceFlag();
                    break;
                case Status::LOST:
                    cell->reveal();
                    break;
                default:
                    qDebug() << "Wrong status";
                    break;
                }
            }
        }
    }
}
