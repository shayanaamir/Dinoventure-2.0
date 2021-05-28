#include "Game.h"
#include "TextureManager.h"
#include "Components.h"
#include "Map.h"
#include "Vector2D.h"
#include "Collision.h"
#include "ColliderComponent.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL_mixer.h>

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

Map *map;
Manager manager;

std::vector<ColliderComponent *> Game::colliders;
auto &cupcake(manager.addEntity());
auto &start(manager.addEntity());
auto &coin1(manager.addEntity());
auto &coin2(manager.addEntity());
auto &coin3(manager.addEntity());
auto &projectile1(manager.addEntity());
auto &projectile2(manager.addEntity());
auto &projectile3(manager.addEntity());
auto &projectile4(manager.addEntity());
auto &villager1(manager.addEntity());
auto &villager2(manager.addEntity());
auto &villager3(manager.addEntity());
auto &villager4(manager.addEntity());
auto &player(manager.addEntity());

// Useless Constructors/Dtor
Game::Game() // ctor
{}
Game::~Game() // dtor
{}

// Initializes the Screen. Not a Default constructor. Needs to be called for
// Screen to be made.
void Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING)==0) // then everything has been initialized successfully
    {
        std::cout << "Everything Initialized..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, 0); //creates window and details for our window

        if (window)         //if anything but zero, then window created
        {
            std::cout << "Window Created!" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);  //takes window which we created as first parameter, then index (of rendering driver to initialize) and flags (4 types of SDL flags which can be or'd, we have kept 0 flags)
        if (renderer) //if anything but zero, then renderer created
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  //first 3 (r,g,b = 255 = white colour), last 255 is max opaqueness
            std::cout << "Renderer Created!" << std::endl;
        }
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) >= 0 ) ///////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
			printf( "SDL_mixer initialized! SDL_mixer Error: %s\n", Mix_GetError() );		
		}
        // initializing bools
        isRunning = true;
        getcake = false;
        projectile = false;
        paused = gamestart = gameover = gamewon = false;
        c1 = false;
        c2 = false;
        c3 = false;

        src.x = src.y = dest.x = dest.y = 0;
        dest.w = src.w = 800;
        dest.h = src.h = 640;
        
        // loading all state screens and also life hearts
        startTexture = TextureManager::LoadTexture("assets/start.png");
        pTexture = TextureManager::LoadTexture("assets/paused.png");
        overTexture = TextureManager::LoadTexture("assets/game over 1.png");
        winTexture = TextureManager::LoadTexture("assets/winner.png");
        heartTexture = TextureManager::LoadTexture("assets/Heart.png");
        srand(time(0));
    }
    else // if everything was not initialized and window was not created or renderer was not created 
    // then game is not running
    {
        isRunning = false;
    }

    map = new Map();

    //ECS implementation
    // Add tiles and interactable objects to the map. i.e. the player, cupcake and other interactable objects.
    addPhysics();
}

// Resets all Game components.
void Game::Restart()
{
    // Reseting all positions of interactable enitites.
    cupcake.getComponent<TransformComponent>().position.x = (18.0*40.0);
    cupcake.getComponent<TransformComponent>().position.y = (12.0*40.0);
    villager1.getComponent<TransformComponent>().position.x = projectile1.getComponent<TransformComponent>().position.x = float(13 * 40);
    villager2.getComponent<TransformComponent>().position.x = projectile2.getComponent<TransformComponent>().position.x = float(8 * 40);
    villager3.getComponent<TransformComponent>().position.y = projectile3.getComponent<TransformComponent>().position.y = float(10 * 40);
    villager4.getComponent<TransformComponent>().position.y = projectile4.getComponent<TransformComponent>().position.y = float(13 * 40);
    projectile1.getComponent<TransformComponent>().position.y = projectile2.getComponent<TransformComponent>().position.y = 0.0f;
    projectile3.getComponent<TransformComponent>().position.x = projectile4.getComponent<TransformComponent>().position.x = 0.0f;
    player.getComponent<TransformComponent>().position.x = 42.0; // Starting x and y positions
    player.getComponent<TransformComponent>().position.y = 0.0;
    // Resetting all games conditions.
    isRunning = true;
    getcake = false;
    projectile = false;
    paused = gamestart = gameover = gamewon = false;
    
    c1 = false;
    c2 = false;
    c3 = false;
    coins = 2;
    count = 0;
    // Resetting all sprites
    cupcake.getComponent<SpriteComponent>().setTex("assets/c.png");
    villager1.getComponent<SpriteComponent>().setTex("assets/g1.jpg");
    villager2.getComponent<SpriteComponent>().setTex("assets/g1.jpg");
    villager3.getComponent<SpriteComponent>().setTex("assets/g1.jpg");
    villager4.getComponent<SpriteComponent>().setTex("assets/g1.jpg");
    projectile1.getComponent<SpriteComponent>().setTex("assets/g1.jpg");
    projectile2.getComponent<SpriteComponent>().setTex("assets/g1.jpg");
    projectile3.getComponent<SpriteComponent>().setTex("assets/g1.jpg");
    projectile4.getComponent<SpriteComponent>().setTex("assets/g1.jpg");
    coin1.getComponent<SpriteComponent>().setTex("p1.png");
    coin2.getComponent<SpriteComponent>().setTex("p1.png");
    coin3.getComponent<SpriteComponent>().setTex("p1.png");
    start.getComponent<SpriteComponent>().setTex("p1.png");
    // rewind music playback to the start
    Mix_ResumeMusic();
}

void Game::addPhysics()
{
    srand(time(0));
    //rand() % (max - min + 1) + min
    numb = (rand() % (13-12+1)) + 12;    
    int x = rand() % (18-14+1) + 14;
    cupcake.addComponent<TileComponent>(x*40, numb*40, 40, 40, 3);
    cupcake.addComponent<ColliderComponent>("Cake");

    start.addComponent<TileComponent>(40, 0, 40, 40, 13);
    start.addComponent<ColliderComponent>("Game");

    villager1.addComponent<TileComponent>(13*40, 0, 32, 32, 0);
    projectile1.addComponent<TileComponent>(13*40, 0, 32, 32, 0);
    projectile1.addComponent<ColliderComponent>("Rock1");

    villager2.addComponent<TileComponent>(8*40, 0, 32, 32, 0);
    projectile2.addComponent<TileComponent>(8*40, 0, 32, 32, 0);
    projectile2.addComponent<ColliderComponent>("Rock2");

    villager3.addComponent<TileComponent>(0, 10*40, 32, 32, 0);
    projectile3.addComponent<TileComponent>(0, 10*40, 32, 32, 0);
    projectile3.addComponent<ColliderComponent>("Rock3");

    villager4.addComponent<TileComponent>(0, 13*40, 32, 32, 0);
    projectile4.addComponent<TileComponent>(0, 13*40, 32, 32, 0);
    projectile4.addComponent<ColliderComponent>("Rock4");

    // randomizing coin location to an extent
    c1rand = (rand() % 10) + 1;
    coin1.addComponent<TileComponent>(c1rand*40, 10*40, 40, 40, 13);
    coin1.addComponent<ColliderComponent>("Coin1");

    c2rand = (rand() % 2) + 1;
    coin2.addComponent<TileComponent>(18*40, c2rand*40, 40, 40, 13);
    coin2.addComponent<ColliderComponent>("Coin2");

    c3rand = (rand() % 15) + 1;
    coin3.addComponent<TileComponent>(c3rand*40, 14*40, 40, 40, 13);
    coin3.addComponent<ColliderComponent>("Coin3");

    player.addComponent<TransformComponent>(42, 0, 32, 32, 1); // Starting x and y positions 
    player.addComponent<SpriteComponent>("assets/dino_all.png", true);
    player.addComponent<KeyboardContoller>();
    player.addComponent<ColliderComponent>("player");
}

bool Game::loadMedia()  // loading all music files
{
    bool success = true;
	bgMusic = Mix_LoadMUS( "sounds/background.wav" );
    coinSFX = Mix_LoadWAV( "sounds/success.wav" );
    winSFX = Mix_LoadWAV( "sounds/win.wav" );
    gameOverSFX = Mix_LoadWAV( "sounds/gameover.wav" );
    cupSFX= Mix_LoadWAV( "sounds/cupcake.wav" );
    ouchSFX= Mix_LoadWAV( "sounds/oof.wav" );
	if(bgMusic == NULL){
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}
    if(coinSFX == NULL){
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}
    if(gameOverSFX == NULL){
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}
    if(winSFX == NULL){
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}
    if(cupSFX == NULL){
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}
    if(ouchSFX == NULL){
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}
	return success;
}

void Game::music() // called in main.cpp to play music
{
    if( Mix_PlayingMusic() == 0 ) // Tells you if music is actively playing,
	{
		//Play the music
		Mix_PlayMusic( bgMusic, 2 );
	}
}

// Handling of Events here. Each and Every event, including key
// presses is handeled here. Using a switch method is more efficient.
void Game::handleEvents()
{
    SDL_PollEvent(&event); // passing reference of the event. ie. its location
    switch (event.type) // this switch case finds the type of the event and tales actions accordingly
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
    if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_p:
                std::cout << "paused!!" << std::endl;
                paused = true;	
                // pause music playback
                Mix_PauseMusic();
                break;
            case SDLK_SPACE:
                paused = false;
                // resume music playback
                Mix_ResumeMusic();
                break;
            case SDLK_RETURN:
                // Functionality of Enter changes according to screen so checks
                // if screen is start, win/lose and gives enter that functionality.
                if (gamestart == false) 
                {
                    gamestart = true;
                }
                else if ((gamewon == false && gameover == true)||(gameover==false && gamewon == true))
                {
                    Restart();
                    std::cout << "Game Restart!" << std::endl;
                }
                break;
            case SDLK_ESCAPE: // quit game
                if (gamestart == false || gameover == true || gamewon == true || paused == true)
                {
                    isRunning = false;
                }
                break;
            default:
                break;
            }
        }
}

// Renders everything onto the screen that needs to be drawn. Called After Update function in main.cpp
void Game::render()
{
	SDL_RenderClear(renderer);  //cleans screen
    //Add textures to be rendered
    src.w = dest.w = 800;
    src.h = dest.h = 640;
    dest.x = dest.y = 0;
    // Draws the start pause or win/lose screens according to the conditions.
    if (paused)
    {
        TextureManager::Draw(pTexture, src, dest);
    }
    else if (gamestart == false)
    {
        TextureManager::Draw(startTexture, src, dest);
    }
    
    else if (gameover)
    {
        TextureManager::Draw(overTexture, src, dest);
    }
    else if (gamewon)
    {
        TextureManager::Draw(winTexture, src, dest);
    }
    else
    {
     // Renders the entire map 60 frames every second.
    map->DrawMap();
    for (int i = 0; i <= coins; i++)
    {
        src.w = src.h = dest.w = dest.h = 40;
        src.x = src.y = 0;
        dest.x = (14 + i ) * 40;
        dest.y = 15 * 40;
        TextureManager::Draw(heartTexture, src, dest);
    }
     // Draws all entities present in the entity manager. Includes Projectiles, Villagers, Player and other interactable assets.
    manager.draw();
    }
    SDL_RenderPresent(renderer);
}

// Objects Updated here
void Game::update()
{
    // refreshing and updating the manager allows to refresh the x y position of every entity
    // and hence allows us to check if objects are interacting.

    // Check the Players position before any updates, like pressing keys.
    if (paused != true && gamestart == true && gamewon==false && gameover == false)
    {
    Vector2D pos = player.getComponent<TransformComponent>().position;
    manager.refresh();
    manager.update();
    // Checking if player out of bounds.
    float xpos, ypos;
    xpos = player.getComponent<TransformComponent>().position.x;
    ypos = player.getComponent<TransformComponent>().position.y;
    if (xpos <= 0 || xpos >= 800 || ypos <= 0 || ypos >= 640)
    {
        player.getComponent<TransformComponent>().position = pos;
    }
    // Transverses all colliders, meaning all entities that are collidable.
    for (auto cc : colliders)
    {
    bool x = Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
    if (x)
    {
        if (cc->tag != "player" && cc->tag != "Game" && cc->tag != "Cake" && cc->tag != "Coin1" && cc->tag != "Coin2" && cc->tag != "Coin3")
        {
            // if the player collides with an object then set his position to the previous position before collision.
            player.getComponent<TransformComponent>().position = pos;
        }
        else
        {
            continue;
        }
        
    }
    }
    // check if the player has acquired the cupcake. If he has set up the flags for the coins and
    // enable all physics for the objects.
    if (Collision::AABB(player.getComponent<ColliderComponent>(), cupcake.getComponent<ColliderComponent>()))
    {
        getcake = true;
        Mix_PlayChannel(-1, cupSFX, 0); // cupcake picked sfx
        cupcake.getComponent<SpriteComponent>().setTex("assets/p1.png"); // remove cupcake
        start.getComponent<SpriteComponent>().setTex("assets/End.jpg"); // display end tile
        // display the rocks
        projectile1.getComponent<SpriteComponent>().setTex("assets/rock.png"); 
        projectile2.getComponent<SpriteComponent>().setTex("assets/rock.png");
        projectile3.getComponent<SpriteComponent>().setTex("assets/rock.png");
        projectile4.getComponent<SpriteComponent>().setTex("assets/rock.png");
        // display 4 villagers
        villager1.getComponent<SpriteComponent>().setTex("assets/ppl1.png");
        villager2.getComponent<SpriteComponent>().setTex("assets/ppl2.png");
        villager3.getComponent<SpriteComponent>().setTex("assets/ppl1.png");
        villager4.getComponent<SpriteComponent>().setTex("assets/ppl2.png");
        c1 = true;
        c2 = true;
        c3 = true;
        // display the 3 coins
        coin1.getComponent<SpriteComponent>().setTex("assets/coin.png");
        coin2.getComponent<SpriteComponent>().setTex("assets/coin.png");
        coin3.getComponent<SpriteComponent>().setTex("assets/coin.png");

        // rock movement
        projectile = true;
        srand(time(0));
        projectile1.getComponent<TransformComponent>().speed = rand() % 4 + 3;
        projectile2.getComponent<TransformComponent>().speed = rand() % 4 + 3;
        projectile3.getComponent<TransformComponent>().speed = rand() % 4 + 3;
        projectile4.getComponent<TransformComponent>().speed = rand() % 4 + 3;
    }
    // Check if the player has acquired any coins. Update coins if necessary.
    if ((c1==true || c2==true || c3==true) && getcake == true)
    {
        if (c1)
        {
            if (Collision::AABB(player.getComponent<ColliderComponent>(), coin1.getComponent<ColliderComponent>()))
            {
                c1 = false;
                coins++;
                Mix_PlayChannel( -1, coinSFX, 0 ); /////////////////////////////////////////////////////////////////////////////////////////////////////////////
                coin1.getComponent<SpriteComponent>().setTex("assets/p1.png");
            }
        }
        if (c2)
        {
            if (Collision::AABB(player.getComponent<ColliderComponent>(), coin2.getComponent<ColliderComponent>()))
            {
                c2 = false;
                coins++;
                Mix_PlayChannel( -1, coinSFX, 0 ); ////////////////////////////////////////////////////////////////////////////////////////////////////////////
                coin2.getComponent<SpriteComponent>().setTex("assets/p1.png");
            }
        }
        if (c3)
        {
            if (Collision::AABB(player.getComponent<ColliderComponent>(), coin3.getComponent<ColliderComponent>()))
            {
                c3 = false;
                coins++;
                Mix_PlayChannel( -1, coinSFX, 0 ); //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                coin3.getComponent<SpriteComponent>().setTex("assets/p1.png");
            }
        }
    }
    // Projectile physics. Updates if the projectile reaches the end of the screen.
    if (projectile==true)
    {
        projectile1.getComponent<TransformComponent>().position.y += projectile1.getComponent<TransformComponent>().speed;
        projectile2.getComponent<TransformComponent>().position.y += projectile2.getComponent<TransformComponent>().speed;
        projectile3.getComponent<TransformComponent>().position.x += projectile3.getComponent<TransformComponent>().speed;
        projectile4.getComponent<TransformComponent>().position.x += projectile4.getComponent<TransformComponent>().speed;
        if ((int)projectile1.getComponent<TransformComponent>().position.y >= 640)
        {
            projectile1.getComponent<TransformComponent>().position.y = 0.0;
            projectile1.getComponent<TransformComponent>().position.x = (float)(rand() % 640);
            villager1.getComponent<TransformComponent>().position.x = projectile1.getComponent<TransformComponent>().position.x;
        }
        if ((int)projectile2.getComponent<TransformComponent>().position.y >= 640)
        {
            projectile2.getComponent<TransformComponent>().position.y = 0.0;
            projectile2.getComponent<TransformComponent>().position.x = (float)(rand() % 640);
            villager2.getComponent<TransformComponent>().position.x = projectile2.getComponent<TransformComponent>().position.x;
        }
        if ((int)projectile3.getComponent<TransformComponent>().position.x >= 800)
        {
            projectile3.getComponent<TransformComponent>().position.x = 0.0;
            projectile3.getComponent<TransformComponent>().position.y = (float)(rand() % 640);
            villager3.getComponent<TransformComponent>().position.y = projectile3.getComponent<TransformComponent>().position.y;
        }
        if ((int)projectile4.getComponent<TransformComponent>().position.x >= 800)
        {
            projectile4.getComponent<TransformComponent>().position.x = 0.0;
            projectile4.getComponent<TransformComponent>().position.y = (float)(rand() % 640);
            villager4.getComponent<TransformComponent>().position.y = projectile4.getComponent<TransformComponent>().position.y;
        }
    }
    // Ending condition. If player has acquired the cake and reached the starting position.
    if (getcake == true && Collision::AABB(player.getComponent<ColliderComponent>(), start.getComponent<ColliderComponent>()))
    {
        Mix_PlayChannel(-1,winSFX,0); // win music
        Mix_PauseMusic(); // pause bgmusic
        gamewon = true; // game over screen
        std::cout << "Coins:" << coins << std::endl;
        std::cout << "Game Won!!" << std::endl;
    }
    // Checking if the player has been hit by a projectile. reduce the coins by 1 if the player has been hit.
    if (projectile == true && (Collision::AABB(player.getComponent<ColliderComponent>(), projectile1.getComponent<ColliderComponent>()) ||
    Collision::AABB(player.getComponent<ColliderComponent>(), projectile2.getComponent<ColliderComponent>()) || 
    Collision::AABB(player.getComponent<ColliderComponent>(), projectile3.getComponent<ColliderComponent>()) ||
    Collision::AABB(player.getComponent<ColliderComponent>(), projectile4.getComponent<ColliderComponent>())))
    {
        // clashing of rock and dino
        if (Collision::AABB(player.getComponent<ColliderComponent>(), projectile1.getComponent<ColliderComponent>()) && Game::coins != 0)
        {
            Mix_PlayChannel( -1, ouchSFX, 0 ); // rock thud
            projectile1.getComponent<TransformComponent>().position.y = 0.0;
            projectile1.getComponent<TransformComponent>().position.x = (float)(rand() % 640);
            villager1.getComponent<TransformComponent>().position.x = projectile1.getComponent<TransformComponent>().position.x;
            Game::coins--; // reduce life
        }
        else if (Collision::AABB(player.getComponent<ColliderComponent>(), projectile2.getComponent<ColliderComponent>()) && Game::coins != 0)
        {
            Mix_PlayChannel( -1, ouchSFX, 0 );
            projectile2.getComponent<TransformComponent>().position.y = 0.0;
            projectile2.getComponent<TransformComponent>().position.x = (float)(rand() % 640);
            villager2.getComponent<TransformComponent>().position.x = projectile2.getComponent<TransformComponent>().position.x;
            Game::coins--; 
        }
        else if (Collision::AABB(player.getComponent<ColliderComponent>(), projectile3.getComponent<ColliderComponent>()) && Game::coins != 0)
        {
            Mix_PlayChannel( -1, ouchSFX, 0 );
            projectile3.getComponent<TransformComponent>().position.x = 0.0;
            projectile3.getComponent<TransformComponent>().position.y = (float)(rand() % 640);
            villager3.getComponent<TransformComponent>().position.y = projectile3.getComponent<TransformComponent>().position.y;
            Game::coins--;
        }
        else if (Collision::AABB(player.getComponent<ColliderComponent>(), projectile4.getComponent<ColliderComponent>()) && Game::coins != 0)
        {
            Mix_PlayChannel( -1, ouchSFX, 0);
            projectile4.getComponent<TransformComponent>().position.x = 0.0;
            projectile4.getComponent<TransformComponent>().position.y = (float)(rand() % 640);
            villager4.getComponent<TransformComponent>().position.y = projectile4.getComponent<TransformComponent>().position.y;
            Game::coins--;
        }
        else
        {
            // If player has 0 coins then game over.
            Mix_PlayChannel( -1, gameOverSFX, 0 ); // game over sfx
            Mix_PauseMusic(); // pause bgmusic
            gameover = true; // gameover screen
            std::cout << "Game Over!!" << std::endl;
        }
        }
    }
}

// Called at the end when window and renderer need to be destroyed.
void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    // free music and sfx
    Mix_FreeMusic(bgMusic); 
    bgMusic = NULL;
    Mix_FreeChunk(coinSFX); 
    Mix_FreeChunk(winSFX); 
    Mix_FreeChunk(gameOverSFX); 
    Mix_FreeChunk(coinSFX); 
    Mix_FreeChunk(cupSFX);
    Mix_FreeChunk(ouchSFX);
    // setting back to nullptr
    gameOverSFX=NULL;
    ouchSFX=NULL;
    winSFX=NULL;
    coinSFX=NULL;
    cupSFX=NULL;
    Mix_Quit();

    SDL_Quit();
    
    std::cout << "Game Cleaned!" << std::endl;
}
// Adding colliders to the tiles in the map. To make them interactable.
void Game::addTiles(int id, int x, int y)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, 40, 40, 20);
    std::string tiles = "tile";
    tiles += std::to_string(y/40);
    tiles += "x";
    tiles += std::to_string(x/40);
    tile.addComponent<ColliderComponent>(tiles);
}