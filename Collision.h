#pragma once
#include "SDL.h"

class ColliderComponent;

class Collision
{
public:
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB); //AA is access inline bounding box which checks the x position of each rectangle and to make sure that they are within bound when they are colliding
    static bool AABB(const ColliderComponent &colA, const ColliderComponent &colB);
};