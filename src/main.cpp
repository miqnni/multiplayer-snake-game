#include <raylib.h>
#include <iostream>
#include "game.h"
#include "map_settings.h"

#define X_CELL_COUNT 25 // 15
#define Y_CELL_COUNT 30 // 20
#define CELL_SIZE 20    // 50

main()
{
    int main_x_cell_count = X_CELL_COUNT;
    int main_y_cell_count = Y_CELL_COUNT;
    int main_cell_size = CELL_SIZE;

    InitWindow(main_cell_size * main_x_cell_count, main_cell_size * main_y_cell_count, "SNAKE PvP");
    SetTargetFPS(240);

    char food_img_path[BUF_SIZE];
    sprintf(food_img_path, "%s", FOOD_PATH);

    Color altered_bg2 = {140, 140, 140, 255};
    MapSettings main_map_settings = MapSettings(main_x_cell_count, main_y_cell_count, main_cell_size, DARKPURPLE, altered_bg2, 4, 3);
    Game game = Game(main_map_settings, food_img_path);

    while (WindowShouldClose() == false)
    {
        game.Update();
    }

    CloseWindow();
    return 0;
}
