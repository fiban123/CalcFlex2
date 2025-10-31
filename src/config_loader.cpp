#include "config_loader.hpp"

#include <format>
#include <fstream>
#include <nlohmann/json.hpp>

#include "eval_config.hpp"

void print_config(EvalConfig& config) {
    std::cout << "representation_type: " << config.out_representation_type
              << "\nrepresentation_format: " << config.out_representation_format
              << "\nsci_representation_n_digits: " << config.sci_representation_n_digits
              << "\nauto_sci_threshold_n_digits: " << config.auto_sci_threshold_n_digits
              << "\nsci_min_n_digits: " << config.sci_min_n_digits << "\nauto_sci: " << config.auto_sci
              << "\nmath_prec: " << config.math_prec << "\nout_prec: " << config.out_prec;
}

EvalConfig load_config(std::string path) {
    EvalConfig config;

    std::ifstream file(path);
    ;

    if (!file.is_open()) {
        std::cout << std::format("file {} not found\n", path);
        return config;
    }

    nlohmann::json json;

    file >> json;

    file.close();

    if (json.contains("eval")) {
        auto& eval = json["eval"];

        std::string representation_type_str = eval.value("representation_type", "exact");
        std::string representation_format_str = eval.value("representation format", "normal");

        config.sci_representation_n_digits = eval.value("sci_representaion_n_digits", 12);
        config.auto_sci_threshold_n_digits = eval.value("auto_sci_threshold_n_digits", 70);
        config.sci_min_n_digits = eval.value("sci_min_n_digits", 3);
        config.auto_sci = eval.value("auto_sci", true);
        config.math_prec = eval.value("math_prec", 8192);
        config.out_prec = eval.value("out_prec", 128);

        if (representation_type_str == "float") {
            config.out_representation_type = REPRESENTATION_TYPE_FLOAT;
        }
        else {
            config.out_representation_type = REPRESENTATION_TYPE_EXACT;
        }

        if (representation_format_str == "sci") {
            config.out_representation_format = REPRESENTATION_FORMAT_SCI;
        }
        else {
            config.out_representation_format = REPRESENTATION_FORMAT_NORMAL;
        }
    }
    else {
        std::cout << "eval not found in config.json" << std::endl;
    }

    std::cout << "loaded config: " << std::endl;

    print_config(config);

    return config;
}
