#include "lines.hpp"

void Lines::draw(){
    window->draw(line_vertices.data(), line_vertices.size(), sf::PrimitiveType::Lines);
}

void Lines::resize_update(){
    update_lines();
}

void Lines::update_lines(){
    float below_expression_input_y = EXPRESSION_INPUT_TOP_OFFSET + EXPRESSION_INPUT_HEIGHT + EXPRESSION_INPUT_SPACING / 2.f;
    float below_expression_input_spacing_y = below_expression_input_y + EXPRESSION_INPUT_SPACING / 2.f;
    // right of func group buttons
    line_vertices[0].position = {2.f * SPACING+ FUNCTION_GROUP_BUTTON_DIM.x, window_size->y};
    line_vertices[1].position = {2.f * SPACING + FUNCTION_GROUP_BUTTON_DIM.x, below_expression_input_spacing_y};
    // left of main buttons
    line_vertices[2].position = {window_size->x - 5.f * BUTTON_SIZE - 6.f * SPACING, window_size->y};
    line_vertices[3].position = {window_size->x - 5.f * BUTTON_SIZE - 6.f * SPACING, below_expression_input_spacing_y};
    // below expression input
    line_vertices[4].position = {0, below_expression_input_y};
    line_vertices[5].position = {window_size->x, below_expression_input_y};
}

Lines::Lines(sf::RenderWindow *_window, sf::Vector2u *_window_size)
    : window(_window), window_size(_window_size)
{

    line_vertices.resize(N_LINES * 2);

    for (sf::Vertex& v : line_vertices){
        v.color = LINE_COLOR;
    }

    update_lines();
}
