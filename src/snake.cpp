#include <iostream>
#include "snake.h"

void Snake::Draw()
{
    if (alive)
    {
        for (std::size_t i = 0; i < snake_body.size(); i++)
        {
            int curr_segment_x = snake_body[i].x;
            int curr_segment_y = snake_body[i].y;
            Rectangle segment_rectangle = {curr_segment_x * (float)map_settings.getCellSize(), curr_segment_y * (float)map_settings.getCellSize(), (float)map_settings.getCellSize(), (float)map_settings.getCellSize()};
            Color segment_color = i % 2 == 1 ? ColorBrightness(color, 0.5) : color;

            // Not rounded
            // DrawRectangle(segment_rectangle.x, segment_rectangle.y, segment_rectangle.width, segment_rectangle.height, segment_color);

            // Rounded
            DrawRectangleRounded(segment_rectangle, 0.5f, 0, segment_color);
        }
        Vector2 head_center = {(float)(snake_body[0].x + 0.5) * map_settings.getCellSize(), (float)(snake_body[0].y + 0.5) * map_settings.getCellSize()};

        double eye_radius_cell_size_ratio = 0.15;
        double pupil_radius_eye_radius_ratio = 0.53;
        double eye_radius = map_settings.getCellSize() * eye_radius_cell_size_ratio;
        double pupil_radius = pupil_radius_eye_radius_ratio * eye_radius;

        float offset_value = 0.25;
        Vector2 default_eye_offset = Vector2Multiply({offset_value, offset_value}, curr_move_direction);
        Vector2 eye_a_offset = default_eye_offset;
        Vector2 eye_b_offset = default_eye_offset;
        bool horizontal_movement = (bool)curr_move_direction.x;
        if (horizontal_movement)
        {
            eye_a_offset.y = -offset_value;
            eye_b_offset.y = offset_value;
        }
        else
        {
            eye_a_offset.x = -offset_value;
            eye_b_offset.x = offset_value;
        }
        Vector2 eye_a = Vector2Add(head_center, Vector2Scale(eye_a_offset, map_settings.getCellSize()));
        Vector2 eye_b = Vector2Add(head_center, Vector2Scale(eye_b_offset, map_settings.getCellSize()));

        DrawCircle(eye_a.x, eye_a.y, eye_radius, WHITE);
        DrawCircle(eye_b.x, eye_b.y, eye_radius, WHITE);
        DrawCircle(eye_a.x, eye_a.y, pupil_radius, BLACK);
        DrawCircle(eye_b.x, eye_b.y, pupil_radius, BLACK);
    }
}

void Snake::Update()
{
    if (alive)
    {
        // Update the direction if necessary.
        if (IsKeyDown(controls.getGoUpKey()) && curr_move_direction.y != 1)
            curr_move_direction = {0, -1};
        else if (IsKeyDown(controls.getGoRightKey()) && curr_move_direction.x != -1)
            curr_move_direction = {1, 0};
        else if (IsKeyDown(controls.getGoDownKey()) && curr_move_direction.y != -1)
            curr_move_direction = {0, 1};
        else if (IsKeyDown(controls.getGoLeftKey()) && curr_move_direction.x != 1)
            curr_move_direction = {-1, 0};

        // Remove the last element of the snake and add the new element in the front,
        // according to the current move direction.
        if (!will_grow)
            snake_body.pop_back();
        else
            will_grow = false;
        Vector2 new_snake_head = Vector2Add(snake_body[0], curr_move_direction);
        snake_body.push_front(new_snake_head);
    }
}

void Snake::Disappear()
{
    snake_body = {};
    alive = false;
}

void Snake::Reset()
{
    alive = true;
    snake_body = CreateBody(initial_head_position, initial_move_direction, initial_length);
    curr_move_direction = initial_move_direction;
}
