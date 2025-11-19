#include <string>

#include "config_options.hpp"
#include "eval_config.hpp"

void print_config(EvalConfig& config);

void read_config(std::string path,
                 EvalConfig& eval_config,
                 Config& main_config);
void write_config(const Config& config, const std::string path);
