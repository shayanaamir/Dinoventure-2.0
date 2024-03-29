#include "Collision.h"
#include "ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
    if ( //if all these conditions below are met then only true will be returned
        recA.x < recB.x + recB.w &&
        recA.x + recA.w  > recB.x &&
        recA.y < recB.y + recB.h &&
        recA.y + recA.h > recB.y
        )
    {
        return true;
    }
    return false;
}

bool Collision::AABB(const ColliderComponent &colA, const ColliderComponent &colB)
{
    if (AABB(colA.collider, colB.collider))
    {
        if (colA.tag == colB.tag)
        {
            return false;
        }
        std::cout << colA.tag << " hit: " << colB.tag << std::endl;
        return true;
    }
    else
    {
        return false;
    }
    
}