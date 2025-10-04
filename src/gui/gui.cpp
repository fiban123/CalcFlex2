#include "gui.hpp"
#include "button.hpp"
#include "config.hpp"

#define SFML_STATIC
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

void test(){
    std::cout << "sidjsidj\n";
}

void start_gui(std::function<std::string(std::string)> callback){
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");
    Button b1(BUTTON_BG_COLOR, BUTTON_OUTLINE_HOVER_COLOR, {100.0f, 100.0f}, {100.0f, 100.0f}, test);


    while (window.isOpen()){
        sf::Event event;   
    
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(visibleArea));
            }

            else if (event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    b1.update_click({event.mouseButton.x, event.mouseButton.y});
                }
            }
        }

        window.clear();

        sf::Vector2i mouse_pos = sf::Mouse::getPosition();

        std::cout << mouse_pos.x << " " << mouse_pos.y << "\n";

        b1.draw(&window);
        b1.update(mouse_pos);

        window.display();
    }
}