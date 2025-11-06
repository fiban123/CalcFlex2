#include <string>

#include "eval_config.hpp"

EvalConfig load_config(std::string path);

void save_config(const EvalConfig& config, const std::string path);
