#include "cell.h"

#include <QKeyEvent>

Cell::Cell(int row, int col, QWidget *parent)
    : QPushButton(parent)
    , row(row)
    , col(col)
    , mineCount(0)
    , isFlagged(false)
    , isRevealed(false)
    , mineIcon(QPixmap(":/images/Mine.ico"))
    , flagIcon(QPixmap(":/images/Flag.ico"))
{
    setMinimumSize(WIDTH, HEIGHT);
    setStyleSheet(NORMAL);
    //    setMaximumSize(maximumHeight() - 1, maximumWidth() - 1);
    //    connect(square, &QPushButton::pressed, this, &MainWindow::buttonPressed);
}

void Cell::reveal()
{
    setStyleSheet(PRESSED);
    if (mineCount < 0) {
        setIcon(mineIcon);
    } else if (!isEmpty()) {
        setText(QString::number(mineCount));
        setStyleSheet(styleSheet() + "; color: " + COLOR[mineCount]);
    }
    isRevealed = true;
}

void Cell::flag()
{
    if (isFlagged)
        setIcon(QIcon());
    else
        setIcon(flagIcon);
    isFlagged = !isFlagged;
    emit flagged(isFlagged);
}

void Cell::forceFlag()
{
    setIcon(flagIcon);
    isFlagged = true;
}

bool Cell::isMine() const
{
    return mineCount < 0;
}

bool Cell::isEmpty() const
{
    return mineCount == 0 && !isFlagged;
}

void Cell::mousePressEvent(QMouseEvent *e)
{
    switch (e->button()) {
    case Qt::LeftButton:
        if (!isFlagged) {
            emit leftClicked(row, col);
        }
        break;
    case Qt::RightButton:
        if (!isRevealed) {
            emit rightClicked(row, col);
        }
        break;
    default: break;
    }
}
