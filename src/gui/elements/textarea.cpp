#include "textarea.hpp"

#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <sstream>

void TextArea::update_text() {
    text_lines.clear();

    std::istringstream iss(string);
    std::string line;

    while (std::getline(iss, line)) {
        sf::Text lineText = sf::Text(line, *style->font, style->font_size);

        lineText.setFillColor(style->text_color);

        text_lines.push_back(lineText);
    }

    update_text_pos();
}

void TextArea::update_text_pos() {
    if (text_lines.empty()) {
        return;
    }

    // compute total height of text
    float total_height = (text_lines[0].getLocalBounds().height + style->entry_spacing) *
                         text_lines.size();
    total_height -= style->entry_spacing;  // remove last spacing

    float start_y;
    switch (ybound) {
        case YBound::TOP: {
            start_y = rect.getPosition().y + style->spacing;
            break;
        }
        case YBound::BOTTOM: {
            start_y =
                rect.getPosition().y + rect.getSize().y - total_height - style->spacing;
            break;
        }
        case YBound::CENTER: {
            start_y = rect.getPosition().y + (rect.getSize().y - total_height) / 2.f;
            break;
        }
    }

    std::cout << start_y << " " << rect.getPosition().y << std::endl;

    float y = start_y;
    // calculate coord of each line
    for (sf::Text& line : text_lines) {
        sf::FloatRect bounds = line.getLocalBounds();

        float x = rect.getPosition().x;
        switch (xbound) {
            case XBound::LEFT: {
                x += style->spacing;
                break;
            }
            case XBound::RIGHT: {
                x += rect.getSize().x - bounds.width - style->spacing;
                break;
            }
            case XBound::CENTER: {
                x += rect.getSize().x / 2.f - bounds.width / 2.f;
                break;
            }
        }

        line.setPosition({x, y - bounds.top});

        y += bounds.height + style->entry_spacing;
    }
}

void TextArea::draw(sf::RenderWindow& window) {
    window.draw(rect);
    for (sf::Text& line : text_lines) {
        window.draw(line);
    }
}

void TextArea::resize(sf::Vector2f new_size) {
    rect.setSize(new_size);
    update_text_pos();
}

TextArea::TextArea(std::string start_text, sf::Vector2f pos, sf::Vector2f size,
                   TextAreaStyle* _style, XBound _xbound, YBound _ybound)
    : style(_style), string(start_text), xbound(_xbound), ybound(_ybound) {
    rect.setPosition(pos);
    rect.setSize(size);
    rect.setFillColor(style->bg_color);
    rect.setOutlineColor(style->outline_color);
    rect.setOutlineThickness(style->outline_width);

    update_text();
}
