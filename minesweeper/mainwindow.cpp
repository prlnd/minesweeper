#include "mainwindow.h"
#include "constants.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(new QWidget)
    , m_vLayout(new QVBoxLayout)
    , m_headerLayout(new QHBoxLayout)
    , m_gridLayout(new QGridLayout)
    , m_mineCounter(new QLCDNumber)
    , m_timeCounter(new LCDTimer)
    , m_faceButton(new QPushButton(":)"))
{
    initializeWidgets();
    initializeLayouts();
    addWidgetsToLayouts();
    createGrid();
    initalizeCentralWidget();
    setCentralWidget(m_centralWidget);
    resize(0, 0);
}

MainWindow::~MainWindow()
{
}

void MainWindow::clear()
{
    int n {m_gridLayout->count()};
    for (int i {0}; i < n; ++i) {
        auto item = m_gridLayout->itemAt(i)->widget();
        if (item) {
            auto square = qobject_cast<QPushButton*>(item);
            resetSquare(square);
        }
    }
    resetWidgets();
}

void MainWindow::initializeWidgets()
{
    // Counters
    m_mineCounter->setStyleSheet(Counter::STYLE);
    m_timeCounter->setStyleSheet(Counter::STYLE);
    m_mineCounter->setPalette(Qt::red);
    m_timeCounter->setPalette(Qt::red);
    m_mineCounter->setSegmentStyle(QLCDNumber::Flat);
    m_timeCounter->setSegmentStyle(QLCDNumber::Flat);
    m_mineCounter->setMinimumSize(Counter::WIDTH, Counter::HEIGHT);
    m_timeCounter->setMinimumSize(Counter::WIDTH, Counter::HEIGHT);
    m_mineCounter->setMaximumSize(Counter::WIDTH, Counter::HEIGHT);
    m_timeCounter->setMaximumSize(Counter::WIDTH, Counter::HEIGHT);

    // Face button
    m_faceButton->setMinimumSize(Face::WIDTH, Face::HEIGHT);
    m_faceButton->setMaximumSize(Face::WIDTH, Face::HEIGHT);
    m_faceButton->setStyleSheet(Face::STYLE);
    connect(m_faceButton, &QPushButton::clicked, this, &MainWindow::clear);

    resetWidgets();
}

void MainWindow::resetWidgets()
{
    // Counters
    m_mineCounter->setDigitCount(3);
    m_mineCounter->display("099"); // TODO
    m_timeCounter->clearTimer();
}

void MainWindow::initializeLayouts()
{
    m_headerLayout->setContentsMargins(5, 0, 5, 0);
    m_gridLayout->setSpacing(0);
}

void MainWindow::addWidgetsToLayouts()
{
    m_headerLayout->addWidget(m_mineCounter, 0, Qt::AlignLeft);
    m_headerLayout->addWidget(m_faceButton, 0, Qt::AlignCenter);
    m_headerLayout->addWidget(m_timeCounter, 0, Qt::AlignRight);

    m_vLayout->addLayout(m_headerLayout);
    m_vLayout->addLayout(m_gridLayout);
}

void MainWindow::createGrid()
{
    for (int i {0}; i < Square::ROWS; ++i) {
        for (int j {0}; j < Square::COLS; ++j) {
            auto square = new QPushButton;
            initializeSquare(square);
            m_gridLayout->addWidget(square, i, j);
        }
    }
}

void MainWindow::initializeSquare(QPushButton *square)
{
    square->setMinimumSize(Square::WIDTH, Square::HEIGHT);
    square->setMaximumSize(square->maximumHeight() - 1, square->maximumWidth() - 1);
    connect(square, &QPushButton::pressed, this, &MainWindow::buttonPressed);

    resetSquare(square);
}

void MainWindow::resetSquare(QPushButton *square)
{
    square->setStyleSheet(Square::Style::NORMAL);
}

void MainWindow::initalizeCentralWidget()
{
    m_centralWidget->setLayout(m_vLayout);
    m_centralWidget->setStyleSheet(Central::STYLE);
}

void MainWindow::buttonPressed()
{
    auto square = qobject_cast<QPushButton*>(sender());
    square->setStyleSheet(Square::Style::PRESSED);
    m_timeCounter->startTimer();
    int count = m_mineCounter->intValue() - 1;
    m_mineCounter->display(QString("%1").arg(count, 3, 10, QLatin1Char('0')));
}
