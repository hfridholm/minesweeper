/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#include "../screen.h"

#include "s-intern.h"

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

SDL_Color COLOR_WHITE = {255, 255, 255};
SDL_Color COLOR_GREEN = {0  , 200, 0  };
SDL_Color COLOR_RED   = {200, 0,   0  };

/*
 * Get texture of text
 */
static SDL_Texture* text_texture_create(SDL_Renderer* renderer, const char* text, TTF_Font* font, SDL_Color color)
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

/*
 * Get width and height of rendered text
 *
 * RETURN (int status)
 * - 0 | Success
 * - 1 | Failed to create text surface
 */
static int text_w_and_h_get(int* w, int* h, const char* text, TTF_Font* font)
{
  SDL_Surface* surface = TTF_RenderText_Solid(font, text, COLOR_WHITE);

  if(!surface)
  {
    error_print("Failed to create text surface");
    error_print("TTF_RenderText_Solid: %s", TTF_GetError());

    return 1;
  }

  *w = surface->w;
  *h = surface->h;

  SDL_FreeSurface(surface);

  return 0;
}

/*
 *
 */
static int texture_w_and_h_get(int* w, int* h, SDL_Texture* texture)
{
  if(SDL_QueryTexture(texture, NULL, NULL, w, h) != 0)
  {
    error_print("Failed to query texture");
    error_print("SDL_QueryTexture: %s", SDL_GetError());

    return 1;
  }

  return 0;
}

/*
 * Create a clamped rect with the ratio of (w, h)
 */
static int clamped_text_rect_create(SDL_Rect* clamped_rect, SDL_Renderer* renderer, const char* text, TTF_Font* font, SDL_Rect* rect)
{
  if(!clamped_rect)
  {
    error_print("Bad input");

    return 1;
  }

  int textw, texth;

  if(text_w_and_h_get(&textw, &texth, text, font) != 0)
  {
    error_print("Failed to get text true dimensions");

    return 2;
  }

  float wratio = (float) textw / (float) texth;
  float hratio = (float) texth / (float) textw;

  if(!rect)
  {
    SDL_Texture* texture = SDL_GetRenderTarget(renderer);

    int rectw, recth;

    if(texture_w_and_h_get(&rectw, &recth, texture) != 0)
    {
      error_print("Failed to get texture dimensions");

      return 3;
    }

    int clampedw = MIN(recth * wratio, rectw);
    int clampedh = MIN(rectw * hratio, recth);

    *clamped_rect = (SDL_Rect)
    {
      .x = (rectw - clampedw) / 2,
      .y = (recth - clampedh) / 2,
      .w = clampedw,
      .h = clampedh
    };

    return 0;
  }
  else
  {
    int clampedw = MIN(rect->h * wratio, rect->w);
    int clampedh = MIN(rect->w * hratio, rect->h);

    *clamped_rect = (SDL_Rect)
    {
      .x = rect->x,
      .y = rect->y,
      .w = clampedw,
      .h = clampedh
    };

    return 0;
  }
}

/*
 *
 */
int text_render(SDL_Renderer* renderer, const char* text, TTF_Font* font, SDL_Color color, SDL_Rect* rect)
{
  SDL_Texture* texture = text_texture_create(renderer, text, font, color);

  if(!texture)
  {
    return 1;
  }

  SDL_Rect clamped_rect;

  if(clamped_text_rect_create(&clamped_rect, renderer, text, font, rect) != 0)
  {
    texture_destroy(&texture);
    
    error_print("Failed to create clamped text rect");

    return 2;
  }

  if(texture_render(renderer, texture, &clamped_rect) != 0)
  {
    texture_destroy(&texture);
    
    error_print("Failed to render texture");

    return 3;
  }

  texture_destroy(&texture);

  return 0;
}

/*
 * Render texture to target texture
 */
int render_target_text_render(SDL_Renderer* renderer, SDL_Texture* target, const char* text, TTF_Font* font, SDL_Color color, SDL_Rect* rect)
{
  SDL_Texture* old_target = SDL_GetRenderTarget(renderer);

  // 1. Temporarly set the new target
  if(render_target_set(renderer, target) != 0)
  {
    return 1;
  }

  int status = text_render(renderer, text, font, color, rect);

  // 2. Change back to the old target
  if(render_target_set(renderer, old_target) != 0)
  {
    return 2;
  }

  return (status == 0) ? 0 : 3;
}
