#include "gui.hpp"
#include "evaluate.hpp"
#include "dynamic_number.hpp"

#include <iostream>
#include <gmp.h>
#include <mpfr.h>

#define SFML_STATIC
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main(){

    // math test
    DynamicVector test{"7878", 0};

    std::cout << test.get_str() << std::endl;


    start_gui(evaluate_string);;
}