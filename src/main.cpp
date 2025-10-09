#include "gui.hpp"
#include "evaluate.hpp"
#include "dynamic_vec.hpp"
#include "dynamic_vec_math.hpp"

#include <iostream>
#include <gmp.h>
#include <mpfr.h>

#define SFML_STATIC
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main(){

    // math test
    DynamicVec test1("1.0", 0);


    start_gui(evaluate_string);;
}