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

    // Initializing all variables for pictures
    SDL_Texture *path;   
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
    SDL_Texture *grass;
    SDL_Texture *path2;
    SDL_Texture *grass2;
    SDL_Texture *grass3;
    SDL_Texture *field;
    SDL_Texture *water;    
    SDL_Texture *hen;    

    int map[16][20]; // initializing a 2d array with 16 rows and 20 columns, holds the map
};