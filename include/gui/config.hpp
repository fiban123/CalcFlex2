#pragma once

#define SFML_STATIC
#include <SFML/Graphics.hpp>

//GUI

// colors
#define DARK_CYAN {7, 31, 37}
#define CYAN {15, 66, 79}
#define SEMI_BRIGHT_CYAN {14, 113, 138}
#define BRIGHT_CYAN {51, 248, 255}
#define BLACK {0, 0, 0}
#define WHITE {255, 255, 255}

#define ELEMENT_BG_COLOR DARK_CYAN
#define HIGHLIGHT_COLOR CYAN
#define DIM_HIGHLIGHT_COLOR SEMI_BRIGHT_CYAN
#define DARK_OUTLINE_HIGHLIGHT_COLOR CYAN
#define OUTLINE_HIGHLIGHT_COLOR BRIGHT_CYAN
#define BG_COLOR BLACK
#define TEXT_COLOR WHITE

// main buttons
#define MAIN_BUTTON_LABELS { \
    {"C", "CE", "<-", "%", "^"}, \
    {"(", ")", "<", ">", "/"}, \
    {"pi", "7", "8", "9", "*"}, \
    {"e", "4", "5", "6", "-"}, \
    {"!", "1", "2", "3", "+"}, \
    {"sqrt", ".", "0", ",", "="} \
}
#define MAIN_BUTTON_STRINGS { \
    {"", "", "", "%", "^"}, \
    {"()", ")", "", "", "/"}, \
    {"pi", "7", "8", "9", "*"}, \
    {"e", "4", "5", "6", "-"}, \
    {"!", "1", "2", "3", "+"}, \
    {"sqrt()", ".", "0", ",", ""} \
}
#define MAIN_BUTTON_OFFSETS { \
    {0, 0, 0, 1, 1}, \
    {1, 1, 1, 1, 1}, \
    {2, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1}, \
    {1, 1, 1, 1, 1}, \
    {5, 1, 1, 1, 0} \
}

#define MAIN_BUTTONS_C_INDEX sf::Vector2u{0, 0}
#define MAIN_BUTTONS_CE_INDEX sf::Vector2u{1, 0}
#define MAIN_BUTTONS_BACKSPACE_INDEX sf::Vector2u{2, 0}
#define MAIN_BUTTONS_EVALUATE_INDEX sf::Vector2u{4, 5}
#define MAIN_BUTTONS_LEFT_INDEX sf::Vector2u{2, 1}
#define MAIN_BUTTONS_RIGHT_INDEX sf::Vector2u{3, 1}

// function buttons
#define FUNCTION_BUTTON_LABELS { \
    {"sqrt", "cbrt", "root", "ln", "log2", "log10", "log", "exp"}, \
    {"sin", "cos", "tan", "csc", "sec"}, \
    {"asin", "acos", "atan", "acsc", "asec"}, \
    {"sinh", "cosh", "tanh", "csch", "sech"}, \
    {"asinhh", "acosh", "atanh", "acsch", "asech"}, \
    {"round", "ceil", "floor"}, \
    {"int.", "sum", "prod"}, \
    {"pi", "e", "phi", "y"}, \
    {"re", "im", "gamma", "fact", "magn", "abs", "conj", "prime", "r", "c", "shutdown now"}, \
}

#define FUNCTION_BUTTON_STRINGS{ \
    {"sqrt()", "cbrt()", "root()", "ln()", "log2()", "log10()", "log()", "exp()"}, \
    {"sin()", "cos()", "tan()", "csc()", "sec()"}, \
    {"asin()", "acos()", "atan()", "acsc()", "asec()"}, \
    {"sinh()", "cosh()", "tanh()", "csch()", "sech()"}, \
    {"asinh()", "acosh()", "atanh()", "acsch()", "asech()"}, \
    {"round()", "ceil()", "floor()"}, \
    {"integrate()", "sum()", "prod()"}, \
    {"pi", "e", "phi", "y"}, \
    {"re()", "im()", "gamma()", "fact()", "magn()", "abs()", "conj()", "prime()", "r()", "c()", ""}, \
}

#define FUNCTION_BUTTON_OFFSETS{ \
    {5, 5, 5, 3, 5, 6, 4, 4}, \
    {4, 4, 4, 4, 4}, \
    {5, 5, 5, 5, 5}, \
    {5, 5, 5, 5, 5}, \
    {6, 6, 6, 6, 6}, \
    {6, 5, 6}, \
    {10, 4, 5}, \
    {2, 1, 3, 1}, \
    {3, 3, 6, 5, 5, 4, 5, 5, 2, 2}, \
}
#define FUNCTION_BUTTON_DIM sf::Vector2f(110.f, 45.f)
#define FUNCTION_BUTTONS_MAX_TOP_OFFSET (EXPRESSION_INPUT_TOP_OFFSET + EXPRESSION_INPUT_HEIGHT + EXPRESSION_INPUT_SPACING)

// function group buttons
#define FUNCTION_GROUP_BUTTON_LABELS { \
    "exp", \
    "trig", \
    "a trig", \
    "h trig", \
    "a h trig", \
    "round", \
    "calculus", \
    "const", \
    "other", \
}

#define FUNCTION_GROUP_BUTTON_STATES { \
    false, \
    false, \
    false, \
    false, \
    false, \
    false, \
    false, \
    false, \
    false, \
}

#define FUNCTION_GROUP_BUTTON_FONT_SIZE 22
#define FUNCTION_GROUP_DELIMIETER_LINE_COLOR ELEMENT_BG_COLOR
#define FUNCTION_GROUP_SPACING 40.f
#define FUNCTION_GROUP_BUTTON_DIM sf::Vector2f(140.f, 56.6666666666666666666f)
#define FUNCTION_GROUP_CHECKED_COLOR DIM_HIGHLIGHT_COLOR

// all elements
#define SPACING 10.f
// buttons
#define BUTTON_OUTLINE_WIDTH 2.f
#define BUTTON_BG_COLOR ELEMENT_BG_COLOR
#define BUTTON_PRESS_BG_COLOR HIGHLIGHT_COLOR
#define BUTTON_HOVER_OUTLINE_COLOR OUTLINE_HIGHLIGHT_COLOR
#define BUTTON_SIZE 90.f
#define BUTTON_FONT_SIZE 30
// expression input
#define EXPRESSION_INPUT_BG_COLOR ELEMENT_BG_COLOR
#define EXPRESSION_INPUT_HEIGHT 45.f
#define EXPRESSION_INPUT_FONT_SIZE 35
#define EXPRESSION_INPUT_SPACING 20.f
#define EXPRESSION_INPUT_TOP_OFFSET (3 * BUTTON_SIZE + 3 * SPACING + EXPRESSION_INPUT_SPACING)


#define FONT "JetBrainsMono-Regular.ttf"

