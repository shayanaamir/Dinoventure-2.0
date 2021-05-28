#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>


class SpriteComponent : public Component
{
    private:
    //we will need to refer to the positions. 
        TransformComponent *transform;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

        bool animated = false;
        int frames = 0;
        int speed = 100;

    public:
        int animIndex = 0; //initial pos = 0
        std::map<const char *, Animation> animations; //holds animation
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;   

        SpriteComponent() = default;
        SpriteComponent(const char* path)
        {
            setTex(path);
            animated = false;
        }
        SpriteComponent(const char* path, bool isAnimated)
        {
            animated = isAnimated;

            Animation idle = Animation(0, 1, 150);  //index=0, one frame and speed=100  //indexes are set according to the spritesheet made
            Animation up = Animation(1, 2, 50);    //index =1, 2 frames, speed=50 etc     
            Animation down = Animation(2, 2, 50);
            Animation walk = Animation(3, 3, 80);
            animations.emplace("Idle", idle);
            animations.emplace("Up", up);
            animations.emplace("Down", down);
            animations.emplace("Walk", walk);

            Play("Idle");
            setTex(path);

        }
        ~SpriteComponent()
        {
            SDL_DestroyTexture(texture);
        }
        void setTex(const char* path) //to change the texture
        {
            texture = TextureManager::LoadTexture(path);
        }

        //to initialise the rectangles
        void init() override  
        {
            transform = &entity->getComponent<TransformComponent>(); //reference to get the component

            srcRect.x = srcRect.y = 0;

            // Since our sprites are very big 300px. we just hardcode for now until we can fix sprites.
            srcRect.w = transform->width;
            srcRect.h = transform->height;
            
        }
        void update() override
        {
            if (animated)
            {
                srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
            }
            srcRect.y = animIndex * transform->height;  //initial pos = 0 because aniIndex set to 0, when aniIndex=1, the pos will be change and so on
            
            destRect.x = static_cast<int>(transform->position.x);
            destRect.y = static_cast<int>(transform->position.y);
            destRect.w = static_cast<int>(transform->width * transform->scale);
            destRect.h = static_cast<int>(transform->height * transform->scale);
        }
        void draw() override
        {
            TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
        }

        //used to change frames, indexes and speed
        void Play(const char* animName)
        {
            frames = animations[animName].frames;
            animIndex = animations[animName].index;
            speed = animations[animName].speed;
        }
};