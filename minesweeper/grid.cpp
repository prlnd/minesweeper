#include "grid.h"

#include <QTextStream>
#include <QDebug>

Grid::Grid(QWidget *parent)
    : Grid(9, 9, 10, parent)
{

}

Grid::Grid(int row, int col, int mines, QWidget *parent)
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
    connect(this, &Grid::over, this, &Grid::finish);
}

Grid::~Grid()
{
    QLayoutItem *item;
    while ((item = takeAt(0))) {
        delete item->widget();
        delete item;
    }
}

void Grid::print() const
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
    qDebug().noquote() << buf;
}

Cell *Grid::cellAt(int row, int col) const
{
    auto widget = itemAtPosition(row, col)->widget();
    return qobject_cast<Cell*>(widget);
}

void Grid::init()
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            auto cell {new Cell(i, j)};
            connect(cell, &Cell::leftClicked, this, &Grid::reveal);
            connect(cell, &Cell::leftClicked, this, &Grid::clicked);
            connect(cell, &Cell::rightClicked, this, &Grid::flag);
            connect(cell, &Cell::rightClicked, this, &Grid::clicked);
            connect(cell, &Cell::flagged, this, &Grid::flagged);
            addWidget(cell, i, j);
        }
    }

//    print();
}

void Grid::generateMines()
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
    print();
}

void Grid::setMine(int row, int col)
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

bool Grid::isValid(int row, int col) const
{
    return 0 <= row && row < rows
            && 0 <= col && col < cols;
}

void Grid::reveal(int row, int col)
{
    if (status != Status::CONTINUES)
        return;
    auto cell {cellAt(row, col)};
    if (cell->isFlagged || cell->isRevealed)
        return;
    cell->reveal();
    if (cell->isMine()) {
            qDebug() << "Lose";
            status = Status::LOST;
            emit over();
            emit lost();
    } else if (--unrevealed == 0) {
            qDebug() << "Win";
            status = Status::WON;
            emit won();
            emit over();
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

void Grid::flag(int row, int col)
{
    if (status == Status::CONTINUES) {
        cellAt(row, col)->flag();
    }
}

void Grid::finish()
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
