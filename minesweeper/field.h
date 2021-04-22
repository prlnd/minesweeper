#ifndef FIELD_H
#define FIELD_H

#include "cell.h"

#include <QGridLayout>

class Field : public QGridLayout
{
    Q_OBJECT
public:
    Field(int row = 9, int col = 9, int mines = 10, QWidget *parent = nullptr);
    QString print() const;
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

#endif // FIELD_H
