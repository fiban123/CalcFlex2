#pragma once

#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <array>
#include <string>

#include "textarea.hpp"

struct TextInputStyle {
    sf::Color cursor_color;
    TextAreaStyle text_area_style;
};

struct TextInput {
    TextArea text_area;

    unsigned character_width;
    size_t cursor_string_index = 0;
    bool selected = false;

    TextInputStyle* style;

    std::array<sf::Vertex, 2> cursor_line_vertices;

    void remove(unsigned n);
    void enter_unicode_char(unsigned c);
    void enter_text(std::string text, unsigned offset);
    void move_cursor(bool sign);

    void update_text();
    void update_text_pos();
    void update_cursor();

    void draw(sf::RenderWindow& window);

    void resize(sf::Vector2f new_size);

    TextInput(std::string start_text, sf::Vector2f pos, sf::Vector2f size,
              TextInputStyle* _style, bool _selected, XBound _xbound, YBound _ybound);

    TextInput() = default;
};
