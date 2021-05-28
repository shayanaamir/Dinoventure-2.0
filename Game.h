#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
// Game class with all variables
// Handles game events and updates the Screen
class ColliderComponent;

class Game
{
public:

    Game(); // ctor (construct game object)
    ~Game(); // dtor (destruct game object when closing)

    void init(const char* title, int xpos, int ypos, int width, int height, int flags); // method for intitializing the game
    void render();
    void update(); // keeps updating the objects
    void handleEvents(); // pause, restart, play. isrunning is also used here for quit game
    void clean(); // freeing all memory
    void addPhysics(); // Used to initialize all objects in game i.e. player, cupcake etc.
    void Restart(); // restsrt game by resetting all values

    bool loadMedia(); // loading the music
    void music(); // plays the music if it is not already playing

    bool running() { return isRunning; } // this fn lets main fn know whether or not the game is still running

    static void addTiles(int id, int x, int y);
    static void AddComponents();
    static SDL_Renderer* renderer;
    static SDL_Event event;
    static std::vector<ColliderComponent *> colliders;

private: // initializing some attributes
    // for bground music and SFX 
    Mix_Music *bgMusic = nullptr; 
    Mix_Chunk *coinSFX = nullptr;
    Mix_Chunk *gameOverSFX = nullptr;
    Mix_Chunk *winSFX = nullptr;
    Mix_Chunk *cupSFX = nullptr;
    Mix_Chunk *ouchSFX = nullptr;
    
    // for different state screens, lives 
    SDL_Texture *pTexture;
    SDL_Texture *startTexture; 
    SDL_Texture *overTexture;
    SDL_Texture *winTexture;
    SDL_Texture *heartTexture;
    SDL_Rect src, dest;

    SDL_Window* window; //SDL_window type window pointer
    bool getcake; // flag keep track of whether cake picked
    bool isRunning; // flag for quit game
    bool projectile; 
    bool paused; // flag for pausing game
    bool gamestart; // flag for start screen
    bool gameover; // flag for game over screen
    bool gamewon; // flag for winning screen
    int count = 0;
    int coins = 2;
    bool c1, c2, c3; // flag to keep track if coin is picked

    int c1rand, c2rand, c3rand, numb;
};