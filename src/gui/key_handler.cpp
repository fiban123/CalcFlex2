#include "key_handler.hpp"

#include <SFML/Window/Keyboard.hpp>

#include "config_loader.hpp"
#include "config_options.hpp"
#include "layouts.hpp"

void key_press_handler(sf::Keyboard::Scancode code) {
    if (code == sf::Keyboard::Scan::F5) {
        set_layout(Layouts::MAIN);
        layout->enter();
    }

    if (code == sf::Keyboard::Scan::F10) {
        set_layout(Layouts::CONFIG);
        layout->enter();
    }
    else if (code == sf::Keyboard::Scan::F11) {
        write_config(config, "../config.json");
    }

    if (code == sf::Keyboard::Scan::Left) {
        layout->move_cursor(0);
    }
    else if (code == sf::Keyboard::Scan::Right) {
        layout->move_cursor(1);
    }
}
