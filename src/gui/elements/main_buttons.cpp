#include "main_buttons.hpp"

#include <functional>
#include <iostream>

void MainButtons::resize_update(){
    size_t main_button_x = main_button_labels[0].size();
    size_t main_button_y = main_button_labels.size();

    size_t start_x = window_size->x - main_button_x * (BUTTON_SIZE + SPACING);
    size_t start_y = window_size->y - main_button_y * (BUTTON_SIZE + SPACING);

    size_t i = 0;

    for (size_t bx = 0; bx < main_button_x; bx++){
        for (size_t by = 0; by < main_button_y; by++){
            buttons[i].update_pos({start_x + bx * (BUTTON_SIZE + SPACING), start_y + by * (BUTTON_SIZE + SPACING)});
            i++;
        }
    }
}

void MainButtons::update(sf::Vector2i mouse_pos, bool left_click){
    for (Button& b : buttons){
        b.update(mouse_pos, left_click);
    }
}

void MainButtons::draw(){
    for (Button& b : buttons){
        b.draw(*window);
    }
}

void MainButtons::update_click(sf::Vector2i click_pos){
    for (Button& b : buttons){
        b.update_click(click_pos);
    }
}
MainButtons::MainButtons(sf::Vector2u *_window_size, sf::Font *_font, std::function<void(size_t, size_t)> button_callback, sf::RenderWindow *_window)
    : window_size(_window_size), font(_font), window(_window)
{

    button_style = ButtonStyle{
        .bg_color = BUTTON_BG_COLOR,
        .hover_border_color = BUTTON_HOVER_OUTLINE_COLOR,
        .press_bg_color = BUTTON_PRESS_BG_COLOR,
        .font = font,
        .font_size = BUTTON_FONT_SIZE
    };


    size_t main_button_x = main_button_labels[0].size();
    size_t main_button_y = main_button_labels.size();

    size_t start_x = window_size->x - main_button_x * (BUTTON_SIZE + SPACING);
    size_t start_y = window_size->y - main_button_y * (BUTTON_SIZE + SPACING);

    for (size_t bx = 0; bx < main_button_x; bx++){
        for (size_t by = 0; by < main_button_y; by++){
            Button b(
                {start_x + bx * (BUTTON_SIZE + SPACING), start_y + by * (BUTTON_SIZE + SPACING)},
                {BUTTON_SIZE, BUTTON_SIZE},
                [button_callback, bx, by]{button_callback(bx, by);},
                main_button_labels[by][bx],
                &button_style
            );
            buttons.push_back(b);
        }
    }
}
