/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#ifndef M_INTERN_H
#define M_INTERN_H

#include "../minesweeper.h"

extern void menu_field_event_handler(menu_t* menu, assets_t* assets, field_t* field, SDL_Event* event);

extern void menu_field_window_field_event_handler(window_t* window, assets_t* assets, field_t* field, SDL_Event* event);


extern window_t* event_window_get(menu_t* menu, SDL_Event* event);

extern bool      event_is_inside_rect(SDL_Event* event, SDL_Rect* rect);

#endif // M_INTERN_H
