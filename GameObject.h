#pragma once
#include "Game.h"

class GameObject
{
    public:
        GameObject(const char *texturesheet, int x, int y, int Vel);
        ~GameObject();

        void Update();
        void Render();
        void Move(int xvel, int yvel);

    private:
        int xpos, ypos, Velocity;

        SDL_Texture *objTexture;
        SDL_Rect srcRect, destRect;
};