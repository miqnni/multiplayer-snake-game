#include "food.h"

Food::Food(MapSettings map_settings, const char *texture_path)
    : map_settings(map_settings)
{
    position = GenerateRandomPos(map_settings.getXCellCount(), map_settings.getYCellCount());
    UseImage(texture_path);
}

void Food::UseImage(const char *texture_path)
{
    // "img/food1.png"
    Image image = LoadImage(texture_path);
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

Vector2 Food::GenerateRandomPos(int x_cell_count, int y_cell_count)
{
    float x_pos = (float)GetRandomValue(0, x_cell_count - 1);
    float y_pos = (float)GetRandomValue(0, y_cell_count - 1);
    return Vector2{x_pos, y_pos};
}

Vector2 Food::GenerateRandomPosExtended(int x_cell_count, int y_cell_count, Vector2 excluded_a, Vector2 excluded_b)
{
    Vector2 candidate_vector = GenerateRandomPos(x_cell_count, y_cell_count);
    while (Vector2Equals(candidate_vector, excluded_a) || Vector2Equals(candidate_vector, excluded_b))
    {
        candidate_vector = GenerateRandomPos(x_cell_count, y_cell_count);
    }
    return candidate_vector;
}

void Food::Draw()
{
    // CONTAINER
    DrawRectangle(position.x * map_settings.getCellSize(), position.y * map_settings.getCellSize(), map_settings.getCellSize(), map_settings.getCellSize(), BLACK);
    DrawCircle((position.x + 0.5) * map_settings.getCellSize(), (position.y + 0.5) * map_settings.getCellSize(), map_settings.getCellSize(), {255, 255, 255, 70});

    // FOOD
    DrawTextureEx(texture, {position.x * map_settings.getCellSize(), position.y * map_settings.getCellSize()}, 0, (float)map_settings.getCellSize() / 50., WHITE);
}
