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

template <typename ValueT>
struct Setting {
    std::string label;
    std::string info;
    std::string value_str;
    ValueT value;

    virtual std::string to_string() = 0;
    virtual bool set_from_string() = 0;

    virtual ~Setting() = default;

    Setting(const std::string& _label,
            const std::string& _info,
            const ValueT _value)
        : label(_label), info(_info), value(_value) {}
};

struct DoubleSetting : Setting<double> {
    std::string to_string() override { return std::to_string(value); }

    bool set_from_string() override {
        value = stod(value_str);
        return true;
    }

    DoubleSetting(const std::string _label,
                  const std::string _info,
                  const double _value)
        : Setting<double>(_label, _info, _value) {
        value_str = to_string();
    }
};

template <typename EnumT>
struct EnumSetting : Setting<EnumT> {
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
        : Setting<EnumT>(_label, _info, _value), bimap(_bimap) {
        this->value_str = this->to_string();
    }
};

struct SizeSetting : Setting<size_t> {
    std::string to_string() override { return std::to_string(value); }
    bool set_from_string() override {
        value = stoull(value_str);
        return true;
    }

    SizeSetting(const std::string _label,
                const std::string _info,
                const size_t _value)
        : Setting<size_t>(_label, _info, _value) {
        value_str = to_string();
    }
};

struct BoolSetting : Setting<bool> {
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
        : Setting<bool>(_label, _info, _value) {
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
};
