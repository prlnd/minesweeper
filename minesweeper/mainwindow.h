#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "lcdtimer.h"

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
    void clear();

private:
    QWidget *m_centralWidget;
    QVBoxLayout *m_vLayout;
    QHBoxLayout *m_headerLayout;
    QGridLayout *m_gridLayout;
    QLCDNumber *m_mineCounter;
    LCDTimer *m_timeCounter;
    QPushButton *m_faceButton;

    void initializeWidgets();
    void resetWidgets();
    void initializeLayouts();
    void addWidgetsToLayouts();
    void createGrid();
    void initializeSquare(QPushButton *square);
    void resetSquare(QPushButton *square);
    void initalizeCentralWidget();

private slots:
    void buttonPressed();
};

#endif // MAINWINDOW_H
