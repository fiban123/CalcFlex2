#pragma once

#define SFML_STATIC
#include <SFML/Graphics.hpp>

struct TextAreaStyle{
    sf::Color text_color;
    sf::Color bg_color;
    float spacing;
    unsigned font_size;
    sf::Font* font;
};

struct TextArea{
    std::string string;
    sf::Text text;

    bool centered;
    
    TextAreaStyle* style;

    sf::RectangleShape rect;

    void update_text();
    void update_text_pos();

    void draw(sf::RenderWindow& window);

    void resize(sf::Vector2f new_size);

    TextArea(std::string start_text, sf::Vector2f pos, sf::Vector2f size, TextAreaStyle *_style, bool _centered);

    TextArea() = default;
};