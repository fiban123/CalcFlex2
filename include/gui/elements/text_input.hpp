#pragma once

#define SFML_STATIC
#include <SFML/Graphics.hpp>

#include <string>
#include <array>

struct TextInputStyle{
    sf::Color text_color;
    sf::Color bg_color;
    sf::Color cursor_color;
    float spacing;
    unsigned font_size;
    sf::Font* font;
};

struct TextInput{
    std::string string;
    sf::Text text;
    unsigned character_width;
    size_t cursor_string_index = 0;
    
    TextInputStyle* style;

    std::array<sf::Vertex, 2> cursor_line_vertices;

    sf::RectangleShape rect;

    void remove(unsigned n);
    void enter_unicode_char(unsigned c);
    void enter_text(std::string text, unsigned offset);

    void update_text();
    void update_text_pos();
    void update_cursor();

    void draw(sf::RenderWindow& window);

    void resize(sf::Vector2f new_size);

    TextInput(std::string start_text, sf::Vector2f pos, sf::Vector2f size, TextInputStyle* _style);

    TextInput() = default;
};