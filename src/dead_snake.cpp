#include "dead_snake.h"

void DeadSnake::Draw()
{
    for (std::size_t i = 0; i < body.size(); i++)
    {

        int curr_segment_x = body[i].x;
        int curr_segment_y = body[i].y;
        DrawCircle((curr_segment_x + 0.25) * map_settings.getCellSize(), (curr_segment_y + 0.75) * map_settings.getCellSize(), 0.75 * map_settings.getCellSize(), color);
        DrawCircle((curr_segment_x + 0.75) * map_settings.getCellSize(), (curr_segment_y + 0.25) * map_settings.getCellSize(), 0.75 * map_settings.getCellSize(), color);
    }
}