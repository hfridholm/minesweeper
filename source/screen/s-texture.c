/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#include "../screen.h"

#include "s-screen-intern.h"

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
