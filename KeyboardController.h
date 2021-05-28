#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"

//to handle inputs
class KeyboardContoller : public Component
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;


    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    //check for the keys we have
    void update() override
    {
        //we need to check for when a key is pressed and when the key is released
        if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                transform->velocity.y = -1;
                sprite->Play("Up"); //setting animations through spritesheet
                break;
            case SDLK_UP:
                transform->velocity.y = -1;
                sprite->Play("Up");
                break;
            case SDLK_s:
                transform->velocity.y = +1;
                sprite->Play("Down");
                break;
            case SDLK_DOWN:
                transform->velocity.y = +1;
                sprite->Play("Down");
                break;
            case SDLK_d:
                transform->velocity.x = +1;
                sprite->Play("Walk");
                break;
            case SDLK_RIGHT:
                transform->velocity.x = +1;
                sprite->Play("Walk");
                break;
            case SDLK_a:
                transform->velocity.x = -1;
                sprite->Play("Walk");
                sprite->spriteFlip = SDL_FLIP_HORIZONTAL; //flips the character the other way
                break;
            case SDLK_LEFT:
                transform->velocity.x = -1;
                sprite->Play("Walk");
                sprite->spriteFlip = SDL_FLIP_HORIZONTAL; //flips the character the other way
                break;
            default:
                break;
            }
        }
        if (Game::event.type == SDL_KEYUP)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                transform->velocity.y = 0;
                sprite->Play("Idle");
                break;
            case SDLK_s:
                transform->velocity.y = 0;
                sprite->Play("Idle");
                break;
            case SDLK_d:
                transform->velocity.x = 0;
                sprite->Play("Idle");
                break;
            case SDLK_a:
                transform->velocity.x = 0;
                sprite->Play("Idle");
                sprite->spriteFlip = SDL_FLIP_NONE; //when key is released, no flip needed
                break;
            case SDLK_RIGHT:
                transform->velocity.x = 0;
                sprite->Play("Idle");
                break;
            case SDLK_UP:
                transform->velocity.y = 0;
                sprite->Play("Idle");
                break;
            case SDLK_DOWN:
                transform->velocity.y = 0;
                sprite->Play("Idle");
                break;
            case SDLK_LEFT:
                transform->velocity.x = 0;
                sprite->Play("Idle");
                sprite->spriteFlip = SDL_FLIP_NONE; //when key is released, no flip needed
                break;
            default:
                break;
            }
        }
    }
};