#ifndef CELL_H
#define CELL_H

#include <QPushButton>

class Cell : public QPushButton
{
    Q_OBJECT
public:
    Cell(int row, int col, QWidget *parent = nullptr);
    void reveal();
    void flag();
    void forceFlag();
    bool isMine() const;
    bool isEmpty() const;

    const int row;
    const int col;
    int mineCount;
    bool isFlagged;
    bool isRevealed;
    QIcon mineIcon;
    QIcon flagIcon;

protected:
    static constexpr auto WIDTH {18};
    static constexpr auto HEIGHT {18};
    static constexpr const char *COLOR[] {
        "none", "blue", "green",
        "red", "darkblue", "darkred",
        "darkcyan", "black", "grey"
    };
    static constexpr auto NORMAL {
        "background-color: silver;"
        "border: 2px outset #999;"
        "font-weight: bold;"
        "font-size: 32;"
    };
    static constexpr auto PRESSED {
        "background-color: silver;"
        "border: 1px inset grey;"
        "font-weight: bold;"
        "font-size: 32;"
    };

    void mousePressEvent(QMouseEvent *e) override;
signals:
    void leftClicked(int row, int col);
    void rightClicked(int row, int col);
    void flagged(bool);
};

#endif // CELL_H
