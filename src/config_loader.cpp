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
              << "\nout_prec: " << config.out_prec;
}

bool str_to_representation_type(std::string& str,
                                NumberRepresentationType& out) {
    if (str == "float") {
        out = REPRESENTATION_TYPE_FLOAT;
        return true;
    }
    else if (str == "exact") {
        out = REPRESENTATION_TYPE_EXACT;
        return true;
    }
    return false;
}

bool str_to_representation_format(std::string& str,
                                  NumberRepresentationFormat& out) {
    if (str == "sci") {
        out = REPRESENTATION_FORMAT_SCI;
        return true;
    }
    else if (str == "normal") {
        out = REPRESENTATION_FORMAT_NORMAL;
        return true;
    }
    return false;
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

        std::string representation_type_str =
            eval.value("representation_type",
                       representation_type_bimap.find_left_r(
                           eval_config.out_representation_type));

        std::string representation_format_str =
            eval.value("representation format",
                       representation_format_bimap.find_left_r(
                           eval_config.out_representation_format));

        config.sci_representation_n_digits =
            eval.value("sci_representaion_n_digits",
                       eval_config.sci_representation_n_digits);
        config.auto_sci_threshold_n_digits =
            eval.value("auto_sci_threshold_n_digits",
                       eval_config.auto_sci_threshold_n_digits);
        config.sci_min_n_digits = eval.value(
            "sci_min_n_digits", eval_config.sci_min_n_digits);
        config.auto_sci =
            eval.value("auto_sci", eval_config.auto_sci);
        config.math_prec =
            eval.value("math_prec", eval_config.math_prec);
        config.out_prec =
            eval.value("out_prec", eval_config.out_prec);

        if (!representation_type_bimap.find_right(
                representation_type_str,
                config.out_representation_type)) {
            std::cout
                << "config loader: invalid out_representation_type\n";
        }

        if (!representation_format_bimap.find_right(
                representation_format_str,
                config.out_representation_format)) {
            std::cout << "config loader: invalid "
                         "out_representation_format\n";
        }
    }
    else {
        std::cout << "config loader: eval not found in config.json"
                  << std::endl;
    }

    std::cout << "loaded config: " << std::endl;

    print_config(config);

    return config;
}

void save_config(const EvalConfig& config, const std::string path) {
    nlohmann::json json;

    // Convert enums back to strings using your BiMaps
    std::string representation_type_str =
        representation_type_bimap.find_left_r(
            config.out_representation_type);
    std::string representation_format_str =
        representation_format_bimap.find_left_r(
            config.out_representation_format);

    // Build the "eval" section
    json["eval"] = {
        {"representation_type", representation_type_str},
        {"representation_format", representation_format_str},
        {"sci_representaion_n_digits",
         config.sci_representation_n_digits},
        {"auto_sci_threshold_n_digits",
         config.auto_sci_threshold_n_digits},
        {"sci_min_n_digits", config.sci_min_n_digits},
        {"auto_sci", config.auto_sci},
        {"math_prec", config.math_prec},
        {"out_prec", config.out_prec}};

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
