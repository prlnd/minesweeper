#include "lcdtimer.h"

LCDTimer::LCDTimer(QWidget *parent, int nDigits)
    : CustomLCD(parent)
    , m_timer(new QTimer(this))
    , m_nDigits(nDigits)
    , m_maxCount(1)
{
    setDigitCount(nDigits);

    while (nDigits-- > 0)
        m_maxCount *= 10;

    connect(m_timer, &QTimer::timeout, this, &LCDTimer::showElapsedTime);

    clearTimer();
}

void LCDTimer::startTimer()
{
    if (!m_timer->isActive()) {
        showElapsedTime();
        m_timer->start(1000);
    }
}

void LCDTimer::stopTimer()
{
    m_timer->stop();
}

void LCDTimer::clearTimer()
{
    m_timer->stop();
    m_count = -1;
    showElapsedTime();
}

void LCDTimer::showElapsedTime()
{
    if (++m_count < m_maxCount)
        display(QString("%1").arg(m_count, m_nDigits, 10, QLatin1Char('0')));
}
