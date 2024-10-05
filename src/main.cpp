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
    bool moved1 = false;
    bool moved2 = false;
    bool Pause;
    bool sound = true;
    bool sfx = true;

    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(60);
    InitAudioDevice();
    Music music = LoadMusicStream("bg-music.mp3");
    PlayMusicStream(music);
    Sound hit = LoadSound("hit.wav");
    SetSoundVolume(hit, 0.6);
    Sound score = LoadSound("score.wav");
    SetSoundPan(score, 1);
    SetSoundVolume(score, 0.5);
    Sound respawn = LoadSound("respawn.wav");

    SetExitKey(NULL);
    set_gui();

    state = Main_Menu;
    
    unsigned char a = 240;
    int b = 2;
    int c = 15;
    bool reset = false;

    while (!WindowShouldClose())
    {
        if (sound) {UpdateMusicStream(music);}
        if(state == Main_Menu){
            DrawText("Pong", 340,40, 50, BLACK);
            score_P1 = 0;
            score_P2 = 0;
            Pause = false;
            ball.collisions = 0;
            left_paddle.y = (screenHeight/2) - (left_paddle.height/2);
            right_paddle.y = (screenHeight/2) - (right_paddle.height/2);
            ball.reset();
            if(a<25 || a>243){
                b *= -1;
            }
            a += b;
            DrawRectangleGradientH(0,0,40,screenHeight,Color{a,a,a,255},RAYWHITE);
            DrawRectangleGradientH(screenWidth-40,0,40,screenHeight,RAYWHITE,Color{a,a,a,255});

            if(GuiButton({350,150,100,50},"1 Player")) {state = Player_1; a = 245;}
            if(GuiButton({350,250,100,50},"2 Player")) {state = Player_2; a = 245;}
            DrawCircle(366,345,22,DARKGRAY);
            DrawCircle(366,345,20,LIGHTGRAY);
            GuiDrawIcon(122,351,329,2,DARKGRAY);
            DrawCircle(435,345,22,DARKGRAY);
            DrawCircle(435,345,20,LIGHTGRAY);
            GuiDrawIcon(123,420,329,2,DARKGRAY);
            if (!sound) {DrawLineEx(Vector2{351,330},Vector2{381,360},2,DARKGRAY);}
            if (!sfx) {DrawLineEx(Vector2{420,330},Vector2{450,360},2,DARKGRAY);}
            
            if (IsMouseButtonPressed(0))
            {
                Vector2 mousepos = GetMousePosition();
                if (CheckCollisionPointCircle(mousepos,Vector2{366,345},20))
                {
                    sound = !sound;
                }
                if (CheckCollisionPointCircle(mousepos,Vector2{435,345},20))
                {
                    sfx = !sfx;
                }
            }
        }
        else{
            if (IsKeyPressed(KEY_ESCAPE)) {Pause = !Pause;}
            if (!Pause)
            {
                
                if (state == Player_1)
                {
                    if (!moved1){
                        DrawText("W & S or arrow keys", 50, 150, 20, GRAY);
                    }
                    
                    if (left_paddle.y >= 0){
                        if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {left_paddle.y -= left_paddle.speed;
                        moved1 = true;}
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
                    if (!moved1){
                        DrawText("W & S", 50, 150, 20, GRAY);
                    }
                    if (!moved2){
                        DrawText("Arrow keys", screenWidth-50-MeasureText("Arrow keys",20), 150, 20, GRAY);
                    }
                    
                    if (left_paddle.y >= 0){
                        if(IsKeyDown(KEY_W)) {left_paddle.y -= left_paddle.speed;
                        moved1 = true;}
                    }
                    if ((left_paddle.y+left_paddle.height) <= screenHeight){
                        if(IsKeyDown(KEY_S)) {left_paddle.y += left_paddle.speed;}
                    }
                    if (right_paddle.y >= 0){
                        if(IsKeyDown(KEY_UP)) {right_paddle.y -= right_paddle.speed;
                        moved2 = true;}
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
                    if(sfx) {PlaySound(hit);}
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
                    if(sfx) {PlaySound(hit);}
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
                            if(sfx) {PlaySound(score);}
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
                            if(sfx) {PlaySound(respawn);}
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
                            if(sfx) {PlaySound(score);}
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
                            if(sfx) {PlaySound(respawn);}
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
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);
            left_paddle.draw();
            right_paddle.draw();
            ball.draw();
            if (state != Main_Menu)
            {
                DrawLine(screenWidth/2,0, screenWidth/2,screenHeight,BLACK);
                DrawCircleLines(screenWidth/2, screenHeight/2, 50, BLACK);
            }
            if (Pause)
            {
                DrawRectangle(0,0,screenWidth,screenHeight, Color{255,255,255,150});
                if(GuiButton({350,100,100,40},"Main menu")) {state = Main_Menu; a = 240;}
                if(GuiButton({350,165,100,40},"Continue")) {Pause = false;}
                DrawCircle(366,250,22,DARKGRAY);
                DrawCircle(366,250,20,LIGHTGRAY);
                GuiDrawIcon(122,351,234,2,DARKGRAY);
                DrawCircle(435,250,22,DARKGRAY);
                DrawCircle(435,250,20,LIGHTGRAY);
                GuiDrawIcon(123,420,234,2,DARKGRAY);
                if (!sound) {DrawLineEx(Vector2{351,235},Vector2{381,265},2,DARKGRAY);}
                if (!sfx) {DrawLineEx(Vector2{420,235},Vector2{450,265},2,DARKGRAY);}
                if (IsMouseButtonPressed(0))
                {
                    Vector2 mousepos = GetMousePosition();
                    if (CheckCollisionPointCircle(mousepos,Vector2{366,250},20))
                    {
                        sound = !sound;
                    }
                    if (CheckCollisionPointCircle(mousepos,Vector2{435,250},20))
                    {
                        sfx = !sfx;
                    }
                }
            }

        EndDrawing();
    }

    UnloadMusicStream(music);
    UnloadSound(hit);
    UnloadSound(score);
    UnloadSound(respawn);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}