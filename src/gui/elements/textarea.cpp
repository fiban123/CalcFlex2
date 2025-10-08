#include "textarea.hpp"

void TextArea::update_text(){
    text = sf::Text(string, *style->font, style->font_size);

    text.setFillColor(style->text_color);

    sf::FloatRect label_bounds = text.getLocalBounds();

    if (centered){
        text.setOrigin(label_bounds.left + label_bounds.width, label_bounds.top + label_bounds.height / 2.f);
    }
    else{
        text.setOrigin(label_bounds.left + label_bounds.width, label_bounds.top);
    }

    
    update_text_pos();
}

void TextArea::update_text_pos(){
    if (centered){
        text.setPosition({rect.getPosition().x + rect.getSize().x - style->spacing, rect.getPosition().y + rect.getSize().y / 2.f});
    }
    else{
        text.setPosition({rect.getPosition().x + rect.getSize().x - style->spacing, rect.getPosition().y + style->spacing});
    }

}

void TextArea::draw(sf::RenderWindow &window){
    window.draw(rect);
    window.draw(text);
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
