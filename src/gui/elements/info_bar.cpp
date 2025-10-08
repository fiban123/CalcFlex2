#include "info_bar.hpp"

#include "gui_config.hpp"

#include <iostream>

void InfoBar::info_button_callback(){
    std::cout << "info button pressed\n";
}

void InfoBar::draw()
{
    info_button.draw(*window);
    text_area.draw(*window);
}

void InfoBar::update(sf::Vector2i mouse_pos, bool left_click){
    info_button.update(mouse_pos, left_click);
}

void InfoBar::update_click(sf::Vector2i click_pos){
    info_button.update_click(click_pos);
}

void InfoBar::resize_update(){
    text_area.resize({window_size->x - SPACING - INFO_BAR_RIGHT_OFFSET, EXPRESSION_INPUT_HEIGHT});
    info_button.update_pos({2 * SPACING + text_area.rect.getSize().x, INFO_BAR_TOP_OFFSET});
}

void InfoBar::set_string(std::string string){
    text_area.string = string;
    text_area.update_text();
}

InfoBar::InfoBar(sf::RenderWindow *_window, sf::Vector2u *_window_size, sf::Font* _font)
        : window(_window), window_size(_window_size), font(_font){
    text_area_style = TextAreaStyle{
        .text_color = INFO_BAR_TEXT_COLOR,
        .bg_color = INFO_BAR_BG_COLOR,
        .spacing = SPACING,
        .entry_spacing = 0,
        .font_size = INFO_BAR_FONT_SIZE,
        .font = font
    };

    info_button_style = ButtonStyle{
        .bg_color = BUTTON_BG_COLOR,
        .hover_border_color = BUTTON_HOVER_OUTLINE_COLOR,
        .press_bg_color = BUTTON_PRESS_BG_COLOR,
        .font = font,
        .font_size = INFO_BUTTON_FONT_SIZE
    };

    text_area = TextArea(
        "", 
        {SPACING, INFO_BAR_TOP_OFFSET},
        {window_size->x - SPACING - INFO_BAR_RIGHT_OFFSET, EXPRESSION_INPUT_HEIGHT},
        &text_area_style,
        true
    );


    info_button = Button(
        {2 * SPACING + text_area.rect.getSize().x, INFO_BAR_TOP_OFFSET},
        {INFO_BUTTON_SIZE, INFO_BUTTON_SIZE},
        [this]{info_button_callback();},
        INFO_BUTTON_LABEL,
        &info_button_style
    );
}