#include <raylib.h>
#include <algorithm>
#include <iostream>
#include <string>
#include "food.h"
#include "snake.h"
#include "dead_snake.h"
#include "map_settings.h"

#define BUF_SIZE 255
#define FOOD_PATH "img/snake_food.png"
#define DEFAULT_SNAKE_LENGTH 4
// #define FOOD_COUNT 8
#define STEP_TIME 0.2
#define GAME_TITLE "SNAKE PvP"
#define DEFAULT_TEXT_CONTENT "Press SPACE to start"

class Game
{
private:
    MapSettings map_settings;
    bool game_started;
    Snake snake0;
    Snake snake1;
    DeadSnake dead_snake0;
    DeadSnake dead_snake1;
    double last_update_time = 0;
    Food single_food0;
    Food single_food1;
    bool eventTriggered(double interval);
    char text_content[BUF_SIZE];

public:
    Game() {}

    Game(MapSettings map_settings, const char *food_img_path);

    void Update();

    bool CheckCollisionSnakeFood(Snake chosen_snake, Food chosen_food);

    bool CheckCollisionSnakeEdge(Snake chosen_snake);

    bool Vector2InSnakeBody(Vector2 vector, std::deque<Vector2> snake_body);

    bool CheckCollisionSnakeSelf(Snake snake);

    bool CheckCollisionSnakeOpponentbody(Snake snake_a, Snake snake_b);

    void StartGame();

    void EndGame();
};
