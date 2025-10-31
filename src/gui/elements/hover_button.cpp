#include "hover_button.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "point_collide.hpp"

void HoverButton::draw(sf::RenderWindow& window) {
    window.draw(rect);
    window.draw(label);
}

void HoverButton::update(sf::Vector2i mouse_pos, bool left_click) {
    if (point_collide(mouse_pos)) {
        hovering = true;
        rect.setOutlineThickness(-style->outline_thickness);
    }
    else {
        hovering = false;
        rect.setOutlineThickness(0);
    }
}

bool HoverButton::point_collide(sf::Vector2i pos) {
    return rect_point_collide(pos, rect);
}

void HoverButton::update_pos(sf::Vector2f new_pos) {
    rect.setPosition(new_pos);

    label.setPosition(new_pos.x + rect.getSize().y / 2.f,
                      new_pos.y + rect.getSize().y / 2.f);
}

void HoverButton::update_label(std::string label_string) {
    label = sf::Text(label_string, *style->font, style->font_size);

    label.setFillColor(style->text_color);

    sf::FloatRect label_bounds = label.getLocalBounds();
    label.setOrigin(label_bounds.left + label_bounds.width / 2.0f,
                    label_bounds.top + label_bounds.height / 2.0f);

    label.setPosition({rect.getPosition().x + rect.getSize().x / 2.0f,
                       rect.getPosition().y + rect.getSize().y / 2.0f});
}

HoverButton::HoverButton(sf::Vector2f pos, sf::Vector2f size, std::string label,
                         HoverButtonStyle* _style)
    : style(_style) {
    rect.setFillColor(style->bg_color);
    rect.setOutlineColor(style->hover_border_color);
    rect.setPosition(pos);
    rect.setSize(size);

    update_label(label);
}
