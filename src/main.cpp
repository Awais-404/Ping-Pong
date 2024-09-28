#define RAYGUI_IMPLEMENTATION
#include <iostream>
#include "raylib.h"
#include "raygui.h"


const int screenWidth = 800;
const int screenHeight = 450;

int score_P1;
int score_P2;
int collisions;

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
        speedX = GetRandomValue(2,5);
        speedY = GetRandomValue(1,4);
        if(GetRandomValue(-1,1) < 0) {speedX *= -1;}
        if(GetRandomValue(-1,1) < 0) {speedY *= -1;}
    }
    void update(){
        x += speedX;
        y += speedY;
        if ((y-radius) <= 0) {speedY *= -1;}
        if ((y+radius) >= screenHeight) {speedY *= -1;}
        if (collisions >= 5)
        {
            if (speedX > 0)
            {
                speedX += 1;
            }else{
                speedX -= 1;
            }

            if (speedY > 0)
            {
                speedY += 1;
            }else{
                speedY -= 1;
            }
            
            collisions = 0;
        }
        
    }
};

enum State{
    Main_Menu = 0,
    Player_1 = 1,
    Player_2 = 2
}state;

int main(void)
{
    Paddle left_paddle; left_paddle.x = 10;
    Paddle right_paddle; right_paddle.x = (screenWidth-10-right_paddle.width);    
    Ball ball; ball.reset();

    InitWindow(screenWidth, screenHeight, "Ping Pong");
    SetTargetFPS(60);

    state = Main_Menu;
    
    GuiSetStyle(BUTTON, BORDER_WIDTH, 3);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    while (!WindowShouldClose())
    {
        if(state == Main_Menu){
            // GuiLabel({350,30,100,50},"Pong");
            DrawText("Pong", 350,30, 40, BLACK);
            if(GuiButton({350,150,100,50},"1 Player")) {state = Player_1;}
            if(GuiButton({350,250,100,50},"2 Player")) {state = Player_2;}
            score_P1 = 0;
            score_P2 = 0;
            collisions = 0;
        }
        else{
            if (state == Player_1)
            {
                if (left_paddle.y >= 0){
                    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {left_paddle.y -= left_paddle.speed;}
                }
                if (left_paddle.y+left_paddle.height <= screenHeight){
                    if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {left_paddle.y += left_paddle.speed;}
                }
                if (right_paddle.y >= 0){
                    if(ball.y < (right_paddle.y+(right_paddle.height/2))) {right_paddle.y -= right_paddle.speed;}
                }
                if ((right_paddle.y+right_paddle.height) <= screenHeight){
                    if(ball.y > (right_paddle.y+(right_paddle.height/2))) {right_paddle.y += right_paddle.speed;}
                }
            }
            if (state == Player_2)
            {
                if (left_paddle.y >= 0){
                    if(IsKeyDown(KEY_W)) {left_paddle.y -= left_paddle.speed;}
                }
                if ((left_paddle.y+left_paddle.height) <= screenHeight){
                    if(IsKeyDown(KEY_S)) {left_paddle.y += left_paddle.speed;}
                }
                if (right_paddle.y >= 0){
                    if(IsKeyDown(KEY_UP)) {right_paddle.y -= right_paddle.speed;}
                }
                if ((right_paddle.y+right_paddle.height) <= screenHeight){
                    if(IsKeyDown(KEY_DOWN)) {right_paddle.y += right_paddle.speed;}
                }
            }
            ball.update();

            if (CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.radius, left_paddle.get_rect()))
            {
                if (ball.x > (left_paddle.x+left_paddle.width)) {ball.speedX *= -1;}
                else{ball.speedY *= -1;}
                collisions++;
            }
            if (CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.radius, right_paddle.get_rect()))
            {
                if (ball.x < right_paddle.x) {ball.speedX *= -1;}
                else{ball.speedY *= -1;}
                collisions++;
            }

            if (ball.x < 0)
            {
                score_P2++;
                ball.reset();
            }
            if (ball.x > screenWidth)
            {
                score_P1++;
                ball.reset();
            }

            DrawText("P1 score: ",25,5,20,RED);
            DrawText((std::to_string(score_P1)).c_str(),120,5,20,RED);
            DrawText("P2 score: ",650,5,20,RED);
            DrawText((std::to_string(score_P2)).c_str(),751,5,20,RED);
            
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