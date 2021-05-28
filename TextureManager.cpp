#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
    SDL_Surface* tempSurface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface); 
    
    return tex;
}
void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(Game::renderer, tex, &src, &dest);  
}
void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)  //overloading
{
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);  //NULLs are for angle , flip para decides to flip the character when moving in other directions 
}

//draw functions get images on screen  
//(parameters are our renderer, texture needed to be rendered, part of the texture that we want on screen, then lastly where on screen)