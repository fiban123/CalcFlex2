#include "layout.hpp"

#include "gui_config.hpp"

#include <iostream>

void Layout::main_button_callback(size_t bx, size_t by){
    sf::Vector2u index{bx, by};

    if (index == MAIN_BUTTONS_C_INDEX){
        expression_input.clear();
    }

    else if (index == MAIN_BUTTONS_CE_INDEX){
        expression_input.clear_entry();
    }
    else if (index == MAIN_BUTTONS_BACKSPACE_INDEX){
        expression_input.remove(1);
    }
    else if (index == MAIN_BUTTONS_EVALUATE_INDEX){
        Result eval_result = on_evaluate(expression_input.text_input.string);
        
        result = std::make_pair(expression_input.text_input.string, std::move(eval_result));

        std::string result_str = result.second.get_string();
        std::string history_entry = expression_input.text_input.string + " = " + result_str;
        result_bar.set_string(result_str);
        history.add_entry(history_entry);
    }
    else if (index == MAIN_BUTTONS_LEFT_INDEX){
        expression_input.move_cursor(0);
    }
    else if (index == MAIN_BUTTONS_RIGHT_INDEX){
        expression_input.move_cursor(1);
    }

    else{
        expression_input.enter_text(
        main_button_strings[by][bx], main_button_offsets[by][bx]
       );
    }
}

void Layout::aux_menu_button_callback(size_t bx, size_t by){
    std::cout << "aux button\n";

    sf::Vector2u index = sf::Vector2u(bx, by);

    if (index == sf::Vector2u(1, 1)){
        std::cout << "toggled scientific mode";
        set_scientific_mode(!get_scientific_mode());
        update_result();
    }
}

void Layout::func_button_callback(std::string string, unsigned offset){
    expression_input.enter_text(string, offset);
}

void Layout::resize_update(sf::Vector2u _window_size){
    window_size = _window_size;
    main_buttons.resize_update();
    aux_menu.resize_update();
    func_buttons.resize_update();
    expression_input.resize_update();
    info_bar.resize_update();
    history.resize_update();
    lines.resize_update();
    result_bar.resize_update();
}

void Layout::text_entered(unsigned c){
    if (c == 127){
        expression_input.clear_entry();
    }
    else{
        expression_input.enter_unicode_char(c);
    }
}

void Layout::move_cursor(bool sign){
    expression_input.move_cursor(sign);
}

void Layout::update(sf::Vector2i mouse_pos, bool left_click){
    main_buttons.update(mouse_pos, left_click);
    aux_menu.update(mouse_pos, left_click);
    func_buttons.update(mouse_pos, left_click);
    info_bar.update(mouse_pos, left_click);
}

void Layout::draw(sf::RenderWindow& window){
    func_buttons.draw();
    main_buttons.draw();
    aux_menu.draw();
    expression_input.draw();
    info_bar.draw();
    history.draw();
    lines.draw();
    result_bar.draw();
}

void Layout::update_click(sf::Vector2i click_pos){
    main_buttons.update_click(click_pos);
    aux_menu.update_click(click_pos);
    func_buttons.update_click(click_pos);
    info_bar.update_click(click_pos);
}

void Layout::update_scroll(sf::Vector2i mouse_pos, float delta){
    func_buttons.update_scroll(mouse_pos, delta);
}

void Layout::update_result() {
    std::string result_str = result.second.get_string();
    result_bar.set_string(result_str);
}

Layout::Layout(sf::Font *_font, sf::Vector2u _window_size, sf::RenderWindow *_window, std::function<Result(std::string)> _on_evaluate)
    : font(_font),
      window_size(_window_size),
      window(_window),
      on_evaluate(_on_evaluate),
      main_buttons(&window_size, _font, [this](size_t bx, size_t by){ main_button_callback(bx, by); }, _window),
      func_buttons(_window, &window_size, _font, [this](std::string string, unsigned offset){func_button_callback(string, offset);}),
      aux_menu(&window_size, _font, [this](size_t bx, size_t by){ aux_menu_button_callback(bx, by); }, _window),
      expression_input(_window, &window_size, _font),
      info_bar(_window, &window_size, _font),
      history(_window, &window_size, _font),
      lines(_window, &window_size),
      result_bar(_window, &window_size, _font)
      {}
