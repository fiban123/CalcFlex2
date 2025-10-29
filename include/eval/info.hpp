#pragma once

#include <string>

bool is_func(char c);

bool is_valid_boundary(std::string& s, size_t pos, size_t len);

std::string get_info(std::string input, size_t cursor_pos);
