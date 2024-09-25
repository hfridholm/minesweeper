/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#include "../assets.h"

#include "a-intern.h"

/*
 * Load texture
 */
SDL_Texture* texture_load(SDL_Renderer* renderer, const char* path)
{
  SDL_Surface* surface = IMG_Load(path);
  
  if(!surface)
  {
    error_print("Failed to load image at: %s", path);
    error_print("IMG_Load: %s", IMG_GetError());

    return NULL;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);

  if(!texture)
  {
    error_print("Failed to create texture from surface");
    error_print("SDL_CreateTextureFromSurface: %s", SDL_GetError());

    return NULL;
  }

  return texture;
}

/*
 * Destroy texture
 */
void texture_destroy(SDL_Texture** texture)
{
  if(*texture == NULL) return;

  SDL_DestroyTexture(*texture);

  *texture = NULL;
}
