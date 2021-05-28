#include "Map.h"
#include "TextureManager.h"
#include "Game.h"

int lvl1[16][20] = // Nested array for map
{   
    { 0, 13, 13,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    { 0, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 11,  0,  0,  0,  0, 13, 13,  0},
    { 0, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  9, 13, 13, 13,  0},
    { 0, 13, 13,  0,  0, 13, 13, 13, 10,  9, 13, 13, 13, 13, 13,  1, 13, 13,  0,  0},
    { 0, 13, 13, 15,  0, 13, 13, 16, 16, 18, 13, 13,  1, 13, 13,  1, 13, 13,  0,  0},
    { 0, 13, 13,  0, 12, 13, 13, 16, 16,  0, 13, 13,  1, 13, 13,  6, 13, 13, 13,  0},
    { 0, 13, 13, 13, 13, 13, 13,  5,  7, 13, 13, 13,  1, 13, 13, 13, 13, 13, 13,  0},
    { 0, 13, 13, 13, 13, 13, 13,  1,  1, 13, 13, 13, 13, 13, 13, 13, 13, 13,  0,  0},
    { 0, 13, 13,  0,  8, 14,  4,  0,  0, 13, 13, 13, 10, 10, 13, 13, 13, 13, 15,  0},
    { 0, 13, 13,  2, 14,  5, 14,  7,  0, 13, 13,  1, 17, 17, 13, 13, 13, 13,  0,  0},
    { 0, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  1, 17, 17, 13, 13, 13, 13,  0,  0},
    { 0, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  1, 17, 17, 13, 13, 11, 11, 11,  0},
    { 0, 13,  6,  6,  1, 10, 11,  8,  9, 15,  1,  1,  1,  1, 13, 13, 13, 13, 13,  0},
    { 0, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  0},
    { 0, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  1,  1,  1,  1},
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
};

Map::Map()
{
    // loading all the pictures from the assets folder
    grass = TextureManager::LoadTexture("assets/g1.jpg");
    grass2 = TextureManager::LoadTexture("assets/g2.jpg");
    path = TextureManager::LoadTexture("assets/p1.png");
    path2 = TextureManager::LoadTexture("assets/p2.jpg");
    field = TextureManager::LoadTexture("assets/field.jpg");
    water = TextureManager::LoadTexture("assets/water.jpg");
    cupcake = TextureManager::LoadTexture("assets/c.png");
    tree = TextureManager::LoadTexture("assets/tree.png");
    Fwheel = TextureManager::LoadTexture("assets/Fwheel.png");
    hen = TextureManager::LoadTexture("assets/hen.png");
    motel = TextureManager::LoadTexture("assets/motel.png");
    school = TextureManager::LoadTexture("assets/school.png");
    hospital = TextureManager::LoadTexture("assets/hospital.png");
    shop = TextureManager::LoadTexture("assets/shop.png");
    cafe = TextureManager::LoadTexture("assets/cafe.png");
    mosque = TextureManager::LoadTexture("assets/mosque.png");
    b1 = TextureManager::LoadTexture("assets/b1.png");
    b2 = TextureManager::LoadTexture("assets/b2.png");
    b3 = TextureManager::LoadTexture("assets/b3.png");
    b4 = TextureManager::LoadTexture("assets/b4.png");

    Map::LoadMap(lvl1);

    src.x = src.y = 0; //starts at 0,0
    src.w = dest.w = 40; //width
    src.h = dest.h = 40; //height
}

Map::~Map()
{
    SDL_DestroyTexture(grass);
    SDL_DestroyTexture(grass2);
    SDL_DestroyTexture(path);
    SDL_DestroyTexture(path2);
    SDL_DestroyTexture(field);
    SDL_DestroyTexture(water);
    SDL_DestroyTexture(cupcake);
    SDL_DestroyTexture(tree);
    SDL_DestroyTexture(Fwheel);
    SDL_DestroyTexture(hen);
    SDL_DestroyTexture(motel);
    SDL_DestroyTexture(school);
    SDL_DestroyTexture(hospital);
    SDL_DestroyTexture(shop);
    SDL_DestroyTexture(cafe);
    SDL_DestroyTexture(mosque);
    SDL_DestroyTexture(b1);
    SDL_DestroyTexture(b2);
    SDL_DestroyTexture(b3);
    SDL_DestroyTexture(b4);
}

void Map::LoadMap(int arr[16][20])
{
    for (int row = 0; row < 16; row++)
    {
        for (int col = 0; col < 20; col++)
        {
            map[row][col] = arr[row][col];
            if (map[row][col] != 13)
            {
                // If a tile is not a path then add a collider to that tile.
                Game::addTiles(map[row][col], col * 40, row * 40);
            }
        }
    }
}

void Map::DrawMap() //assignment of our textures to numbers so that we can create our map by placing textures in matrix in form of integers
{
    int type = 0;
    for (int row = 0; row < 16; row++)
    {
        for (int col = 0; col < 20; col++)
        {
            type = map[row][col];

            dest.x = col * 40; //for each increment in column,(for eg when row=0 and col=1 texture will move 40 pixels across
            dest.y = row * 40;
            switch (type)
            {
            case 0:
                TextureManager::Draw(grass, src, dest);
                break;
            case 1:
                TextureManager::Draw(tree, src, dest);
                break;
            case 2:
                TextureManager::Draw(motel, src, dest);
                break;
            case 3:
                TextureManager::Draw(cupcake, src, dest);
                break;
            case 4:
                TextureManager::Draw(school, src, dest);
                break;
            case 5:
                TextureManager::Draw(hospital, src, dest);
                break;
            case 6:
                TextureManager::Draw(shop, src, dest);
                break;
            case 7:
                TextureManager::Draw(cafe, src, dest);
                break;
            case 8:
                TextureManager::Draw(mosque, src, dest);
                break;
            case 9:
                TextureManager::Draw(b1, src, dest);
                break;
            case 10:
                TextureManager::Draw(b2, src, dest);
                break;
            case 11:
                TextureManager::Draw(b3, src, dest);
                break;
            case 12:
                TextureManager::Draw(Fwheel, src, dest);
                break;
            case 13:
                TextureManager::Draw(path, src, dest);
                break;
            case 14:
                TextureManager::Draw(path2, src, dest);
                break;
            case 15:
                TextureManager::Draw(b4, src, dest);
                break;
            case 16:
                TextureManager::Draw(field, src, dest);
                break;
            case 17:
                TextureManager::Draw(water, src, dest);
                break;
            case 18:
                TextureManager::Draw(hen, src, dest);
                break;
            default:
                break;
            }
        }
    }
}