#pragma once

#include <raylib.h>
#include "controls.h"

#define MAX_FOOD_COUNT 8
#define MAX_SNAKE_COUNT 4

class MapSettings
{
private:
    int x_cell_count;
    int y_cell_count;
    int cell_size;
    Color foreground_color;
    Color background_color;
    int initial_food_count;
    int initial_snake_count;

public:
    MapSettings(){};
    MapSettings(int x_cell_count, int y_cell_count, int cell_size, Color foreground_color, Color background_color, int initial_food_count, int initial_snake_count)
        : x_cell_count(x_cell_count), y_cell_count(y_cell_count), cell_size(cell_size), foreground_color(foreground_color), background_color(background_color), initial_food_count(initial_food_count), initial_snake_count(initial_snake_count) {}

    int getXCellCount()
    {
        return x_cell_count;
    }
    int getYCellCount()
    {
        return y_cell_count;
    }
    int getCellSize()
    {
        return cell_size;
    }
    Color getForegroundColor()
    {
        return foreground_color;
    }
    Color getBackgroundColor()
    {
        return background_color;
    }
};
