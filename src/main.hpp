#define RAYGUI_IMPLEMENTATION
#include <iostream>
#include "raylib.h"
#include "raygui.h"

const int screenWidth = 800;
const int screenHeight = 450;

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
    float r;
    Color color = BLACK;
    float speedX;
    float speedY;
    int collisions;
public:
    void draw(){DrawCircle(x, y, radius, color);}
    void reset(){
        x = screenWidth/2;
        y = screenHeight/2;
        speedX = GetRandomValue(2,5);
        speedY = GetRandomValue(1,4);
        if(GetRandomValue(-5,5) < 0) {speedX *= -1;}
        if(GetRandomValue(-5,5) < 0) {speedY *= -1;}
        r = radius*4;
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

void set_gui(){
    GuiSetStyle(BUTTON, BORDER_WIDTH, 3);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, 0x2c2c2cff);
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, 0x848484ff);
    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, 0x181818ff);
    GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, 0x3f3f3fff);
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, 0xf6f6f6ff);
    GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, 0x414141ff);
}