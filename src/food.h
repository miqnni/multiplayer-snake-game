#pragma once

#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "map_settings.h"

class Food
{
private:
    MapSettings map_settings;
    Vector2 position;
    Color color;
    Texture2D texture;

public:
    Food() {}
    Food(MapSettings map_settings, const char *texture_path);

    void Draw();
    void UseImage(const char *texture_path);
    Vector2 GenerateRandomPos(int x_cell_count, int y_cell_count);
    Vector2 GenerateRandomPosExtended(int x_cell_count, int y_cell_count, Vector2 excluded_a, Vector2 excluded_b);
    Vector2 getPosition() { return position; }
    MapSettings getMapSettings() { return map_settings; }
    Color getColor() { return color; }
    Texture2D getTexture2D() { return texture; }
    void setPosition(Vector2 new_position) { position = new_position; }
};
