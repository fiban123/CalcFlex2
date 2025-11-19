#include "config_layout.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "config_options.hpp"
#include "gui_config.hpp"
#include "layouts.hpp"
#include "text_setting.hpp"
#include "textarea.hpp"

void ConfigLayout::enter() {}

void ConfigLayout::resize_update(sf::Vector2u size) {}

void ConfigLayout::text_entered(unsigned c) {
    if (c == 13) {
        update_config();
    }

    for (TextSetting& s : settings) {
        s.text_entered(c);
    }
}

void ConfigLayout::move_cursor(bool sign) {
    for (TextSetting& s : settings) {
        s.move_cursor(sign);
    }
}

void ConfigLayout::update(sf::Vector2i mouse_pos, bool left_click) {
    for (TextSetting& s : settings) {
        s.update(mouse_pos, left_click);
    }
}

void ConfigLayout::draw(sf::RenderWindow& window) {
    for (TextSetting& s : settings) {
        s.draw(window);
    }
}

void ConfigLayout::update_click(sf::Vector2i mouse_pos) {
    for (TextSetting& s : settings) {
        s.update_click(mouse_pos);
    }
}

void ConfigLayout::update_scroll(sf::Vector2i mouse_pos,
                                 float delta) {}

void ConfigLayout::update_config() {
    config.auto_sci.value_str = settings[0].input.text_area.string;
    config.auto_sci_threshold_n_digits.value_str =
        settings[1].input.text_area.string;
    config.math_prec.value_str = settings[2].input.text_area.string;
    config.out_prec.value_str = settings[3].input.text_area.string;
    config.representation_format.value_str =
        settings[4].input.text_area.string;
    config.representation_type.value_str =
        settings[5].input.text_area.string;
    config.sci_min_n_digits.value_str =
        settings[6].input.text_area.string;
    config.sci_representaion_n_digits.value_str =
        settings[7].input.text_area.string;

    std::string err_str;
    bool err = config.read_from_strings(err_str);

    config.write();

    Layout* layout =
        static_cast<Layout*>(layouts[Layouts::MAIN].get());

    if (err) {
        layout->info_bar.set_string(err_str);
    }
    else {
        layout->info_bar.set_string("settings saved successfully!");
    }

    config.write_to_strings();

    for (size_t i = 0; i < setting_vec.size(); i++) {
        settings[i].input.text_area.string =
            setting_vec[i]->value_str;
        settings[i].input.update_text();
    }
}

ConfigLayout::ConfigLayout(sf::Font* font,
                           sf::Vector2u window_size,
                           sf::RenderWindow* window)
    : LayoutBase(font, window_size, window) {
    // create style

    // lots of emopty comments becuse otherwise clang
    // format puts everything in one line👽
    style = TextSettingStyle{

        40,
        40,
        10,
        //
        {
            //
            TEXT_COLOR,
            BLACK,
            OUTLINE_CONTRAST,
            1,
            10,
            10,
            23,
            font
            //
        },
        //
        {
            //
            TEXT_COLOR,
            BUTTON_BG_COLOR,
            DIM_HIGHLIGHT_COLOR,
            1,
            10,
            10,
            20,
            font
            //
        },
        //
        {
            //
            TEXT_COLOR,
            TEXT_COLOR,
            {
                //
                TEXT_COLOR,
                BUTTON_BG_COLOR,
                OUTLINE_HIGHLIGHT_COLOR,
                1,
                10,
                10,
                30,
                font
                //
            },
            //
            {
                //
                TEXT_COLOR,
                BUTTON_BG_COLOR,
                HIGHLIGHT_COLOR,
                1,
                10,
                10,
                30,
                font
                //
            }
            //
        },

        {
            //
            BUTTON_BG_COLOR,
            BUTTON_HOVER_OUTLINE_COLOR,
            TEXT_COLOR,
            font,
            1,
            10,
            22
            //
        }  //
        //
    };

    float x = 30;
    float y = 30;

    for (Setting* s : setting_vec) {
        settings.emplace_back(
            //
            TextSetting(
                //
                s->label,
                s->value_str,
                s->info,
                {x, y},
                &style,
                200,
                false
                //
                )
            //
        );

        y += settings.back().rect.getLocalBounds().height + 50;
    }
}
