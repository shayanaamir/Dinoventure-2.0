#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

// Game class with all variables
// Handles game events and updates the Screen
class Game
{
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, int flags);
    void render();
    void update();
    void handleEvents();
    void clean();
    
    bool running() { return isRunning; }
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    int count = 0;
};