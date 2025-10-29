#pragma once

#include <string>
#include <vector>

#include "aux_menu.hpp"
#include "eval_config.hpp"
#include "expression_input.hpp"
#include "func_buttons.hpp"
#include "gui_config.hpp"
#include "history.hpp"
#include "info_bar.hpp"
#include "interface.hpp"
#include "lines.hpp"
#include "main_buttons.hpp"
#include "result_bar.hpp"
#include "text_input.hpp"

struct Layout {
    sf::Font* font;
    sf::Vector2u window_size;
    sf::RenderWindow* window;

    std::pair<std::string, Result> result;

    MainButtons main_buttons;
    FunctionButtons func_buttons;
    ExpressionInput expression_input;
    InfoBar info_bar;
    AuxMenu aux_menu;
    History history;
    Lines lines;
    ResultBar result_bar;

    std::function<Result(std::string)> on_evaluate;

    void evaluate();

    void main_button_callback(size_t bx, size_t by);
    void func_button_callback(std::string string, unsigned offset);

    void resize_update(sf::Vector2u _window_size);

    void text_entered(unsigned c);
    void move_cursor(bool sign);

    void update(sf::Vector2i mouse_pos, bool left_click);
    ;
    void draw(sf::RenderWindow& window);
    void update_click(sf::Vector2i click_pos);
    void update_scroll(sf::Vector2i mouse_pos, float delta);

    void update_result();

    Layout(sf::Font* _font, sf::Vector2u _window_size, sf::RenderWindow* _window,
           std::function<Result(std::string)> _on_evaluate);
};
