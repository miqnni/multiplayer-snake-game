#pragma once

#include <raylib.h>
#include <raymath.h>
#include <deque>

#include "map_settings.h"
#include "controls.h"

class Snake
{
private:
    MapSettings map_settings;
    Controls controls;
    Vector2 initial_head_position;
    Vector2 initial_move_direction;
    int initial_length;
    std::deque<Vector2> snake_body;
    Vector2 curr_move_direction;
    Color color;
    bool alive;
    bool will_grow;

    std::deque<Vector2> CreateBody(Vector2 head_position, Vector2 move_direction, int initial_length)
    {
        Vector2 reverse_move_direction = Vector2Negate(move_direction);
        std::deque<Vector2> created_body = {head_position};
        for (int i = 1; i < initial_length; i++)
        {
            Vector2 body_element_offset = {i * reverse_move_direction.x, i * reverse_move_direction.y};
            Vector2 new_body_element_position = Vector2Add(head_position, body_element_offset);
            created_body.push_back(new_body_element_position);
        }
        return created_body;
    }

public:
    Snake() {}

    Snake(
        MapSettings map_settings,
        Controls controls,
        Vector2 initial_head_position,
        Vector2 initial_move_direction,
        int initial_length,
        Color color)
        : map_settings(map_settings),
          controls(controls),
          initial_head_position(initial_head_position),
          initial_move_direction(initial_move_direction),
          initial_length(initial_length),
          snake_body(CreateBody(initial_head_position, initial_move_direction, initial_length)),
          curr_move_direction(initial_move_direction),
          color(color),
          alive(true),
          will_grow(false)
    {
    }

    bool isAlive() { return alive; }

    void Draw();

    void Update();

    void Disappear();

    void Reset();

    std::deque<Vector2> getSnakeBody()
    {
        return snake_body;
    }

    MapSettings getMapSettings() { return map_settings; }

    void setWillGrow(bool new_value)
    {
        will_grow = new_value;
    }
};
