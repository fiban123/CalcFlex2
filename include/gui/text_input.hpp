#pragma once

#define SFML_STATIC
#include <SFML/Graphics.hpp>

#include <string>
#include <array>

struct TextInput{
    std::string string;
    sf::Text text;
    unsigned character_width;
    size_t cursor_string_index = 0;

    std::array<sf::Vertex, 2> cursor_line_vertices;

    sf::RectangleShape rect;

    void remove(unsigned n, unsigned spacing, unsigned font_size, sf::Color bg_color, sf::Color text_color, sf::Font& font);
    void enter_unicode_char(unsigned c, unsigned spacing, unsigned font_size, sf::Color bg_color, sf::Color text_color, sf::Font &font);
    void enter_text(std::string text, unsigned offset, sf::Color cursor_line_color, unsigned spacing, unsigned font_size, sf::Color bg_color, sf::Color text_color, sf::Font &font);

    void update_text(unsigned font_size, sf::Color bg_color, sf::Color text_color, sf::Font &font, unsigned spacing);
    void update_text_pos(unsigned spacing);
    void update_cursor(sf::Color cursor_line_color, unsigned spacing);

    void draw(sf::RenderWindow& window);

    void resize(sf::Vector2f new_size, unsigned spacing, sf::Color text_color);

    TextInput(std::string start_text, sf::Vector2f pos, sf::Vector2f size, sf::Font& font, unsigned font_size, sf::Color bg_color, sf::Color text_color, unsigned spacing);

    TextInput() = default;
};