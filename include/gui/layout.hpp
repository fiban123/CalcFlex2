#pragma once

#include "text_input.hpp"
#include "main_buttons.hpp"
#include "func_buttons.hpp"
#include "expression_input.hpp"
#include "aux_menu.hpp"
#include "gui_config.hpp"
#include "info_bar.hpp"
#include "history.hpp"
#include "lines.hpp"
#include "result_bar.hpp"

#include <vector>
#include <string>


struct Layout{
    sf::Font* font;
    sf::Vector2u window_size;
    sf::RenderWindow* window;

    MainButtons main_buttons;
    FunctionButtons func_buttons;
    ExpressionInput expression_input;
    InfoBar info_bar;
    AuxMenu aux_menu;
    History history;
    Lines lines;
    ResultBar result_bar;

    std::function<std::string(std::string)> on_evaluate;

    void main_button_callback(size_t bx, size_t by);
    void aux_menu_button_callback(size_t bx, size_t by);
    void func_button_callback(std::string string, unsigned offset);

    void resize_update(sf::Vector2u _window_size);

    void text_entered(unsigned c);
    void move_cursor(bool sign);

    void update(sf::Vector2i mouse_pos, bool left_click);;
    void draw(sf::RenderWindow& window);
    void update_click(sf::Vector2i click_pos);
    void update_scroll(sf::Vector2i mouse_pos, float delta);

    Layout(sf::Font* _font, sf::Vector2u _window_size, sf::RenderWindow* _window, std::function<std::string(std::string)> _on_evaluate);
};