#include "gui.hpp"

#define SFML_STATIC
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <optional>

void start_gui(std::function<std::string(std::string)> callback){
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");

        while (window.isOpen()){
            sf::Event event;   
        
            while (window.pollEvent(event))
            {
                // Close window: exit
                if (event.type == sf::Event::Closed)
                    window.close();
            }
    
            // Clear screen
            window.clear();
    
            // Update the window
            window.display();
    }
}