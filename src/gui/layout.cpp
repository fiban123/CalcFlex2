#include "layout.hpp"

#include "config.hpp"

#include <iostream>



void Layout::button_callback(size_t bx, size_t by){
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
        //...
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


void Layout::resize_update(sf::Vector2u _window_size){
    window_size = _window_size;
    main_buttons.resize_update();
    func_buttons.resize_update();
    expression_input.resize_update();
}

void Layout::text_entered(unsigned c){
    expression_input.enter_unicode_char(c);
}

void Layout::move_cursor(bool sign){
    expression_input.move_cursor(sign);
}

void Layout::update(sf::Vector2i mouse_pos, bool left_click){
    main_buttons.update(mouse_pos, left_click);
    func_buttons.update(mouse_pos, left_click);
}

void Layout::draw(sf::RenderWindow& window){
    main_buttons.draw();
    expression_input.draw();
    func_buttons.draw();
}

void Layout::update_click(sf::Vector2i click_pos){
    main_buttons.update_click(click_pos);
    func_buttons.update_click(click_pos);
}

void Layout::update_scroll(float delta){
    func_buttons.update_scroll(delta);
}

Layout::Layout(sf::Font *_font, sf::Vector2u _window_size, sf::RenderWindow *_window)
    : font(_font),
      window_size(_window_size),
      window(_window),
      main_buttons(&window_size, _font, [this](size_t bx, size_t by){ button_callback(bx, by); }, _window),
      func_buttons(_window, &window_size, _font),
      expression_input(_window, &window_size, _font)
      {}
