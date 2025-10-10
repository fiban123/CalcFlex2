#include "gui.hpp"
#include "button.hpp"
#include "gui_config.hpp"
#include "layout.hpp"

#include <iostream>
#include <vector>

void start_gui(std::function<std::string(std::string)> callback){
    sf::RenderWindow window(sf::VideoMode({1200, 1200}), "CalcFlex2");
    sf::Vector2u min_size = {700, 700};

    sf::Font font;
    font.loadFromFile(FONT);

    Layout layout(
        &font, 
        window.getSize(), 
        &window, 
        callback
    );

    
    while (window.isOpen()){
        sf::Event event;   

        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        bool left_click = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::Resized) {
                sf::Vector2u new_size = {
                    std::max(event.size.width, min_size.x), 
                    std::max(event.size.height, min_size.y)
                };
                sf::FloatRect visibleArea(0, 0, new_size.x, new_size.y);
                window.setView(sf::View(visibleArea));
                window.setSize(new_size);
                layout.resize_update(window.getSize());
            }

            else if (event.type == sf::Event::MouseWheelScrolled){
                layout.update_scroll(mouse_pos, event.mouseWheelScroll.delta);
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

        //std::cout << mouse_pos.x << " " << mouse_pos.y << "\n";
        layout.update(mouse_pos, left_click);
        layout.draw(window);

        window.display();
    }
}