#pragma once

#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <vector>

enum class YBound { TOP, BOTTOM, CENTER };
enum class XBound { LEFT, RIGHT, CENTER };

struct TextAreaStyle {
    sf::Color text_color;
    sf::Color bg_color;
    sf::Color outline_color;
    float outline_width;
    float spacing;
    float entry_spacing;
    unsigned font_size;
    sf::Font* font;
};

struct TextArea {
    std::string string;
    std::vector<sf::Text> text_lines;
    bool centered;

    TextAreaStyle* style;

    XBound xbound;
    YBound ybound;

    sf::RectangleShape rect;

    void update_text();
    void update_text_pos();

    void draw(sf::RenderWindow& window);

    void resize(sf::Vector2f new_size);

    TextArea(std::string start_text, sf::Vector2f pos, sf::Vector2f size,
             TextAreaStyle* _style, XBound _xbound, YBound _ybound);

    TextArea() = default;
};
