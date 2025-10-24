#include "aux_menu.hpp"

void AuxMenu::clear_callback() {}

void AuxMenu::config_callback() {}

void AuxMenu::menu_callback(size_t x, size_t y) {}

void AuxMenu::mode_callback(size_t x, size_t y) {
    if (*modes_checkbox_states[0][0] && *modes_checkbox_states[0][1]){
        if (x == 0 && y == 0){
            *modes_checkbox_states[0][1] = false;
        }
        else{
            *modes_checkbox_states[0][0] = false; 
        }
    }
    if (*modes_checkbox_states[1][0] && *modes_checkbox_states[1][1]){
        if (x == 0 && y == 1){
            *modes_checkbox_states[1][1] = false;
        }
        else{
            *modes_checkbox_states[1][0] = false; 
        }
    }

    set_scientific_mode(*modes_checkbox_states[0][0]);
    set_float_mode(*modes_checkbox_states[1][0]);;

    result_update_callback();
}


void AuxMenu::resize_update() {}

void AuxMenu::update(sf::Vector2i mouse_pos, bool left_click){
    modes->update(mouse_pos, left_click);
    menu->update(mouse_pos, left_click);
    clear_btn.update(mouse_pos, left_click);
    config_btn.update(mouse_pos, left_click);
}

void AuxMenu::draw(){
    modes->draw(*window);
    menu->draw(*window);
    clear_btn.draw(*window);
    config_btn.draw(*window);
}

void AuxMenu::update_click(sf::Vector2i click_pos){
    modes->update_click(click_pos);
    menu->update_click(click_pos);
    clear_btn.update_click(click_pos);
    config_btn.update_click(click_pos);
}

AuxMenu::AuxMenu(sf::Vector2u *_window_size, sf::Font *_font, sf::RenderWindow *_window, std::function<void()> _result_update_callback)
        : window_size(_window_size), font(_font), window(_window), result_update_callback(_result_update_callback){

    button_style = ButtonStyle{
        .bg_color = BUTTON_BG_COLOR,
        .hover_border_color = BUTTON_HOVER_OUTLINE_COLOR,
        .press_bg_color = BUTTON_PRESS_BG_COLOR,
        .font = font,
        .font_size = AUX_MENU_BUTTON_FONT_SIZE
    };

    checkbox_style = CheckboxStyle{
        .bg_color = BUTTON_BG_COLOR,
        .hover_border_color = BUTTON_HOVER_OUTLINE_COLOR,
        .press_bg_color = BUTTON_PRESS_BG_COLOR,
        .checked_border_color = DIM_HIGHLIGHT_COLOR,
        .unchecked_border_color = OUTLINE_CONTRAST,
        .font = font,
        .font_size = AUX_MENU_BUTTON_FONT_SIZE
    };

    clear_btn = Button(
        {SPACING, SPACING}, {BUTTON_SIZE, BUTTON_SIZE},
        [this]{clear_callback();}, aux_menu_button_labels[0][0], &button_style
    );

    config_btn = Button(
        {SPACING, 2 * SPACING + BUTTON_SIZE}, {BUTTON_SIZE, BUTTON_SIZE},
        [this]{config_callback();}, aux_menu_button_labels[1][0], &button_style
    );

    menu.emplace(
        sf::Vector2f{2 * SPACING + BUTTON_SIZE, SPACING}, sf::Vector2f{BUTTON_SIZE, BUTTON_SIZE},
        [this](size_t x, size_t y){menu_callback(x, y);}, aux_menu_button_labels[0][1], &checkbox_style,
        &menu_checkbox_labels, menu_checkbox_initial_states, &menu_checkbox_states
    );


    modes.emplace(
        sf::Vector2f{2 * SPACING + BUTTON_SIZE, 2 * SPACING + BUTTON_SIZE}, sf::Vector2f{BUTTON_SIZE, BUTTON_SIZE},
        [this](size_t x, size_t y){mode_callback(x, y);}, aux_menu_button_labels[1][1], &checkbox_style,
        &modes_checkbox_labels, modes_checkbox_initial_states, &modes_checkbox_states
    );
}
