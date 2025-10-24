#pragma once

#include "button.hpp"
#include "expanding_button.hpp"
#include "gui_config.hpp"
#include "interface.hpp"

inline const std::vector<std::vector<std::string> > aux_menu_button_labels = AUX_MENU_BUTTON_LABELS;


struct AuxMenu{
    std::optional<ExpandingButton> modes;
    std::optional<ExpandingButton>  menu;
    Button clear_btn;
    Button config_btn;

    sf::Vector2u* window_size;
    sf::RenderWindow* window;
    sf::Font* font;

    ButtonStyle button_style;
    CheckboxStyle checkbox_style;

    std::function<void()> result_update_callback;

    std::vector<std::vector<std::string> > modes_checkbox_labels = {
        {
            "sci",
            "normal"
        },
        {
            "float",
            "exact"
        }
    };
    std::vector<std::vector<bool> > modes_checkbox_initial_states = {
        {
            get_scientific_mode(),
            !get_scientific_mode()
        },
        {
            get_float_mode(),
            !get_float_mode()
        }
    };
    std::vector<std::vector<bool*> > modes_checkbox_states;

    std::vector<std::vector<bool> > menu_checkbox_initial_states = {};
    std::vector<std::vector<std::string> > menu_checkbox_labels = {};
    std::vector<std::vector<bool*> > menu_checkbox_states;


    void clear_callback();
    void config_callback();

    void menu_callback(size_t x, size_t y);
    void mode_callback(size_t, size_t y);

    void resize_update();

    void update(sf::Vector2i mouse_pos, bool left_click);
    void draw();
    void update_click(sf::Vector2i click_pos);

    AuxMenu(sf::Vector2u *_window_size, sf::Font *_font, sf::RenderWindow *_window, std::function<void()> _result_update_callback);

    AuxMenu() = default;
};