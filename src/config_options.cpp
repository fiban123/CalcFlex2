#include "config_options.hpp"

#include <set>

#include "config_loader.hpp"

void Config::write_to_eval_cfg(EvalConfig& eval_config) {
    eval_config.out_prec = out_prec.value;
    eval_config.auto_sci_threshold_n_digits =
        auto_sci_threshold_n_digits.value;
    eval_config.math_prec = math_prec.value;
    eval_config.out_representation_format =
        representation_format.value;
    eval_config.out_representation_type = representation_type.value;
    eval_config.sci_min_n_digits = sci_min_n_digits.value;
    eval_config.sci_representation_n_digits =
        sci_representaion_n_digits.value;
}

void Config::write_to_strings() {
    for (Setting* s : setting_vec) {
        s->value_str = s->to_string();
    }
}

bool Config::read_from_strings(std::string& err_out) {
    bool err = false;
    for (Setting* s : setting_vec) {
        if (!s->set_from_string()) {
            err = true;
            err_out = "could not parse: " + s->label;
        }
    }
    return err;
}

void Config::write() {
    print_config(eval_config);

    write_config(*this, "../config.json");
}
