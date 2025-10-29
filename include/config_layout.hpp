#include "layout_base.hpp"

struct ConfigLayout : LayoutBase {
    void resize_update(sf::Vector2u);

    void text_entered(unsigned c);

    void move_cursor(bool sign);

    void update(sf::Vector2i mouse_pos, bool left_click);

    void draw(sf::RenderWindow& window);

    void update_click(sf::Vector2i mouse_pos);

    void update_scroll(sf::Vector2i mouse_pos, float delta);

    ConfigLayout(sf::Font* _font, sf::Vector2u _window_size, sf::RenderWindow* _window)
        : LayoutBase(_font, _window_size, _window) {}
};
