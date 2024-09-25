/*
 * The screen struct is used to render assets
 *
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#ifndef SCREEN_H
#define SCREEN_H

#include <stdlib.h>
#include <unistd.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "debug.h"

typedef struct window_t window_t;

typedef struct menu_t   menu_t;

typedef struct screen_t screen_t;

/*
 *
 */
typedef int window_event_t(window_t*, int);

typedef struct window_t
{
  char*           name;
  window_t*       children;
  int             child_count;
  SDL_Rect        rect;        // Size and local position
  window_event_t* event;
  window_t*       parent;      // Reference back to parent window
  menu_t*         menu;        // Reference back to menu
} window_t;

extern window_t* window_create();

extern void      window_destroy(window_t** window);

/*
 *
 */
typedef int menu_event_t(menu_t*, int);

typedef struct menu_t
{
  char*         name;
  window_t**    windows;
  int           window_count;
  menu_event_t* event;
  screen_t*     screen;       // Reference back to screen
} menu_t;


extern menu_t* menu_create();

extern void    menu_destroy(menu_t** menu);

extern int     menu_window_add(menu_t* menu, window_t* window);
/*
 *
 */
typedef struct screen_t
{
  char*         title;
  SDL_Window*   window;    // The physical window
  SDL_Renderer* renderer;
  menu_t**      menus;
  int           menu_count;
} screen_t;

extern screen_t* screen_create(int width, int height, char* title);

extern void      screen_destroy(screen_t** screen);

extern int       screen_menu_add(screen_t* screen, menu_t* menu);

#endif // SCREEN_H
