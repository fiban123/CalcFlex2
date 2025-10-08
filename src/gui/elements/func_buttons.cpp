#include "func_buttons.hpp"

#include "point_collide.hpp"

#include <iostream>

inline const std::vector<std::vector<std::string> > aux_menu_button_labels = AUX_MENU_BUTTON_LABELS;

void FunctionButtons::group_button_callback(){
    update_buttons();
}

void FunctionButtons::draw()
{
    for (Checkbox& b : func_groups){
        b.draw(*window);
    }
    for (FunctionButton& fb : func_buttons){
        fb.b.draw(*window);
    }
    window->draw(
        func_group_delimeters_transformed.data(), 
        func_group_delimeters_transformed.size(),
        sf::PrimitiveType::Lines
    );
    window->draw(black_rect);
}

void FunctionButtons::update(sf::Vector2i mouse_pos, bool left_click){
    for (Checkbox& b : func_groups){
        b.update(mouse_pos, left_click);
    }
    for (FunctionButton& fb : func_buttons){
        fb.b.update(mouse_pos, left_click);
    }
    
}

void FunctionButtons::update_click(sf::Vector2i click_pos){
    for (Checkbox& b : func_groups){
        b.update_click(click_pos);
    }
    for (FunctionButton& fb : func_buttons){
        fb.b.update_click(click_pos);
    }
}

void FunctionButtons::update_scroll(sf::Vector2i mouse_pos, float delta){
    // -1 = down, 1 = up
    if(rect_point_collide(mouse_pos, rect_pos_transformed, rect_size)){
        y_offset += delta * 50;
        update_button_offsets();
    }
}

void FunctionButtons::resize_update(){
    size_t x = SPACING;
    size_t start_y = window_size->y - func_group_button_states.size() * (FUNCTION_GROUP_BUTTON_DIM.y + SPACING);

    for (size_t by = 0; by < func_group_button_labels.size(); by++){
        func_groups[by].update_pos({(float) x, start_y + by * (FUNCTION_GROUP_BUTTON_DIM.y + SPACING)});
    }

    update_buttons();
}

void FunctionButtons::update_button_offsets(){

    rect_pos_transformed = rect_pos;
    rect_pos_transformed.y += y_offset;

    bool big_function_buttons = rect_pos.y + rect_size.y > window_size->y;

    float min_y_offset;
    float max_y_offset;

    if (big_function_buttons){
        min_y_offset = window_size->y - rect_pos.y - rect_size.y;
        max_y_offset = 0;
    }
    else{
        min_y_offset = 0;
        max_y_offset = window_size->y - rect_pos.y - rect_size.y; 
    }

    y_offset = std::max(y_offset, min_y_offset);
    y_offset = std::min(y_offset, max_y_offset);


    for (FunctionButton& fb : func_buttons){
        fb.b.update_pos({fb.pos.x, fb.pos.y + y_offset});
    }
    func_group_delimeters_transformed = func_group_delimeters;

    for (sf::Vertex& v : func_group_delimeters_transformed){
        v.position.y += y_offset;
    }
}

void FunctionButtons::update_buttons(){

    func_buttons.clear();
    func_group_delimeters.clear();

    unsigned max_buttons_x = (window_size->x - FUNCTION_GROUP_BUTTON_DIM.x - 5 * BUTTON_SIZE - 8 * SPACING) / (FUNCTION_BUTTON_DIM.x + SPACING);
    
    float start_x = FUNCTION_GROUP_BUTTON_DIM.x + 3 * SPACING;
    float end_x = (window_size->x - 5 * BUTTON_SIZE - 6 * SPACING);
    float start_y = window_size->y - 6 * (BUTTON_SIZE + SPACING);

    float cy = start_y;

    rect_pos = {start_x, start_y};
    rect_size.x = end_x - start_x;
    
    for (size_t group = 0; group < func_groups.size(); group++){ // foreach func group
        // check if group is enabled
        if (!func_groups[group].checked){
            continue;
            std::cout << group << std::endl;
        }
        // create buttons
        size_t column = 0;
        for (size_t func = 0; func < func_button_labels[group].size(); func++){
            if (column >= max_buttons_x){
                column = 0;
                cy += (FUNCTION_BUTTON_DIM.y + SPACING);
            }
            FunctionButton fb;
            fb.pos = {start_x + column * (FUNCTION_BUTTON_DIM.x + SPACING), cy};
            fb.label = func_button_labels[group][func];
            fb.b = Button(
                {fb.pos.x, fb.pos.y - y_offset},
                FUNCTION_BUTTON_DIM,
                [this, group, func]{func_callback(func_button_strings[group][func], func_button_offsets[group][func]);},
                fb.label,
                &button_style
            );
            func_buttons.push_back(fb);

            column++;
        }
        cy += FUNCTION_BUTTON_DIM.y + FUNCTION_GROUP_SPACING / 2;
        
        // create group delimeter
        func_group_delimeters.push_back(sf::Vertex({start_x, cy}, FUNCTION_GROUP_DELIMIETER_LINE_COLOR, {0, 0}));
        func_group_delimeters.push_back(sf::Vertex({end_x - SPACING, cy}, FUNCTION_GROUP_DELIMIETER_LINE_COLOR, {0, 0}));
        cy += FUNCTION_GROUP_SPACING / 2;
    }

    rect_size.y = cy - start_y;

    if (cy > window_size->y){
        // adjust button position to fit
        float maxdiff = start_y - FUNCTION_BUTTONS_MAX_TOP_OFFSET;
        float diff = cy - window_size->y;
        diff = std::min(diff, maxdiff);

        for (FunctionButton& fb : func_buttons){
            fb.pos.y -= diff;
        }

        for (sf::Vertex& v : func_group_delimeters){
            v.position.y -= diff;
        }
        rect_pos.y -= diff;
    }

    update_button_offsets();
}

FunctionButtons::FunctionButtons(sf::RenderWindow *_window, sf::Vector2u *_window_size, sf::Font *_font, std::function<void(std::string, unsigned)> _func_callback)
        : window(_window), window_size(_window_size), font(_font), func_callback(_func_callback){
    
    checkbox_style = CheckboxStyle{
        .bg_color = BUTTON_BG_COLOR,
        .hover_border_color = BUTTON_HOVER_OUTLINE_COLOR,
        .press_bg_color = BUTTON_PRESS_BG_COLOR,
        .checked_border_color = DIM_HIGHLIGHT_COLOR,
        .font = font,
        .font_size = FUNCTION_GROUP_BUTTON_FONT_SIZE
    };

    button_style = ButtonStyle{
        .bg_color = BUTTON_BG_COLOR,
        .hover_border_color = BUTTON_HOVER_OUTLINE_COLOR,
        .press_bg_color = BUTTON_PRESS_BG_COLOR,
        .font = font,
        .font_size = FUNCTION_GROUP_BUTTON_FONT_SIZE
    };

    y_offset = 0;

    // create func group buttons
    size_t func_group_button_y = func_group_button_labels.size();

    size_t x = SPACING;
    size_t start_y = window_size->y - func_group_button_y * (FUNCTION_GROUP_BUTTON_DIM.y + SPACING);

    for (size_t by = 0; by < func_group_button_y; by++){
        std::string label = func_group_button_labels[by];;
        Checkbox b(
            {(float) x, start_y + by * (FUNCTION_GROUP_BUTTON_DIM.y + SPACING)},
            FUNCTION_GROUP_BUTTON_DIM,
            [this]{group_button_callback();},
            label,
            &checkbox_style,
            func_group_button_states[by]
        );
        func_groups.push_back(b);;
    }

    // create black rect
    black_rect.setPosition({0, 0});
    black_rect.setSize({window_size->y, FUNCTION_BUTTONS_MAX_TOP_OFFSET});
    black_rect.setFillColor(sf::Color::Black);

    update_buttons();
}
