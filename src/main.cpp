#include "main.hpp"

int score_P1;
int score_P2;

enum State{
    Main_Menu = 0,
    Player_1 = 1,
    Player_2 = 2
}state;

int main(void)
{
    Paddle left_paddle; left_paddle.x = 10;
    Paddle right_paddle; right_paddle.x = (screenWidth-10-right_paddle.width);    
    Ball ball; 
    ball.reset();

    InitWindow(screenWidth, screenHeight, "Ping Pong");
    SetTargetFPS(60);
    set_gui();

    state = Main_Menu;
    
    unsigned char a = 240;
    int b = 2;
    int c = 15;
    bool reset = false;

    while (!WindowShouldClose())
    {
        if(state == Main_Menu){
            DrawText("Pong", 350,30, 40, BLACK);
            score_P1 = 0;
            score_P2 = 0;
            ball.collisions = 0;
            if(a<25 || a>243){
                b *= -1;
            }
            a += b;
            DrawRectangleGradientH(0,0,40,screenHeight,Color{a,a,a,255},RAYWHITE);
            DrawRectangleGradientH(screenWidth-40,0,40,screenHeight,RAYWHITE,Color{a,a,a,255});

            if(GuiButton({350,150,100,50},"1 Player")) {state = Player_1; a = 245;}
            if(GuiButton({350,250,100,50},"2 Player")) {state = Player_2; a = 245;}
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
                if (ball.x > (left_paddle.x+left_paddle.width))
                {
                    ball.x = left_paddle.x+left_paddle.width+ball.radius;
                    ball.speedX *= -1;
                }
                else{ball.speedY *= -1;}
                ball.collisions++;
            }
            if (CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.radius, right_paddle.get_rect()))
            {
                if (ball.x < right_paddle.x)
                {
                    ball.x = right_paddle.x-ball.radius;
                    ball.speedX *= -1;
                }
                else{ball.speedY *= -1;}
                ball.collisions++;
            }

            if (ball.x < 0)
            {
                if (!reset){
                    if (a>240)
                    {
                        a = 240;
                        c =10;
                        score_P2++;
                    }
                    if (a<25)
                    {
                        c *= -1;
                    }
                    a -= c;
                    if(a>240){
                        a = 245;
                        reset = true;
                    }
                    DrawRectangleGradientH(0,0,25,screenHeight,Color{a,a,a,255},RAYWHITE);
                }
                if (reset)
                {
                    if (ball.r > ball.radius)
                    {
                        DrawCircleGradient(screenWidth/2, screenHeight/2, ball.r, ball.color, RAYWHITE);
                        DrawCircle(screenWidth/2, screenHeight/2, ball.radius, ball.color);
                        ball.r -= 1.5;
                    }else{
                        ball.reset();
                        reset = false;
                    }
                }
            }
            if (ball.x > screenWidth)
            {
                if (!reset)
                {
                    if (a>240)
                    {
                        a = 240;
                        c =10;
                        score_P1++;
                    }
                    if (a<25)
                    {
                        c *= -1;
                    }
                    a -= c;
                    if(a>240){
                        a = 245;
                        reset = true;
                    } 
                    DrawRectangleGradientH(screenWidth-25,0,25,screenHeight,RAYWHITE,Color{a,a,a,255});
                }
                if (reset)
                {
                    if (ball.r > ball.radius)
                    {
                        DrawCircleGradient(screenWidth/2, screenHeight/2, ball.r, ball.color, RAYWHITE);
                        DrawCircle(screenWidth/2, screenHeight/2, ball.radius, ball.color);
                        ball.r -= 1.5;
                    }else{
                        ball.reset();
                        reset = false;
                        }
                }
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