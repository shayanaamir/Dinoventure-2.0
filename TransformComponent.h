#pragma once
#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
    public:
        Vector2D position;
        Vector2D velocity;

        int height = 32;
        int width = 32;
        int scale = 1;

        int speed = 3;
        
        TransformComponent()
        {
            position.Zero();
        }
        TransformComponent(int sc) // using for scale purposes
        {
            position.Zero();
            scale = sc;
        }
        TransformComponent(float x, float y) // fnc overloading
        {
            position.x = x;
            position.y = y;
        }
        TransformComponent(float x, float y, int w, int h, int sc) // fnc overloading
        {
            position.x = x;
            position.y = y;
            height = h;
            width = w;
            scale = sc;
        }
        void init() override
        {
            velocity.Zero();
        }
        void update() override
        {
            position.x += velocity.x * speed;
            position.y += velocity.y * speed;
        }
};