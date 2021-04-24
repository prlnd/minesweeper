#ifndef GRID_H
#define GRID_H

#include "cell.h"

#include <QGridLayout>

class Grid : public QGridLayout
{
    Q_OBJECT
public:
    Grid(QWidget *parent = nullptr);
    Grid(int row, int col, int mines, QWidget *parent = nullptr);
    ~Grid();
    void print() const;
    Cell *cellAt(int row, int col) const;

    const int rows;
    const int cols;
    const int mines;

protected:
    enum class Status {
        CONTINUES, WON, LOST
    };

private:
    void init();
    void generateMines();
    void setMine(int row, int col);
    bool isValid(int row, int col) const;

    int unrevealed;
    Status status;
    const QPair<int, int> adj[8] {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

private slots:
    void reveal(int row, int col);
    void flag(int row, int col);
    void finish();

signals:
    void won();
    void lost();
    void over();
    void clicked();
    void flagged(bool);
};

#endif // GRID_H
