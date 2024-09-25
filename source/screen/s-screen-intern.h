/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#ifndef S_SCREEN_INTERN_H
#define S_SCREEN_INTERN_H

#include "../screen.h"

extern SDL_Renderer* screen_renderer_get(screen_t* screen);

extern SDL_Renderer* menu_renderer_get(menu_t* menu);

extern SDL_Renderer* window_renderer_get(window_t* window);

extern int texture_render(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* srcrect, SDL_Rect* dstrect);

#endif // S_SCREEN_INTERN_H
