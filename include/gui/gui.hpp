#pragma once

#include "layout.hpp"

#include <functional>
#include <string>

void start_gui(std::function<Result(std::string)> callback);