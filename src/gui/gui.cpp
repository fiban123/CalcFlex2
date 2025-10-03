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
        }

        if (event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(visibleArea));
        }

        window.clear();

        b1.draw(&window);
        b1.update(&window);

        window.display();
    }
}