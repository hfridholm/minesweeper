/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-22
 */

#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <stdbool.h>

#include "debug.h"
#include "screen.h"
#include "assets.h"
#include "field.h"

extern void game_render(screen_t* screen, assets_t* assets, field_t* field);

extern void event_handler(screen_t* screen, assets_t* assets, field_t* field, SDL_Event* event);

extern int  screen_resize(screen_t* screen, field_t* field, int width, int height);

#endif // MINESWEEPER_H
