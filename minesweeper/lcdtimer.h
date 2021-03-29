#ifndef LCDTIMER_H
#define LCDTIMER_H

#include <QLCDNumber>
#include <QTimer>

class LCDTimer : public QLCDNumber
{
    Q_OBJECT

public:
    LCDTimer(QWidget *parent = nullptr, int nDigits = 3);

public slots:
    void startTimer();
    void stopTimer();
    void clearTimer();

private:
    QTimer *m_timer;
    int m_nDigits;
    int m_count;
    int m_maxCount;

    void displayElapsedTime();

private slots:
    void showElapsedTime();
};

#endif // LCDTIMER_H
