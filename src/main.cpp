#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Ping Pong");

    SetTargetFPS(60);

    class Paddle{
    public:
        float width = 10;
        float height = 100;
        float x;
        float y = (screenHeight/2) - (height/2);
        Color color = BLACK;
    public:
        void draw(){DrawRectangle(x, y, width, height, color);};
    };
    Paddle left_paddle; left_paddle.x = 10;
    Paddle right_paddle; right_paddle.x = (screenWidth-10-right_paddle.width);

    class Ball{
    public:
        int x = screenWidth/2;
        int y = screenHeight/2;
        float radius = 10;
        Color color = BLACK;
    public:
        void draw(){DrawCircle(x, y, radius, color);}
    };
    Ball ball;

    while (!WindowShouldClose())
    {

        BeginDrawing();

            left_paddle.draw();
            right_paddle.draw();
            ball.draw();

            ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}