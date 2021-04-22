#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(new QWidget)
    , m_vLayout(new QVBoxLayout)
    , m_headerLayout(new QHBoxLayout)
    , m_grid(new Field)
    , m_mineCounter(new CustomLCD)
    , m_timeCounter(new LCDTimer)
    , m_faceButton(new QPushButton)
    , iconContinues(QPixmap(":/images/Smiley1.ico"))
    , iconWon(QPixmap(":/images/Smiley.ico"))
    , iconLost(QPixmap(":/images/Smiley3.ico"))
{
    initializeWidgets();
    initializeLayouts();
    addWidgetsToLayouts();
    initalizeCentralWidget();
    setCentralWidget(m_centralWidget);
    resize(0, 0);
    connect(m_grid, &Field::over, this, &MainWindow::finish);
    connect(m_grid, &Field::won, this, &MainWindow::win);
    connect(m_grid, &Field::lost, this, &MainWindow::lose);
}

MainWindow::~MainWindow()
{
}

void MainWindow::reset()
{
    // Grid
    m_vLayout->removeItem(m_vLayout->itemAt(1));
    m_grid->deleteLater();
    m_grid = new Field;
    m_vLayout->addLayout(m_grid);
    connect(m_grid, &Field::clicked, this, &MainWindow::buttonPressed);
    connect(m_grid, &Field::flagged, this, &MainWindow::flagged);
    connect(m_grid, &Field::over, this, &MainWindow::finish);

    // Counters
    m_mineCounter->setDigitCount(3);
    m_mineCounter->display(QString("%1").arg(m_grid->mines, 3, 10, QLatin1Char('0'))); // TODO
    m_timeCounter->clearTimer();

    // Face
    m_faceButton->setIcon(iconContinues);
    connect(m_grid, &Field::won, this, &MainWindow::win);
    connect(m_grid, &Field::lost, this, &MainWindow::lose);
}

void MainWindow::initializeWidgets()
{
    // Counters

    // Face button
    m_faceButton->setIcon(iconContinues);
    m_faceButton->setMinimumSize(WIDTH, HEIGHT);
    m_faceButton->setMaximumSize(WIDTH, HEIGHT);
    m_faceButton->setStyleSheet(FACE_STYLE);
    m_mineCounter->setDigitCount(3);
    m_mineCounter->display(QString("%1").arg(m_grid->mines, 3, 10, QLatin1Char('0'))); // TODO
    m_timeCounter->clearTimer();
    connect(m_faceButton, &QPushButton::clicked, this, &MainWindow::reset);
    connect(m_grid, &Field::flagged, this, &MainWindow::flagged);
}

void MainWindow::initializeLayouts()
{
    m_headerLayout->setContentsMargins(5, 0, 5, 0);
    connect(m_grid, &Field::clicked, this, &MainWindow::buttonPressed);
}

void MainWindow::addWidgetsToLayouts()
{
    m_headerLayout->addWidget(m_mineCounter, 0, Qt::AlignLeft);
    m_headerLayout->addWidget(m_faceButton, 0, Qt::AlignCenter);
    m_headerLayout->addWidget(m_timeCounter, 0, Qt::AlignRight);

    m_vLayout->addLayout(m_headerLayout);
    m_vLayout->addLayout(m_grid);
}

void MainWindow::initalizeCentralWidget()
{
    m_centralWidget->setLayout(m_vLayout);
    m_centralWidget->setStyleSheet(CENTRAL_STYLE);
}

void MainWindow::buttonPressed()
{
    m_timeCounter->startTimer();
    disconnect(m_grid, &Field::clicked, this, &MainWindow::buttonPressed);
}

void MainWindow::flagged(bool isFlagged)
{
    int count = m_mineCounter->intValue() + (isFlagged ? -1 : 1);
    m_mineCounter->display(QString("%1").arg(count, 3, 10, QLatin1Char('0')));
}

void MainWindow::finish()
{
    m_timeCounter->stopTimer();
    m_mineCounter->display("000");
}

void MainWindow::win()
{
    m_faceButton->setIcon(iconWon);
}

void MainWindow::lose()
{
    m_faceButton->setIcon(iconLost);
}
