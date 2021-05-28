#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponent : public Component
{
    public:
    TransformComponent* transform;
    SpriteComponent *sprite;

    SDL_Rect tileRect;
    char *path;
    int tileID;

    TileComponent() = default;

    TileComponent(int x, int y, int w, int h, int id)
    {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        tileID = id; //will help with creating tiles

        switch (tileID)
        {
        case 0:
            path = "assets/g1.jpg";
            break;
        case 1:
            path = "assets/tree.png";
            break;
        case 2:
            path = "assets/motel.png";
            break;
        case 3:
            path = "assets/c.png";
            break;
        case 4:
            path = "assets/school.png";
            break;
        case 5:
            path = "assets/hospital.png";
            break;
        case 6:
            path = "assets/shop.png";
            break;
        case 7:
            path = "assets/cafe.png";
            break;
        case 8:
            path = "assets/mosque.png";
            break;
        case 9:
            path = "assets/b1.png";
            break;
        case 10:
            path = "assets/b2.png";
            break;
        case 11:
            path = "assets/b3.png";
            break;
        case 12:
            path = "assets/Fwheel.png";
            break;
        case 13:
            path = "assets/p1.png";
            break;
        case 14:
            path = "assets/p2.jpg";
            break;
        case 15:
            path = "assets/b4.png";
            break;
        case 16:
            path = "assets/field.png";
            break;
        case 17:
            path = "assets/water.png";
            break;
        case 18:
            path = "assets/hen.png";
            break;
        case 20:
            path = "assets/invisible.png";
            break;
        default:
            break;
        }
    }
    void init() override
    {
        entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1); //adding component to the entity
        transform = &entity->getComponent<TransformComponent>();

        entity->addComponent<SpriteComponent>(path);
        sprite = &entity->getComponent<SpriteComponent>();
    }
};