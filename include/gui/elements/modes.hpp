#include "button.hpp"
#include "gui_config.hpp"

struct Modes{
    std::vector<Button> buttons;

    sf::Vector2u* window_size;
    sf::RenderWindow* window;
    sf::Font* font;

    ButtonStyle button_style;

    void resize_update();

    void update(sf::Vector2i mouse_pos, bool left_click);
    void draw();
    void update_click(sf::Vector2i click_pos);

    Modes(sf::Vector2u *_window_size, sf::Font *_font, std::function<void(size_t, size_t)> button_callback, sf::RenderWindow *_window);

    Modes() = default;
};

