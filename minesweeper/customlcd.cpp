#include "customlcd.h"

CustomLCD::CustomLCD(QWidget *parent)
    : QLCDNumber(parent)
{
    setStyleSheet(STYLE);
    setPalette(Qt::red);
    setSegmentStyle(QLCDNumber::Flat);
    setMinimumSize(WIDTH, HEIGHT);
    setMaximumSize(WIDTH, HEIGHT);
}
