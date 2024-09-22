#include <iostream>
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
        float speed = 4;
    public:
        void draw(){DrawRectangle(x, y, width, height, color);};
        Rectangle get_rect(){return Rectangle{x, y, width, height};}
    };
    Paddle left_paddle; left_paddle.x = 10;
    Paddle right_paddle; right_paddle.x = (screenWidth-10-right_paddle.width);

    class Ball{
    public:
        float x = screenWidth/2;
        float y = screenHeight/2;
        float radius = 10;
        Color color = BLACK;
        float speedX;
        float speedY;
    public:
        void draw(){DrawCircle(x, y, radius, color);}
        void reset(){
            x = screenWidth/2;
            y = screenHeight/2;
            speedX = GetRandomValue(2,4);
            speedY = GetRandomValue(1,4);
            if(GetRandomValue(-1,1) < 0) {speedX *= -1;}
            if(GetRandomValue(-1,1) < 0) {speedY *= -1;}
        }
        void update(){
            x += speedX;
            y += speedY;
            if ((y-radius) <= 0) {speedY *= -1;}
            if ((y+radius) >= screenHeight) {speedY *= -1;}
        }
    };
    Ball ball; ball.reset();
    
    

    // std::cout<<"select 1player or 2player"<<std::endl;
    // int p; std::cin>>p;

    while (!WindowShouldClose())
    {
        // if (p==1)
        // {
            if (left_paddle.y >= 0){
                if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {left_paddle.y -= left_paddle.speed;}
            }
            if (left_paddle.y+left_paddle.height <= screenHeight){
                if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {left_paddle.y += left_paddle.speed;}
            }
            if (right_paddle.y >= 0){
                if(ball.y < right_paddle.y) {right_paddle.y -= right_paddle.speed;}
            }
            if ((right_paddle.y+right_paddle.height) <= screenHeight){
                if(ball.y > (right_paddle.y + right_paddle.height)) {right_paddle.y += right_paddle.speed;}
            }
        // }
        // if (p==2)
        // {
        //     if (left_paddle.y >= 0){
        //         if(IsKeyDown(KEY_W)) {left_paddle.y -= left_paddle.speed;}
        //     }
        //     if ((left_paddle.y+left_paddle.height) <= screenHeight){
        //         if(IsKeyDown(KEY_S)) {left_paddle.y += left_paddle.speed;}
        //     }
        //     if (right_paddle.y >= 0){
        //         if(IsKeyDown(KEY_UP)) {right_paddle.y -= right_paddle.speed;}
        //     }
        //     if ((right_paddle.y+right_paddle.height) <= screenHeight){
        //         if(IsKeyDown(KEY_DOWN)) {right_paddle.y += right_paddle.speed;}
        //     }
        // }
        ball.update();

        if (CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.radius, left_paddle.get_rect()))
        {
            if (ball.x > (left_paddle.x+left_paddle.width)) {ball.speedX *= -1;}
            else{ball.speedY *= -1;}
        }
        if (CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.radius, right_paddle.get_rect()))
        {
            if (ball.x < right_paddle.x) {ball.speedX *= -1;}
            else{ball.speedY *= -1;}
        }
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
            left_paddle.draw();
            right_paddle.draw();
            ball.draw();


        EndDrawing();
    }

    CloseWindow();

    return 0;
}