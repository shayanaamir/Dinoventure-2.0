#include "Map.h"
#include "TextureManager.h"

int lvl1[16][20] =
{   {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 2, 0, 0, 3, 0, 0, 4, 0, 0, 5, 0, 0, 6, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 11, 0, 0, 10, 0, 0, 9, 0, 0, 8, 0, 0, 7, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}
};

Map::Map()
{
    water = TextureManager::LoadTexture("assets/water.png");
    cupcake = TextureManager::LoadTexture("assets/c.png");
    motel = TextureManager::LoadTexture("assets/motel.png");
    tree = TextureManager::LoadTexture("assets/tree.png");
    school = TextureManager::LoadTexture("assets/school.png");
    hospital = TextureManager::LoadTexture("assets/hospital.png");
    shop = TextureManager::LoadTexture("assets/shop.png");
    cafe = TextureManager::LoadTexture("assets/cafe.png");
    mosque = TextureManager::LoadTexture("assets/mosque.png");
    b1 = TextureManager::LoadTexture("assets/b1.png");
    b2 = TextureManager::LoadTexture("assets/b2.png");
    b3 = TextureManager::LoadTexture("assets/b3.png");
    b4 = TextureManager::LoadTexture("assets/b4.png");
    Fwheel = TextureManager::LoadTexture("assets/Fwheel.png");
    path = TextureManager::LoadTexture("assets/path1.png");
    path1 = TextureManager::LoadTexture("assets/path2.png");

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
                TextureManager::Draw(water, src, dest);
                break;
            case 1:
                TextureManager::Draw(water, src, dest);
                TextureManager::Draw(tree, src, dest);
                break;
            case 2:
                TextureManager::Draw(water, src, dest);
                TextureManager::Draw(motel, src, dest);
                break;
            case 3:
                TextureManager::Draw(water, src, dest);
                TextureManager::Draw(cupcake, src, dest);
                break;
            case 4:
                TextureManager::Draw(water, src, dest);
                TextureManager::Draw(school, src, dest);
                break;
            case 5:
                TextureManager::Draw(water, src, dest);
                TextureManager::Draw(hospital, src, dest);
                break;
            case 6:
                TextureManager::Draw(water, src, dest);
                TextureManager::Draw(shop, src, dest);
                break;
            case 7:
                TextureManager::Draw(water, src, dest);
                TextureManager::Draw(cafe, src, dest);
                break;
            case 8:
                TextureManager::Draw(water, src, dest);
                TextureManager::Draw(mosque, src, dest);
                break;
            case 9:
                TextureManager::Draw(water, src, dest);
                TextureManager::Draw(b1, src, dest);
                break;
            case 10:
                TextureManager::Draw(water, src, dest);
                TextureManager::Draw(b2, src, dest);
                break;
            case 11:
                TextureManager::Draw(water, src, dest);
                TextureManager::Draw(b3, src, dest);
                break;
            case 12:
                TextureManager::Draw(water, src, dest);
                TextureManager::Draw(Fwheel, src, dest);
                break;
            case 13:
                TextureManager::Draw(path1, src, dest);
                break;
            default:
                break;
            }
        }
    }
}