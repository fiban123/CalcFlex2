#pragma once

#define SFML_STATIC
#include <SFML/Graphics.hpp>


#include <functional>
#include <string>

void key_press(sf::Event::KeyEvent key);

void start_gui(std::function<std::string(std::string)> callback);