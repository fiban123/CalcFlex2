#include "gui.hpp"
#include "evaluate.hpp"

#include <iostream>
#include <gmp.h>

#define SFML_STATIC
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main(){

    mpz_t a, result;
    mpz_init(a);
    mpz_init(result);

    mpz_set_str(a, "3248972349872349872384723984723984723847384738473847347", 10);

    mpz_mul(result, a, a);
    mpz_mul(result, result, result);

    char* out = mpz_get_str(NULL, 10, result);

    std::cout << out << std::endl;

    free(out);

    mpz_clear(a);
    mpz_clear(result);

    start_gui(evaluate_string);

}