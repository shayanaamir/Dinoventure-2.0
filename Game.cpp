#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
GameObject* Player;
Map *map;

SDL_Renderer *Game::renderer = nullptr;


// SDL_Texture *ppp;
// SDL_Rect sss, ddd;
// Useless Constructors
Game::Game()
{}
Game::~Game()
{}

// Initializes the Screen. Not a Default constructor. Needs to be called for
// Screen to be made.
void Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING)==0)
    {
        std::cout << "Everything Initialized..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);

        if (window)
        {
            std::cout << "window Created!" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "renderer Created!" << std::endl;
        }
        isRunning = true;
    }
    else
    {
        isRunning = false;
    }
    Player = new GameObject("assets/small_image.jpeg", 0, 0, 5);
    map = new Map();

    // ppp = TextureManager::LoadTexture("assets/small_image.jpeg", renderer);
}

// Handling of Events here. Each and Every event, including key
// presses is handeled here. Using a switch method is more efficient.
void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        switch( event.key.keysym.sym )
        {
        case SDLK_LEFT:
            Player->Move(-1,0);
            break;
        case SDLK_RIGHT:
            Player->Move(1,0);
            break;
        case SDLK_UP:
            Player->Move(0,-1);
            break;
        case SDLK_DOWN:
            Player->Move(0,1);
            break;
        case SDLK_a:
            Player->Move(-1,0);
            break;
        case SDLK_d:
            Player->Move(1,0);
            break;
        case SDLK_w:
            Player->Move(0,-1);
            break;
        case SDLK_s:
            Player->Move(0,1);
            break;
        default:
            break;
        }
    default:
        break;
    }
}

// Renderes everything that need to be drawn. Called After Update function in main.cpp
void Game::render()
{
	SDL_RenderClear(renderer);
    //Add textures to be rendered
    map->DrawMap();
    Player->Render();
    // SDL_RenderCopy(renderer, ppp, NULL, &ddd);
    SDL_RenderPresent(renderer);
}

// Objects Updated here
void Game::update()
{
    Player->Update();
    // ddd.h = 64;
    // ddd.w = 64;
}

// Called at the end when window and renderer need to be destroyed.
void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned!" << std::endl;
}