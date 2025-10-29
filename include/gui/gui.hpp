#pragma once

#include <functional>
#include <string>

#include "main_layout.hpp"

void start_gui(std::function<Result(std::string)> callback);
