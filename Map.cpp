#include "Map.h"
#include "TextureManager.h"

int lvl1[16][20] = // Nested array for map
{   
    { 1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0, 13,  0,  0,  0,  0, 13, 13, 13,  0},
    { 1,  1,  1,  1, 13, 13, 13, 13, 13, 13, 13, 13, 11,  0,  0,  0,  0,  0, 13, 13},
    { 0,  0, 13,  0,  0,  0,  6, 13,  0,  0, 0 , 13,  0,  0,  0,  0,  9, 13, 13,  0},
    { 0, 15, 13,  0, 13, 13, 13, 13, 10,  0,  0, 13, 13, 13, 13,  0,  0, 13,  0,  0},
    { 0,  0, 13,  0,  0, 13,  0,  0,  0,  18,  0, 13,  0,  0, 13,  0,  0, 13,  0,  0},
    { 0,  0, 13,  0, 12, 13,  0, 16, 16,  0,  9, 13,  0,  0, 13,  0,  6, 13, 13,  0},
    { 0,  0, 13, 13, 13, 13,  0, 16, 16,  0,  0, 13,  0,  0, 13,  0,  0, 13,  0,  0},
    { 0, 13, 13,  0,  0,  0,  0,  0,  0,  0,  0, 13, 13, 13, 13, 13, 13, 13,  0,  0},
    { 0, 13,  0,  0,  8, 14,  4,  0,  0, 13, 13, 13,  0,  0,  0, 10,  0, 13, 15,  0},
    { 0, 13,  0,  2, 14,  5, 14,  7,  0, 13,  0,  0,  0, 17,  0,  0,  0, 13,  0,  0},
    { 0, 13,  0,  0,  0,  0,  0,  0,  0, 13, 13,  0,  0, 17,  0, 13, 13, 13,  0,  0},
    { 0, 13, 13, 13, 13, 13, 13, 13, 13, 13,  0,  0,  0, 17,  0, 13,  0,  0,  0,  0},
    {13, 13,  0,  0,  0,  0,  0,  0,  0, 15,  0, 13,  0,  0,  0, 13, 11,  0, 13,  0},
    {13,  0,  6,  0,  0, 10,  0,  0,  0,  0,  0, 13,  0,  0, 13, 13, 13, 13,  3,  0},
    {13, 13, 13, 13, 13, 13, 13,  0,  0, 13, 13, 13,  9, 13, 13,  0,  1,  1,  1,  1},
    { 0,  0,  0,  0,  0,  0, 13, 13, 13, 13,  0, 13, 13, 13,  0,  0,  1,  1,  1,  1}
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

    src.x = src.y = 0;
    src.w = dest.w = 40;
    src.h = dest.h = 40;
}

Map::~Map()
{}

void Map::LoadMap(int arr[16][20])
{
    for (int row = 0; row < 16; row++)
    {
        for (int col = 0; col < 20; col++)
        {
            map[row][col] = arr[row][col];
        }
    }
}

void Map::DrawMap()
{
    int type = 0;
    for (int row = 0; row < 16; row++)
    {
        for (int col = 0; col < 20; col++)
        {
            type = map[row][col];

            dest.x = col * 40;
            dest.y = row * 40;
            switch (type)
            {
            case 0:
                TextureManager::Draw(grass, src, dest);
                break;
            case 1:
                TextureManager::Draw(grass2, src, dest);
                TextureManager::Draw(tree, src, dest);
                break;
            case 2:
                TextureManager::Draw(path2, src, dest);
                TextureManager::Draw(motel, src, dest);
                break;
            case 3:
                TextureManager::Draw(path, src, dest);
                TextureManager::Draw(cupcake, src, dest);
                break;
            case 4:
                TextureManager::Draw(path2, src, dest);
                TextureManager::Draw(school, src, dest);
                break;
            case 5:
                TextureManager::Draw(path2, src, dest);
                TextureManager::Draw(hospital, src, dest);
                break;
            case 6:
                TextureManager::Draw(grass, src, dest);
                TextureManager::Draw(shop, src, dest);
                break;
            case 7:
                TextureManager::Draw(path2, src, dest);
                TextureManager::Draw(cafe, src, dest);
                break;
            case 8:
                TextureManager::Draw(path2, src, dest);
                TextureManager::Draw(mosque, src, dest);
                break;
            case 9:
                TextureManager::Draw(grass, src, dest);
                TextureManager::Draw(b1, src, dest);
                break;
            case 10:
                TextureManager::Draw(grass, src, dest);
                TextureManager::Draw(b2, src, dest);
                break;
            case 11:
                TextureManager::Draw(grass, src, dest);
                TextureManager::Draw(b3, src, dest);
                break;
            case 12:
                TextureManager::Draw(grass, src, dest);
                TextureManager::Draw(Fwheel, src, dest);
                break;
            case 13:
                TextureManager::Draw(path, src, dest);
                break;
            case 14:
                TextureManager::Draw(path2, src, dest);
                break;
            case 15:
                TextureManager::Draw(grass, src, dest);
                TextureManager::Draw(b4, src, dest);
                break;
            case 16:
                TextureManager::Draw(field, src, dest);
                break;
            case 17:
                TextureManager::Draw(water, src, dest);
                break;
            case 18:
                TextureManager::Draw(grass, src, dest);
                TextureManager::Draw(hen, src, dest);
                break;
            default:
                break;
            }
        }
    }
}