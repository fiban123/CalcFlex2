#pragma once

#include "button.hpp"
#include "config.hpp"

inline const std::vector<std::vector<std::string> > aux_menu_button_labels = AUX_MENU_BUTTON_LABELS;


struct AuxMenu{
    std::vector<Button> buttons;

    sf::Vector2u* window_size;
    sf::RenderWindow* window;
    sf::Font* font;

    ButtonStyle button_style;

    void resize_update();

    void update(sf::Vector2i mouse_pos, bool left_click);
    void draw();
    void update_click(sf::Vector2i click_pos);

    AuxMenu(sf::Vector2u *_window_size, sf::Font *_font, std::function<void(size_t, size_t)> button_callback, sf::RenderWindow *_window);

    AuxMenu() = default;
};

