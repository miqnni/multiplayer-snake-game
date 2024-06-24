#include "game.h"

Game::Game(MapSettings map_settings, const char *food_img_path)
    : map_settings(map_settings)
{

    snake0 = Snake(map_settings, Controls(KEY_W, KEY_D, KEY_S, KEY_A), {1 + DEFAULT_SNAKE_LENGTH, 1}, {1, 0}, DEFAULT_SNAKE_LENGTH, DARKGREEN);
    snake1 = Snake(map_settings, Controls(KEY_UP, KEY_RIGHT, KEY_DOWN, KEY_LEFT), {(float)(map_settings.getXCellCount() - 2 - DEFAULT_SNAKE_LENGTH), (float)(map_settings.getYCellCount() - 2)}, {-1, 0}, DEFAULT_SNAKE_LENGTH, DARKBROWN);

    dead_snake0 = DeadSnake(snake0);
    dead_snake1 = DeadSnake(snake1);

    single_food0 = Food(map_settings, food_img_path);
    single_food1 = Food(map_settings, "img/snake_food_v2.png");

    sprintf(text_content, "%s\n\n\n%s", GAME_TITLE, DEFAULT_TEXT_CONTENT);

    game_started = false;
}

void Game::Update()
{
    if (game_started && eventTriggered(STEP_TIME))
    {
        snake0.Update();
        snake1.Update();

        bool alive_after_collision[2] = {true, true}; // Applies only for the snakes that are sill alive.
        if (snake0.isAlive())
        {
            if (CheckCollisionSnakeFood(snake0, single_food0))
            {
                single_food0.setPosition((single_food0.GenerateRandomPosExtended(map_settings.getXCellCount(), map_settings.getYCellCount(), snake0.getSnakeBody()[0], snake1.getSnakeBody()[1])));
                snake0.setWillGrow(true);
            }
            if (CheckCollisionSnakeFood(snake0, single_food1))
            {
                single_food1.setPosition((single_food1.GenerateRandomPosExtended(map_settings.getXCellCount(), map_settings.getYCellCount(), snake0.getSnakeBody()[0], snake1.getSnakeBody()[1])));
                snake0.setWillGrow(true);
            }
            if (CheckCollisionSnakeEdge(snake0) || CheckCollisionSnakeSelf(snake0) || CheckCollisionSnakeOpponentbody(snake0, snake1))
            {
                alive_after_collision[0] = false;
            }
        }

        if (snake1.isAlive())
        {
            if (CheckCollisionSnakeFood(snake1, single_food0))
            {
                single_food0.setPosition((single_food0.GenerateRandomPosExtended(map_settings.getXCellCount(), map_settings.getYCellCount(), snake0.getSnakeBody()[0], snake1.getSnakeBody()[1])));
                snake1.setWillGrow(true);
            }
            if (CheckCollisionSnakeFood(snake1, single_food1))
            {
                single_food1.setPosition((single_food1.GenerateRandomPosExtended(map_settings.getXCellCount(), map_settings.getYCellCount(), snake0.getSnakeBody()[0], snake1.getSnakeBody()[1])));
                snake1.setWillGrow(true);
            }
            if (CheckCollisionSnakeEdge(snake1) || CheckCollisionSnakeSelf(snake1) || CheckCollisionSnakeOpponentbody(snake1, snake0))
            {
                alive_after_collision[1] = 0;
            }
        }

        if (snake0.isAlive() && snake1.isAlive())
        {
            if (CheckCollisionSnakeOpponentbody(snake0, snake1))
                alive_after_collision[0] = false;
            if (CheckCollisionSnakeOpponentbody(snake1, snake0))
                alive_after_collision[1] = false;
        }

        if (snake0.isAlive() && !alive_after_collision[0])
        {
            dead_snake0 = DeadSnake(snake0);
            snake0.Disappear();
        }
        if (snake1.isAlive() && !alive_after_collision[1])
        {
            dead_snake1 = DeadSnake(snake1);
            snake1.Disappear();
        }
    }

    BeginDrawing();

    ClearBackground(map_settings.getBackgroundColor());

    single_food0.Draw();
    single_food1.Draw();

    if (snake0.isAlive())
        snake0.Draw();
    else
        dead_snake0.Draw();

    if (snake1.isAlive())
        snake1.Draw();
    else
        dead_snake1.Draw();

    if (!snake0.isAlive() || !snake1.isAlive())
    {
        if (snake0.isAlive())
        {
            sprintf(text_content, "SNAKE A WINS\n\n\n%s", DEFAULT_TEXT_CONTENT);
        }
        else if (snake1.isAlive())
        {
            sprintf(text_content, "SNAKE B WINS\n\n\n%s", DEFAULT_TEXT_CONTENT);
        }
        else
        {
            sprintf(text_content, "IT'S A DRAW!\n\n\n\n%s", DEFAULT_TEXT_CONTENT);
        }

        EndGame();
    }

    if (!game_started)
    {
        DrawText(text_content, 2 * map_settings.getCellSize(), 2 * map_settings.getCellSize(), map_settings.getCellSize(), BLACK);
        if (IsKeyDown(KEY_SPACE))
            StartGame();
    }

    EndDrawing();
}

bool Game::eventTriggered(double interval)
{
    double current_time = GetTime();
    if (current_time - last_update_time >= interval)
    {
        last_update_time = current_time;
        return true;
    }
    return false;
}

bool Game::CheckCollisionSnakeFood(Snake chosen_snake, Food chosen_food)
{
    return Vector2Equals(chosen_snake.getSnakeBody()[0], chosen_food.getPosition());
}

bool Game::CheckCollisionSnakeEdge(Snake chosen_snake)
{
    Vector2 snake_pos = chosen_snake.getSnakeBody()[0];
    float snake_x = snake_pos.x;
    float snake_y = snake_pos.y;
    return (snake_x < 0 || snake_x >= map_settings.getXCellCount() || snake_y < 0 || snake_y >= map_settings.getYCellCount());
}

bool Game::Vector2InSnakeBody(Vector2 vector2, std::deque<Vector2> snake_body)
{
    for (Vector2 body_vector2 : snake_body)
    {
        if (Vector2Equals(vector2, body_vector2))
            return true;
    }
    return false;
}

bool Game::CheckCollisionSnakeSelf(Snake snake)
{
    std::deque<Vector2> snake_body = snake.getSnakeBody();
    Vector2 snake_head = snake_body[0];
    std::deque<Vector2> snake_body_no_head = snake_body;
    snake_body_no_head.pop_front();

    return Vector2InSnakeBody(snake_head, snake_body_no_head);
}

bool Game::CheckCollisionSnakeOpponentbody(Snake snake_a, Snake snake_b)
{
    Vector2 snake_a_head = snake_a.getSnakeBody()[0];
    std::deque<Vector2> snake_b_body_rest = snake_b.getSnakeBody();
    return Vector2InSnakeBody(snake_a_head, snake_b_body_rest);
}

void Game::StartGame()
{
    snake0.Reset();
    snake1.Reset();
    single_food0.setPosition((single_food0.GenerateRandomPosExtended(map_settings.getXCellCount(), map_settings.getYCellCount(), snake0.getSnakeBody()[0], snake1.getSnakeBody()[1])));
    single_food1.setPosition((single_food1.GenerateRandomPosExtended(map_settings.getXCellCount(), map_settings.getYCellCount(), snake0.getSnakeBody()[0], snake1.getSnakeBody()[1])));

    game_started = true;
}

void Game::EndGame()
{
    game_started = false;
}