/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#include "../screen.h"

#include "s-intern.h"

/*
 * Load texture
 */
SDL_Texture* texture_load(SDL_Renderer* renderer, const char* file)
{
  info_print("Loading texture");

  SDL_Surface* surface = IMG_Load(file);
  
  if(!surface)
  {
    error_print("Failed to load image at: %s", file);
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

  info_print("Loaded texture");

  return texture;
}

/*
 *
 */
SDL_Texture* texture_create(SDL_Renderer* renderer, int width, int height)
{
  info_print("Creating texture");

  SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);

  if(!texture)
  {
    error_print("Failed to create texture");
    error_print("SDL_CreateTexture: %s", SDL_GetError());

    return NULL;
  }

  if(SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) != 0)
  {
    error_print("SDL_SetTextureBlendMode: %s", SDL_GetError());

    texture_destroy(&texture);

    return NULL;
  }

  info_print("Created texture");

  return texture;
}

/*
 *
 */
int render_target_set(SDL_Renderer* renderer, SDL_Texture* target)
{
  int status = SDL_SetRenderTarget(renderer, target);

  if(status != 0)
  {
    error_print("SDL_SetRenderTarget: %s", SDL_GetError());

    return status;
  }

  return 0;
}

/*
 * Clear the supplied texture
 *
 * This function should set a temporary new target, clear, and set back the old target
 */
int render_target_clear(SDL_Renderer* renderer, SDL_Texture* target)
{
  SDL_Texture* old_target = SDL_GetRenderTarget(renderer);

  // 1. Temporarly set the new target
  if(render_target_set(renderer, target) != 0)
  {
    return 1;
  }

  SDL_RenderClear(renderer);

  // 2. Change back to the old target
  if(render_target_set(renderer, old_target) != 0)
  {
    return 2;
  }

  return 0;
}

/*
 * Render texture to target texture
 */
int render_target_texture_render(SDL_Renderer* renderer, SDL_Texture* target, SDL_Texture* texture, SDL_Rect* rect)
{
  SDL_Texture* old_target = SDL_GetRenderTarget(renderer);

  // 1. Temporarly set the new target
  if(render_target_set(renderer, target) != 0)
  {
    return 1;
  }

  int status = texture_render(renderer, texture, rect);

  // 2. Change back to the old target
  if(render_target_set(renderer, old_target) != 0)
  {
    return 2;
  }

  return (status == 0) ? 0 : 3;
}

/*
 * Render texture
 */
int texture_render(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* rect)
{
  int status = SDL_RenderCopy(renderer, texture, NULL, rect);

  if(status != 0)
  {
    error_print("Failed to render texture");
    error_print("SDL_RenderCopy: %s", SDL_GetError());
  }

  return status;
}

/*
 * Destroy texture
 */
void texture_destroy(SDL_Texture** texture)
{
  if(*texture == NULL) return;

  // info_print("Destroying texture");

  SDL_DestroyTexture(*texture);

  // info_print("Destroyed texture");

  *texture = NULL;
}

/*
 *
 */
void texture_resize(SDL_Texture** texture, SDL_Renderer* renderer, int width, int height)
{
  texture_destroy(texture);

  *texture = texture_create(renderer, width, height);
}
