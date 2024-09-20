#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Basic window");

    SetTargetFPS(60);

    Rectangle paddle_left{30, (screenHeight/2) - (paddle_left.height/2), 20, 100};
    Rectangle paddle_right{(screenWidth-30-paddle_right.width), (screenHeight/2) - (paddle_left.height/2), 20, 100, };
    struct circle{
        int x = screenWidth/2;
        int y = screenHeight/2;
        float radius = 10;
        Color color = BLACK;

        void draw(){DrawCircle(x, y, radius, color);}
    };
    circle ball;
    while (!WindowShouldClose())
    {

        BeginDrawing();

            DrawRectangleRec(paddle_left, BLACK);
            DrawRectangleRec(paddle_right, BLACK);
            ball.draw();

            ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}