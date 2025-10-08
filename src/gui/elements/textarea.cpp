#include "textarea.hpp"

#include <sstream>
#include <iostream>

void TextArea::update_text(){
    text_lines.clear();
    
    float line_spacing = 5.f; // extra spacing between lines

    std::istringstream iss(string);
    std::string line;

    while (std::getline(iss, line)) {
        sf::Text lineText = sf::Text(line, *style->font, style->font_size);

        sf::FloatRect line_bounds = lineText.getLocalBounds();
        if (centered){
            lineText.setOrigin(line_bounds.left + line_bounds.width, line_bounds.top + line_bounds.height / 2.f);
        }
        else{
            lineText.setOrigin(line_bounds.left + line_bounds.width, line_bounds.top + line_bounds.height);
        }
        lineText.setFillColor(style->text_color);

        text_lines.push_back(lineText);
    }

    update_text_pos();
}

void TextArea::update_text_pos(){
    if (text_lines.empty()){
        return;
    }
    if (centered){
        text_lines[0].setPosition({rect.getPosition().x + rect.getSize().x - style->spacing, rect.getPosition().y + rect.getSize().y / 2.f});
    }
    else{
        float line_height = text_lines[0].getLocalBounds().height + style->entry_spacing;
        float start_y = rect.getPosition().y + rect.getSize().y - text_lines.size() * line_height;

        for (size_t i = 0; i < text_lines.size(); i++){
            text_lines[i].setPosition(
                {rect.getPosition().x + rect.getSize().x - style->spacing, 
                start_y + i * line_height
            });
        }
    }

}

void TextArea::draw(sf::RenderWindow &window){
    window.draw(rect);
    for (sf::Text& line : text_lines){
        window.draw(line);
    }
}

void TextArea::resize(sf::Vector2f new_size){
    rect.setSize(new_size);
    update_text_pos();
}

TextArea::TextArea(std::string start_text, sf::Vector2f pos, sf::Vector2f size, TextAreaStyle *_style, bool _centered)
        : style(_style), string(start_text), centered(_centered){

    rect.setPosition(pos);
    rect.setSize(size);
    rect.setFillColor(style->bg_color);

    update_text();
}
