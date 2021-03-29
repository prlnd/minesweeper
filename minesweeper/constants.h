#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Central {
inline constexpr auto STYLE {
    "background-color: silver;"
};
}

namespace Counter {
inline constexpr auto WIDTH {48};
inline constexpr auto HEIGHT {32};
inline constexpr auto STYLE {
    "color: red;"
    "background-color: black;"
};
}

namespace Face {
inline constexpr auto WIDTH {32};
inline constexpr auto HEIGHT {32};
inline constexpr auto STYLE {
    "background-color: silver;"
    "border: 2px outset #999;"
    "color: yellow;"
    "font: arial;"
    "font-size: 20px;"
    "font-weight: bold;"
};
}

namespace Square {
inline constexpr auto ROWS {16};
inline constexpr auto COLS {30};
inline constexpr auto WIDTH {16};
inline constexpr auto HEIGHT {16};
inline constexpr auto BG_COLOR {"silver"};
inline constexpr const char *COLOR[] {
    "none",
    "blue",
    "green",
    "red",
    "darkblue",
    "darkred",
    "darkcyan",
    "black",
    "grey"
};
namespace Temp {
inline constexpr auto BOMB {"B"};
inline constexpr auto FLAG {"F"};
}
namespace Style {
inline constexpr auto NORMAL {
    "background-color: silver;"
    "border: 2px outset #999;"
};
inline constexpr auto PRESSED {
    "background-color: silver;"
    "border: 1px inset grey;"
};
}
}

#endif // CONSTANTS_H
