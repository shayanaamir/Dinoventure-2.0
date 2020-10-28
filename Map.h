#pragma once
#include "Game.h"

class Map
{
public:
    Map();
    ~Map();

    void LoadMap(int arr[16][20]);
    void DrawMap();

private:
    SDL_Rect src, dest;
    SDL_Texture *path;
    SDL_Texture *path1;    
    SDL_Texture *cupcake;
    SDL_Texture *motel;
    SDL_Texture *tree;
    SDL_Texture *school;
    SDL_Texture *hospital;
    SDL_Texture *shop;
    SDL_Texture *cafe;
    SDL_Texture *mosque;
    SDL_Texture *b1;
    SDL_Texture *b2;
    SDL_Texture *b3;
    SDL_Texture *b4;
    SDL_Texture *Fwheel;
    SDL_Texture *water;

    int map[16][20];
};