#include "customlcd.h"

CustomLCD::CustomLCD(QWidget *parent)
    : QLCDNumber(parent)
{
    setStyleSheet(STYLE);
    setPalette(Qt::red);
    setSegmentStyle(QLCDNumber::Flat);
    setMinimumSize(WIDTH, HEIGHT);
    setMaximumSize(maximumWidth() - 1, maximumHeight() - 1);
}
