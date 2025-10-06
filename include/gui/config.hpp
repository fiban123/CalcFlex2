#pragma once

#define SFML_STATIC
#include <SFML/Graphics.hpp>

//GUI

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

// colors
#define DARK_CYAN {7, 31, 37}
#define CYAN {9, 77, 94}
#define BRIGHT_CYAN {51, 248, 255}
#define BLACK {0, 0, 0}
#define WHITE {255, 255, 255}

#define ELEMENT_BG_COLOR DARK_CYAN
#define HIGHLIGHT_COLOR CYAN
#define OUTLINE_HIGHLIGHT_COLOR BRIGHT_CYAN
#define BG_COLOR BLACK
#define TEXT_COLOR WHITE

// all elements
#define SPACING 10.f
// buttons
#define BUTTON_OUTLINE_WIDTH 2.f
#define BUTTON_BG_COLOR ELEMENT_BG_COLOR
#define BUTTON_PRESS_BG_COLOR HIGHLIGHT_COLOR
#define BUTTON_HOVER_OUTLINE_COLOR OUTLINE_HIGHLIGHT_COLOR
#define BUTTON_SIZE 90.f
#define BUTTON_FONT_SIZE 30.f
// expression input
#define EXPRESSION_INPUT_BG_COLOR ELEMENT_BG_COLOR
#define EXPRESSION_INPUT_HEIGHT 45.f
#define EXPRESSION_INPUT_FONT_SIZE 35.f


#define FONT "JetBrainsMono-Regular.ttf"

