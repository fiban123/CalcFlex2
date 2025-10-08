#include "history.hpp"

#include "config.hpp"

void History::draw(){
    text_area.draw(*window);
}

void History::resize_update(){
    text_area.resize({window_size->x - text_area_pos_x - SPACING, HISTORY_HEIGHT});
}

void History::add_entry(std::string string){
    text_area.string += "\n" + string;
    text_area.update_text();
}

History::History(sf::RenderWindow *_window, sf::Vector2u *_window_size, sf::Font *_font)
        : window(_window), window_size(_window_size), font(_font){

    text_area_style = TextAreaStyle{
        .text_color = TEXT_COLOR,
        .bg_color = HISTORY_BG_COLOR,
        .spacing = SPACING,
        .font_size = HISTORY_TEXT_FONT_SIZE,
        .font = font
    };

    text_area_pos_x = 2.f * BUTTON_SIZE + 2.f * SPACING + HISTORY_LEFT_SPACING;

    text_area = TextArea(
        "hallo3\nhallo4", 
        {text_area_pos_x, SPACING},
        {window_size->x - text_area_pos_x - SPACING, HISTORY_HEIGHT},
        &text_area_style,
        false
    );
}
