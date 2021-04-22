#ifndef CUSTOMLCD_H
#define CUSTOMLCD_H

#include <QLCDNumber>

class CustomLCD : public QLCDNumber
{
public:
    CustomLCD(QWidget *parent = nullptr);

protected:
    static constexpr auto WIDTH {48};
    static constexpr auto HEIGHT {32};
    static constexpr auto STYLE {
        "color: red;"
        "background-color: black;"
    };
};

#endif // CUSTOMLCD_H
