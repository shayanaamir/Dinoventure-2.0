#include "Game.h"

/* Note That in order to compile the game "g++ *.cpp"
command will not work since we are using SDL. So in order
to tackle this copy and paste the below command in Terminal:
g++ *.cpp -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

*/

// our Game object
Game* game = nullptr;

// Main function calling necessary functions.
int main(int argc, char* argv[])
{
    // Defining the Frame Rate and making the game run more smoothly
    const int FrameRate = 60;
    const int FrameDelay = 1000 / FrameRate;
    Uint32 FrameStart;
    int FrameTime;

    // Creating a new game object, initializing it and making sure
    // that the game runs in a loop and handling all game updates
    // and renderes
    game = new Game();
    game->init("Chapter 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, 0);

    // Main game loop handles all Game events and Updates the Screen
    while(game->running())
    {
        FrameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        FrameTime = SDL_GetTicks() - FrameStart;
        // Handles the Frame Rate of The game such that it can dip below 60 but
        // Not exceed 60
        if (FrameDelay > FrameTime)
        {
            SDL_Delay(FrameDelay - FrameTime);
        }
    }
    // End of the Game when peron presses the Exit window button
    game->clean();
    return 0;
}