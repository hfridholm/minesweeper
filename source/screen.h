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
 * Either the window has a parent window, or a menu, not both
 */
typedef struct window_t
{
  char*        name;
  SDL_Rect     rect;        // Size and local position
  SDL_Texture* texture;
  window_t**   children;
  int          child_count;
  window_t*    parent;      // Reference back to parent window
  menu_t*      menu;        // Reference back to menu
} window_t;

extern window_t* window_create(char* name, SDL_Rect rect);

extern void      window_destroy(window_t** window);

extern int       window_child_add(window_t* window, window_t* child);

extern int       window_texture_render(window_t* window, SDL_Texture* texture, SDL_Rect* rect);

/*
 *
 */
typedef struct menu_t
{
  char*        name;
  SDL_Texture* texture;
  window_t**   windows;
  int          window_count;
  screen_t*    screen;       // Reference back to screen
} menu_t;


extern menu_t*   menu_create(char* name);

extern void      menu_destroy(menu_t** menu);

extern int       menu_window_add(menu_t* menu, window_t* window);

extern int       menu_texture_render(menu_t* menu, SDL_Texture* texture, SDL_Rect* rect);

extern window_t* menu_window_get(menu_t* menu, const char* name);

/*
 *
 */
typedef struct screen_t
{
  char*         name;
  SDL_Window*   window;    // The physical window
  SDL_Renderer* renderer;
  int           width;
  int           height;
  menu_t**      menus;
  int           menu_count;
  char*         menu_name;
} screen_t;

extern screen_t* screen_create(int width, int height, char* name);

extern void      screen_destroy(screen_t** screen);

extern int       screen_menu_add(screen_t* screen, menu_t* menu);

extern int       screen_render(screen_t* screen);

extern menu_t*   screen_menu_get(screen_t* screen, const char* name);

/*
 *
 */
extern SDL_Texture* texture_load(SDL_Renderer* renderer, const char* file);

extern SDL_Texture* texture_create(SDL_Renderer* renderer, int width, int height);

extern int          texture_render(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* srcrect, SDL_Rect* dstrect);

extern void         texture_destroy(SDL_Texture** texture);

/*
 *
 */
extern Mix_Chunk* chunk_load(const char* file);

extern int        chunk_play(Mix_Chunk* chunk);

extern void       chunk_free(Mix_Chunk** chunk);

/*
 *
 */
extern SDL_Color COLOR_WHITE;
extern SDL_Color COLOR_GREEN;
extern SDL_Color COLOR_RED;

extern TTF_Font*    font_load(const char* file, int size);

extern SDL_Texture* text_texture_create(SDL_Renderer* renderer, const char* text, TTF_Font* font, SDL_Color color);

extern void         font_close(TTF_Font** font);

/*
 *
 */
extern int  sdl_drivers_init(void);

extern void sdl_drivers_quit(void);

#endif // SCREEN_H
