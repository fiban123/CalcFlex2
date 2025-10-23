#include "modes.hpp"

void Modes::resize_update() {}

void Modes::update(sf::Vector2i mouse_pos, bool left_click) {}

void Modes::draw() {}

void Modes::update_click(sf::Vector2i click_pos) {}

Modes::Modes(sf::Vector2u *_window_size, sf::Font *_font, std::function<void(size_t, size_t)> button_callback, sf::RenderWindow *_window)
        : window_size(_window_size), font(_font), window(_window){
}
