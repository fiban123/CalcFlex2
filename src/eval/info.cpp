#include "info.hpp"

#include "functions.hpp"

// checks if a char can be part of a primitive.
// so anything except digits, numbers and underscores returns false
bool is_func(char c) { return std::isalnum(static_cast<unsigned char>(c)) || c == '_'; }

// checks if a primitives boundary is not another primitive. this prevents collisions
bool is_valid_boundary(std::string& s, size_t pos, size_t len) {
    bool left_ok = (pos == 0 || !is_func(s[pos - 1]));
    bool right_ok = (pos + len >= s.length() || !is_func(s[pos + len]));
    return left_ok && right_ok;
}

// find the rightmost (nearest) primitive to the left of the cursor
std::string get_info(std::string input, size_t cursor_pos) {
    size_t i = 0;  // primitive pos
    MathPrimitive nearest_primitive;
    bool found = false;

    for (size_t j = 0; j < MATH_PRIMITIVE_STRINGS.size(); j++) {
        MathPrimitive primitive = static_cast<MathPrimitive>(j);  // convert index -> primitive

        // get primitive string
        const std::string& func_str = MATH_PRIMITIVE_STRINGS[j];

        // find rightmost occurence of primitive using rfind
        size_t func_i = input.rfind(func_str, cursor_pos + 1);

        // check if current primitive pos is more right than primitive pos
        // and if it has a valid boundary
        if (func_i >= i && func_i != std::string::npos && is_valid_boundary(input, func_i, func_str.length())) {
            // if so, update the primitive and primitive index
            i = func_i;
            nearest_primitive = primitive;
            found = true;
        }
    }

    // return the primitive info if it was found, otherwise nothing
    if (found) {
        return MATH_PRIMITVE_INFOS[static_cast<size_t>(nearest_primitive)];
    }
    return "";
}
