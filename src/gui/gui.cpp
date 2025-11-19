#include "gui.hpp"

#include <iostream>
#include <vector>

#include "button.hpp"
#include "config_layout.hpp"
#include "config_loader.hpp"
#include "config_options.hpp"
#include "eval_config.hpp"
#include "evaluator.hpp"
#include "gui_config.hpp"
#include "key_handler.hpp"
#include "layouts.hpp"

void start_gui(std::function<Result(std::string)> callback) {
    read_config("../config.json", eval_config, config);

    sf::RenderWindow window(sf::VideoMode({1200, 1200}), "CalcFlex2");
    window.setVerticalSyncEnabled(true);
    sf::Vector2u min_size = {700, 700};

    sf::Font font;
    font.loadFromFile(FONT);

    make_layouts(&font, window.getSize(), &window, callback);

    set_layout(Layouts::MAIN);
    layout->enter();

    while (window.isOpen()) {
        sf::Event event;

        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        bool left_click =
            sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::Resized) {
                sf::Vector2u new_size = {
                    std::max(event.size.width, min_size.x),
                    std::max(event.size.height, min_size.y)};
                sf::FloatRect visibleArea(
                    0, 0, new_size.x, new_size.y);
                window.setView(sf::View(visibleArea));
                window.setSize(new_size);
                layout->resize_update(window.getSize());
            }

            else if (event.type == sf::Event::MouseWheelScrolled) {
                layout->update_scroll(mouse_pos,
                                      event.mouseWheelScroll.delta);
            }

            else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    layout->update_click(
                        {event.mouseButton.x, event.mouseButton.y});
                }
            }

            else if (event.type == sf::Event::TextEntered) {
                std::cout << event.text.unicode << std::endl;
                layout->text_entered(event.text.unicode);
            }

            else if (event.type == sf::Event::KeyPressed) {
                key_press_handler(event.key.scancode);
            }
        }

        window.clear();

        // std::cout << mouse_pos.x << " " << mouse_pos.y << "\n";
        layout->update(mouse_pos, left_click);
        layout->draw(window);

        window.display();
    }
}
