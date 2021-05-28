#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"

class ColliderComponent : public Component
{
public:
    SDL_Rect collider;
    std::string tag;

    TransformComponent* transform;

    ColliderComponent(std::string t) //ctor
    {
        tag = t;
    }
    void init() override
    {
        if (!entity-> hasComponent <TransformComponent> ()) //checks if the entity has the component already or not
        {
            entity->addComponent<TransformComponent>(); //if the entity does not have the component then we add it here
        }
        transform = &entity->getComponent<TransformComponent>();

        Game::colliders.push_back(this);
    }
    void update() override
    {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
    }
};