#include <raylib.h>
#include <raymath.h>
#include <deque>

#include "map_settings.h"
#include "snake.h"

class DeadSnake : public Snake
{
private:
    MapSettings map_settings;
    std::deque<Vector2> body;
    Color color = {255, 0, 0, 70};

public:
    DeadSnake() {}
    DeadSnake(Snake snake) : map_settings(snake.getMapSettings()), body(snake.getSnakeBody()) {}

    void Draw();
};
