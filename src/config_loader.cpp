#include "config_loader.hpp"

#include <format>
#include <fstream>
#include <nlohmann/json.hpp>

#include "config_options.hpp"
#include "dynamic_vec.hpp"
#include "eval_config.hpp"

void print_config(EvalConfig& config) {
    std::cout << "representation_type: "
              << config.out_representation_type
              << "\nrepresentation_format: "
              << config.out_representation_format
              << "\nsci_representation_n_digits: "
              << config.sci_representation_n_digits
              << "\nauto_sci_threshold_n_digits: "
              << config.auto_sci_threshold_n_digits
              << "\nsci_min_n_digits: " << config.sci_min_n_digits
              << "\nauto_sci: " << config.auto_sci
              << "\nmath_prec: " << config.math_prec
              << "\nout_prec: " << config.out_prec << "sdisjhd";
}

void read_config(std::string path,
                 EvalConfig& eval_config,
                 Config& main_config) {
    std::cout << "readddingg config\n\n\n";

    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << std::format("file {} not found\n", path);
        return;
    }

    nlohmann::json json;

    file >> json;

    file.close();

    if (json.contains("eval")) {
        auto& eval = json["eval"];

        std::string representation_type_str =
            eval.value("representation_type",
                       representation_type_bimap.find_left_r(
                           eval_config.out_representation_type));

        std::string representation_format_str =
            eval.value("representation format",
                       representation_format_bimap.find_left_r(
                           eval_config.out_representation_format));

        main_config.sci_representaion_n_digits.value =
            eval.value("sci_representaion_n_digits",
                       eval_config.sci_representation_n_digits);
        main_config.auto_sci_threshold_n_digits.value =
            eval.value("auto_sci_threshold_n_digits",
                       eval_config.auto_sci_threshold_n_digits);
        main_config.sci_min_n_digits.value = eval.value(
            "sci_min_n_digits", eval_config.sci_min_n_digits);
        main_config.auto_sci.value =
            eval.value("auto_sci", eval_config.auto_sci);
        main_config.math_prec.value =
            eval.value("math_prec", eval_config.math_prec);
        main_config.out_prec.value =
            eval.value("out_prec", eval_config.out_prec);

        if (!representation_type_bimap.find_right(
                representation_type_str,
                main_config.representation_type.value)) {
            std::cout
                << "config loader: invalid out_representation_type\n";
        }

        std::cout << "math prec: " << config.math_prec.value << "\n";

        if (!representation_format_bimap.find_right(
                representation_format_str,
                config.representation_format.value)) {
            std::cout << "config loader: invalid "
                         "out_representation_format\n";
        }
    }
    else {
        std::cout << "config loader: eval not found in config.json"
                  << std::endl;
    }

    main_config.write_to_strings();
    std::cout << "jjjj" << main_config.math_prec.value_str << "\n";

    std::cout << "loaded config: " << std::endl;

    main_config.write_to_eval_cfg(eval_config);

    std::cout << "hhhhh" << eval_config.math_prec << "\n";

    print_config(eval_config);
}

void write_config(const Config& config, const std::string path) {
    nlohmann::json json;

    // Convert enums back to strings using your BiMaps
    std::string representation_type_str =
        representation_type_bimap.find_left_r(
            config.representation_type.value);
    std::string representation_format_str =
        representation_format_bimap.find_left_r(
            config.representation_format.value);

    // Build the "eval" section
    json["eval"] = {
        {"representation_type", representation_type_str},
        {"representation_format", representation_format_str},
        {"sci_representaion_n_digits",
         config.sci_representaion_n_digits.value},
        {"auto_sci_threshold_n_digits",
         config.auto_sci_threshold_n_digits.value},
        {"sci_min_n_digits", config.sci_min_n_digits.value},
        {"auto_sci", config.auto_sci.value},
        {"math_prec", config.math_prec.value},
        {"out_prec", config.out_prec.value}};

    // Write JSON to file (pretty printed)
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << std::format("Failed to open {} for writing\n",
                                 path);
        return;
    }

    file << std::setw(4) << json << std::endl;
    file.close();

    std::cout << "Config saved to " << path << std::endl;
}
