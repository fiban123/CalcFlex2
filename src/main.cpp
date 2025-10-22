#include "gui.hpp"
#include "evaluator.hpp"
#include "dynamic_vec.hpp"
#include "dynamic_vec_math.hpp"

#include <iostream>
#include <gmp.h>
#include <mpfr.h>

#define SFML_STATIC
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main(){
    int 💣 = 23;
    💣+= 1000;
    std::cout << 💣 << "\n";
    std::cout << "💣" << std::endl;

    start_gui(evaluate_string);
}