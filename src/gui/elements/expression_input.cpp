#include "expression_input.hpp"

void ExpressionInput::draw(){
    text_input.draw(*window);
}

void ExpressionInput::resize_update(){
    text_input.resize({window_size->x - 2.0f * SPACING, EXPRESSION_INPUT_HEIGHT});
}

void ExpressionInput::enter_unicode_char(unsigned c){
    text_input.enter_unicode_char(c);
}

void ExpressionInput::enter_text(std::string s, unsigned offset){
    text_input.enter_text(s, offset);
}

void ExpressionInput::clear(){
    text_input.string = "";
    text_input.update_text();
}

void ExpressionInput::clear_entry(){
    //...
}

void ExpressionInput::remove(unsigned n){
    text_input.remove(n);
}

void ExpressionInput::move_cursor(bool sign){
    ssize_t new_pos = sign ? text_input.cursor_string_index + 1 : text_input.cursor_string_index - 1;
    text_input.cursor_string_index = std::clamp(new_pos, 0ll, (ssize_t) text_input.string.length());

    text_input.update_cursor();
}

ExpressionInput::ExpressionInput(sf::RenderWindow *_window, sf::Vector2u *_window_size, sf::Font* _font)
        : window(_window), window_size(_window_size), font(_font){

    text_input_style = TextInputStyle{
        .text_color = TEXT_COLOR,
        .bg_color = EXPRESSION_INPUT_BG_COLOR,
        .cursor_color = TEXT_COLOR,
        .spacing = SPACING,
        .font_size = EXPRESSION_INPUT_FONT_SIZE,
        .font = font
    };

    text_input = TextInput(
        "hallo", 
        {SPACING, 3 * BUTTON_SIZE + 3 * SPACING + EXPRESSION_INPUT_SPACING},
        {window_size->x -  2 * SPACING, EXPRESSION_INPUT_HEIGHT},
        &text_input_style
    );
}
