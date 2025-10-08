#include "history.hpp"

#include "gui_config.hpp"

void History::draw(){
    text_area.draw(*window);
}

void History::resize_update(){
    text_area.resize({window_size->x - text_area_pos_x - SPACING, HISTORY_HEIGHT});
}

void History::add_entry(std::string string){
    text_area.string.insert(0, string + "\n");
    text_area.update_text();
}

History::History(sf::RenderWindow *_window, sf::Vector2u *_window_size, sf::Font *_font)
        : window(_window), window_size(_window_size), font(_font){

    text_area_style = TextAreaStyle{
        .text_color = TEXT_COLOR,
        .bg_color = HISTORY_BG_COLOR,
        .spacing = SPACING,
        .entry_spacing = HISTORY_ENTRY_SPACING,
        .font_size = HISTORY_TEXT_FONT_SIZE,
        .font = font
    };

    text_area_pos_x = 2.f * BUTTON_SIZE + 2.f * SPACING + HISTORY_LEFT_SPACING;

    text_area = TextArea(
        "", 
        {text_area_pos_x, HISTORY_TOP_OFFSET},
        {window_size->x - text_area_pos_x - SPACING, HISTORY_HEIGHT},
        &text_area_style,
        false
    );
}
