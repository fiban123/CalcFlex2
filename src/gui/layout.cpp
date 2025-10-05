

#include "layout.hpp";

#include "config.hpp"

#include <iostream>

void callback(std::string s){
    std::cout << s << std::endl;
}

void Layout::init(){
    init_buttons();
    init_expression_input();
}

void Layout::init_expression_input(){
    expression_input = TextInput(
        "hallo", 
        {SPACING, 3 * BUTTON_SIZE + 4 * SPACING},
        {window_size.x -  2 * SPACING, EXPRESSION_INPUT_HEIGHT},
        *font, 
        EXPRESSION_INPUT_FONT_SIZE, 
        EXPRESSION_INPUT_BG_COLOR,
        TEXT_COLOR, 
        SPACING
    );
}

void Layout::init_buttons(){
    button_vec.clear();
    init_main_buttons();
}

void Layout::init_main_buttons(){
    size_t main_button_x = main_buttons[0].size();
    size_t main_button_y = main_buttons.size();

    size_t start_x = window_size.x - main_button_x * (BUTTON_SIZE + SPACING);
    size_t start_y = window_size.y - main_button_y * (BUTTON_SIZE + SPACING);

    for (size_t bx = 0; bx < main_button_x; bx++){
        for (size_t by = 0; by < main_button_y; by++){
            Button b(BUTTON_BG_COLOR, BUTTON_HOVER_OUTLINE_COLOR, BUTTON_PRESS_BG_COLOR, 
                {start_x + bx * (BUTTON_SIZE + SPACING), start_y + by * (BUTTON_SIZE + SPACING)},
                {BUTTON_SIZE, BUTTON_SIZE}, 
                [=]{callback(main_buttons[by][bx]);}, 
                main_buttons[by][bx], 
                font, 
                BUTTON_FONT_SIZE
            );
            button_vec.push_back(b);
        }
    }
}



void Layout::resize_update(sf::Vector2u _window_size){
    window_size = _window_size;
    resize_update_buttons();
    resize_update_expression_input();
}

void Layout::resize_update_buttons(){
    resize_update_main_buttons();
}

void Layout::resize_update_expression_input(){
    expression_input.resize({window_size.x - 2.0f * SPACING, EXPRESSION_INPUT_HEIGHT}, SPACING);
}       

void Layout::resize_update_main_buttons(){
    size_t main_button_x = main_buttons[0].size();
    size_t main_button_y = main_buttons.size();

    size_t start_x = window_size.x - main_button_x * (BUTTON_SIZE + SPACING);
    size_t start_y = window_size.y - main_button_y * (BUTTON_SIZE + SPACING);

    size_t i = 0;

    for (size_t bx = 0; bx < main_button_x; bx++){
        for (size_t by = 0; by < main_button_y; by++){
            button_vec[i].update_pos({start_x + bx * (BUTTON_SIZE + SPACING), start_y + by * (BUTTON_SIZE + SPACING)});
            i++;
        }
    }
}

void Layout::update(sf::Vector2i mouse_pos, bool left_click){
    for (Button& b : button_vec){
        b.update(mouse_pos, left_click, BUTTON_BG_COLOR, BUTTON_PRESS_BG_COLOR);
    }
}

void Layout::draw(sf::RenderWindow& window){
    for (Button& b : button_vec){
        b.draw(window);
    }
    expression_input.draw(window);
}

void Layout::update_click(sf::Vector2i click_pos){
    for (Button& b : button_vec){
        b.update_click({click_pos.x, click_pos.y});
    }
}
