#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, int x, int y, int Vel)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
    Velocity = Vel;
}

void GameObject::Move(int xvel,int yvel)
{
    if (xvel!=0){ xpos += xvel*Velocity; }
    if (yvel!=0){ ypos += yvel*Velocity; }
}
void GameObject::Update()
{
    // xpos++;
    // ypos++;

    // srcRect.h = 32;
    // srcRect.w = 32;
    // srcRect.x = 0;
    // srcRect.y = 0;

    // This queries the image that is passed onto the GameObject and finds
    // its width and height. It then passes the width and height of the
    // original image into the source Rectangle, Hence selecting the whole image.
    SDL_QueryTexture(objTexture, NULL, NULL, &srcRect.w, &srcRect.h);


    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w/5;
    destRect.h = srcRect.h/5;

}

void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer,objTexture, &srcRect, &destRect);
}