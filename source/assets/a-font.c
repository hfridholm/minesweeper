/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#include "../assets.h"

#include "a-intern.h"

/*
 *
 */
TTF_Font* font_load(const char* file, int size)
{
  TTF_Font* font = TTF_OpenFont(file, size);

  if(!font)
  {
    error_print("Failed to load font at: %s", file);
    error_print("TTF_OpenFont: %s", TTF_GetError());

    return NULL;
  }

  return font;
}

/*
 *
 */
void font_close(TTF_Font** font)
{
  if(*font == NULL) return;

  TTF_CloseFont(*font);

  *font = NULL;
}

SDL_Color COLOR_WHITE = {200, 200, 200};
SDL_Color COLOR_GREEN = {0  , 200, 0  };
SDL_Color COLOR_RED   = {200, 0,   0  };

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
