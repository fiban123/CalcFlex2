#pragma once

#define SFML_STATIC
#include <SFML/Graphics.hpp>

struct LayoutBase {
    sf::Font* font;
    sf::Vector2u window_size;
    sf::RenderWindow* window;

    virtual void enter() = 0;
    virtual void resize_update(sf::Vector2u) = 0;
    virtual void text_entered(unsigned c) = 0;
    virtual void move_cursor(bool sign) = 0;
    virtual void update(sf::Vector2i mouse_pos, bool left_click) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update_click(sf::Vector2i click_pos) = 0;
    virtual void update_scroll(sf::Vector2i mouse_pos,
                               float delta) = 0;

    LayoutBase(sf::Font* _font,
               sf::Vector2u _window_size,
               sf::RenderWindow* _window)
        : font(_font), window_size(_window_size), window(_window) {}

    virtual ~LayoutBase() = default;
};
