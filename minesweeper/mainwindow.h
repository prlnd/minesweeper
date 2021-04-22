#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "lcdtimer.h"
//#include "grid.h"
#include "field.h"

#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void reset();

private:
    QWidget *m_centralWidget;
    QVBoxLayout *m_vLayout;
    QHBoxLayout *m_headerLayout;
    Field *m_grid;
    CustomLCD *m_mineCounter;
    LCDTimer *m_timeCounter;
    QPushButton *m_faceButton;
    QIcon iconContinues;
    QIcon iconWon;
    QIcon iconLost;

    void initializeWidgets();
    void initializeLayouts();
    void addWidgetsToLayouts();
    void initalizeCentralWidget();

    inline static constexpr auto WIDTH {32};
    inline static constexpr auto HEIGHT {32};
    inline static constexpr auto FACE_STYLE {
        "background-color: silver;"
        "border: 2px outset #999;"
        "color: yellow;"
        "font: arial;"
        "font-size: 20px;"
        "font-weight: bold;"
    };

    inline static constexpr auto CENTRAL_STYLE {
        "background-color: silver;"
    };

private slots:
    void buttonPressed();
    void flagged(bool isFlagged);
    void finish();
    void win();
    void lose();
};

#endif // MAINWINDOW_H
