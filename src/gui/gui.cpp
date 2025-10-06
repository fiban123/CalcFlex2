#include "gui.hpp"
#include "button.hpp"
#include "config.hpp"
#include "layout.hpp"

#include <iostream>
#include <vector>

void start_gui(std::function<std::string(std::string)> callback){
    sf::RenderWindow window(sf::VideoMode({1200, 1200}), "CalcFlex2");

    sf::Font font;
    font.loadFromFile(FONT);

    Layout layout(&font, window.getSize(), &window);

    
    while (window.isOpen()){
        sf::Event event;   
    
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                layout.resize_update(window.getSize());
            }

            else if (event.type == sf::Event::MouseButtonReleased){
                if(event.mouseButton.button == sf::Mouse::Left){
                    layout.update_click({event.mouseButton.x, event.mouseButton.y});
                }
            }

            else if (event.type == sf::Event::TextEntered){
                std::cout << event.text.unicode << std::endl;
                layout.text_entered( event.text.unicode);
            }

            else if (event.type == sf::Event::KeyPressed){
                if (event.key.scancode == sf::Keyboard::Scan::Left){
                    layout.move_cursor(0);
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Right){
                    layout.move_cursor(1);
                }
            }
        }

        window.clear();

        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        bool left_click = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        //std::cout << mouse_pos.x << " " << mouse_pos.y << "\n";
        layout.update(mouse_pos, left_click);
        layout.draw(window);

        window.display();
    }
}