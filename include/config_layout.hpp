#include "layout_base.hpp"
#include "text_setting.hpp"

struct ConfigLayout : LayoutBase {
    std::vector<TextArea> setting_group_labels;
    std::vector<TextSetting> settings;

    TextSettingStyle style;

    void resize_update(sf::Vector2u);

    void text_entered(unsigned c);

    void move_cursor(bool sign);

    void update(sf::Vector2i mouse_pos, bool left_click);

    void draw(sf::RenderWindow& window);

    void update_click(sf::Vector2i mouse_pos);

    void update_scroll(sf::Vector2i mouse_pos, float delta);

    ConfigLayout(sf::Font* _font,
                 sf::Vector2u _window_size,
                 sf::RenderWindow* _window);
};
