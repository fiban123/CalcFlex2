#pragma once

#include <boost/bimap.hpp>
#include <cassert>
#include <cstdlib>
#include <initializer_list>
#include <string>
#include <utility>
#include <vector>

#include "eval_config.hpp"

template <typename T1, typename T2>
struct BiMap {
    boost::bimap<T1, T2> bimap;

    BiMap() = default;

    BiMap(std::initializer_list<std::pair<T1, T2>> init_list) {
        for (const auto& [left, right] : init_list) {
            bimap.insert({left, right});
        }
    }

    bool find_right(const T1& left, T2& right_out) const {
        auto it = bimap.left.find(left);
        if (it == bimap.left.end()) {
            return false;
        }
        right_out = it->second;
        return true;
    }

    bool find_left(const T2& right, T1& left_out) const {
        auto it = bimap.right.find(right);
        if (it == bimap.right.end()) {
            return false;
        }
        left_out = it->second;
        return true;
    }

    const T1& find_left_r(const T2& right) const {
        auto it = bimap.right.find(right);
        assert(it != bimap.right.end());
        return it->second;
    }
};

template <typename EnumT>
using EnumSettingBiMap = BiMap<std::string, EnumT>;

struct Setting {
    std::string label;
    std::string info;
    std::string value_str;

    virtual std::string to_string() = 0;
    virtual bool set_from_string() = 0;

    virtual ~Setting() = default;

    Setting(const std::string& _label, const std::string& _info)
        : label(_label), info(_info) {}
};

struct DoubleSetting : Setting {
    double value;

    std::string to_string() override { return std::to_string(value); }

    bool set_from_string() override {
        try {
            value = std::stod(value_str);
            return true;
        }
        catch (...) {
            return false;
        }
    }

    DoubleSetting(const std::string _label,
                  const std::string _info,
                  const double _value)
        : Setting(_label, _info), value(_value) {
        value_str = to_string();
    }
};

template <typename EnumT>
struct EnumSetting : Setting {
    EnumT value;
    const EnumSettingBiMap<EnumT>& bimap;

    std::string to_string() override {
        return bimap.find_left_r(this->value);
    }
    bool set_from_string() override {
        EnumT e;
        bool s = bimap.find_right(this->value_str, e);
        if (!s) {
            return false;
        }
        this->value = e;
        return true;
    }

    EnumSetting(const std::string _label,
                const std::string _info,
                const EnumT _value,
                const EnumSettingBiMap<EnumT>& _bimap)
        : Setting(_label, _info), value(_value), bimap(_bimap) {
        this->value_str = this->to_string();
    }
};

struct SizeSetting : Setting {
    size_t value;
    std::string to_string() override { return std::to_string(value); }
    bool set_from_string() override {
        try {
            value = std::stoull(value_str);
            return true;
        }
        catch (...) {
            return false;
        }
    }

    SizeSetting(const std::string _label,
                const std::string _info,
                const size_t _value)
        : Setting(_label, _info), value(_value) {
        value_str = to_string();
    }
};

struct BoolSetting : Setting {
    bool value;
    std::string to_string() override {
        if (value == true) {
            return "true";
        }
        else {
            return "false";
        }
    }
    bool set_from_string() override {
        if (value_str == "true") {
            value = true;
        }
        else if (value_str == "false") {
            value = false;
        }
        else {
            return false;
        }
        return true;
    }

    BoolSetting(const std::string _label,
                const std::string _info,
                const bool _value)
        : Setting(_label, _info), value(_value) {
        value_str = to_string();
    }
};

inline const EnumSettingBiMap<NumberRepresentationType>
    representation_type_bimap = {
        {"float", REPRESENTATION_TYPE_FLOAT},
        {"exact", REPRESENTATION_TYPE_EXACT}};

inline const EnumSettingBiMap<NumberRepresentationFormat>
    representation_format_bimap = {
        {"sci", REPRESENTATION_FORMAT_SCI},
        {"normal", REPRESENTATION_FORMAT_NORMAL}};

struct Config {
    BoolSetting auto_sci{
        //
        "Auto scientific mode [true, false]",
        //
        "if the length of a result is bigger than\n"
        "Auto sci Threshold,\n"
        "it will automatically switch to\n"
        "scientific mode\n",
        true
        //
    };

    SizeSetting auto_sci_threshold_n_digits{
        //
        "Auto Sci Threshold [n digits]",
        //
        "if auto scientific mode is enabled, this\n"
        "determines how long a result has to be\n"
        "for auto sci to kick in.\n",
        //
        70};

    SizeSetting math_prec{
        //
        "Math precision [bits]",
        //
        "the the amount of precision in bits\n"
        "used during calculation for floating-\n"
        "point operations. 64 bits is about\n"
        "15 (base-10) digits of precision\n"
        "must be below ~2^32-512 on Windows\n",
        //
        8192
        //
    };

    SizeSetting out_prec{
        //
        "Result Precision [bits]",
        //
        "the amount of precision in bits\n"
        "in which float results are\n"
        "displayed. 64 bits is ~15\n"
        "(base-10) digits.\n",
        //
        128,
        //
    };

    EnumSetting<NumberRepresentationFormat> representation_format{
        //
        "Representation Format [sci, normal]",
        //
        "if the representation format is sci,\n"
        "results will be displayed in scientific\n"
        "notation.\n",
        //
        REPRESENTATION_FORMAT_SCI,
        representation_format_bimap
        //
    };

    EnumSetting<NumberRepresentationType> representation_type{
        //
        "Result Representation Type [exact, float]",
        //
        "if the representation type is exact, results\n"
        "will be displayed as exact, rational numbers\n"
        "if possible. if the representation type is\n"
        "float, results will always be displayed as\n"
        "sometimes imperfect, floating-point values.",
        //
        REPRESENTATION_TYPE_EXACT,
        representation_type_bimap
        //
    };

    SizeSetting sci_min_n_digits{
        //
        "Minimum digits for scientific mode [n digits]",
        //
        "if the log10 of a result\n"
        "is below this number, it will never\n"
        "be displayed as scientifix. even if\n"
        "scientific mode is enabled. This is\n"
        "not affected by auto scientific mode.",
        //
        3
        //
    };

    SizeSetting sci_representaion_n_digits{
        //
        "Max. Mantissa length for scientific notation [n digits]",
        //
        "controls the maximum amount of digits\n"
        "displayed in the mantissa of\n"
        "scientific notation\n",
        //
        12,
        //
    };
    void write_to_eval_cfg(EvalConfig& eval_config);
    void write_to_strings();
    bool read_from_strings(std::string& err_out);

    void write();
};

inline Config config;

inline std::vector<Setting*> setting_vec = {
    //
    &config.auto_sci,
    &config.auto_sci_threshold_n_digits,
    &config.math_prec,
    &config.out_prec,
    &config.representation_format,
    &config.representation_type,
    &config.sci_min_n_digits,
    &config.sci_representaion_n_digits
    //
};
