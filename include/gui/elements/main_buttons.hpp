#pragma once

#include "button.hpp"
#include "gui_config.hpp"

#include <vector>

inline const std::vector<std::vector<std::string> > main_button_labels = MAIN_BUTTON_LABELS;
inline const std::vector<std::vector<std::string> > main_button_strings = MAIN_BUTTON_STRINGS;
inline const std::vector<std::vector<int> > main_button_offsets = MAIN_BUTTON_OFFSETS;

struct MainButtons{
    std::vector<Button> buttons;
    sf::Vector2u* window_size;
    sf::RenderWindow* window;
    sf::Font* font;

    ButtonStyle button_style;

    void resize_update();

    void update(sf::Vector2i mouse_pos, bool left_click);
    void draw();
    void update_click(sf::Vector2i click_pos);

    MainButtons(sf::Vector2u *_window_size, sf::Font *_font, std::function<void(size_t, size_t)> button_callback, sf::RenderWindow *_window);

    MainButtons() = default;
};

