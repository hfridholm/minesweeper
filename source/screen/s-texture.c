/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#include "../screen.h"

#include "s-intern.h"

SDL_Color COLOR_WHITE = {200, 200, 200};
SDL_Color COLOR_GREEN = {0  , 200, 0  };
SDL_Color COLOR_RED   = {200, 0,   0  };

/*
 * Render texture
 */
int texture_render(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* srcrect, SDL_Rect* dstrect)
{
  int status = SDL_RenderCopy(renderer, texture, srcrect, dstrect);

  if(status != 0)
  {
    error_print("Failed to render texture");
    error_print("SDL_RenderCopy: %s", SDL_GetError());
  }

  return status;
}

/*
 * Get texture of text
 */
SDL_Texture* text_texture_create(SDL_Renderer* renderer, const char* text, TTF_Font* font, SDL_Color color)
{
  SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);

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
