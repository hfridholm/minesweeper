/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#ifndef S_INTERN_H
#define S_INTERN_H

#include "../screen.h"

extern SDL_Renderer* screen_renderer_get(screen_t* screen);

extern SDL_Renderer* menu_renderer_get(menu_t* menu);

extern SDL_Renderer* window_renderer_get(window_t* window);


extern int render_target_set(SDL_Renderer* renderer, SDL_Texture* target);

extern int render_target_clear(SDL_Renderer* renderer, SDL_Texture* target);

extern int render_target_texture_render(SDL_Renderer* renderer, SDL_Texture* target, SDL_Texture* texture, SDL_Rect* rect);

extern int render_target_text_render(SDL_Renderer* renderer, SDL_Texture* target, const char* text, TTF_Font* font, SDL_Color color, SDL_Rect* rect);


extern int window_render(window_t* window);

extern int menu_render(menu_t* menu);


extern void texture_resize(SDL_Texture** texture, SDL_Renderer* renderer, int width, int height);

#endif // S_INTERN_H
