/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#include "../screen.h"

#include "s-intern.h"

/*
 * Create SDL Window
 */
static SDL_Window* sdl_window_create(int width, int height, char* name)
{
  info_print("Creating SDL Window");

  SDL_Window* window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

  if(!window)
  {
    error_print("SDL_CreateWindow: %s", SDL_GetError());

    return NULL;
  }

  SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

  info_print("Created SDL Window");

  return window;
}

/*
 * Destroy SDL Window
 */
static void sdl_window_destroy(SDL_Window** window)
{
  if(!window) return;

  info_print("Destroying SDL Window");

  SDL_DestroyWindow(*window);

  *window = NULL;

  info_print("Destroyed SDL Window");
}

/*
 *
 */
static SDL_Renderer* sdl_renderer_create(SDL_Window* window)
{
  info_print("Creating SDL Renderer");

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

  if(!renderer)
  {
    error_print("SDL_CreateRenderer: %s", SDL_GetError());

    return NULL;
  }

  info_print("Created SDL Renderer");

  return renderer;
}

/*
 *
 */
static void sdl_renderer_destroy(SDL_Renderer** renderer)
{
  if(!renderer) return;

  info_print("Destroying SDL Renderer");

  SDL_DestroyRenderer(*renderer);

  info_print("Destroyed SDL Renderer");

  *renderer = NULL;
}

/*
 *
 */
menu_t* screen_menu_get(screen_t* screen, const char* name)
{
  if(!screen)
  {
    error_print("Bad input");

    return NULL;
  }

  for(int index = 0; index < screen->menu_count; index++)
  {
    menu_t* menu = screen->menus[index];

    if(menu && strcmp(menu->name, name) == 0) return menu;
  }

  return NULL;
}

/*
 *
 */
int screen_menu_add(screen_t* screen, menu_t* menu)
{
  if(!screen || !menu)
  {
    error_print("Bad input");
    
    return 1;
  }

  info_print("Adding menu: %s", menu->name);

  // 1. Add menu to screen
  screen->menus = realloc(screen->menus, sizeof(menu_t*) * (screen->menu_count + 1));

  if(!screen->menus)
  {
    error_print("Failed to allocate added menu");

    return 2;
  }

  screen->menus[screen->menu_count++] = menu;

  // 2. Add references to menu
  menu->screen = screen;

  menu->texture = texture_create(screen->renderer, screen->width, screen->height);

  info_print("Added menu: %s", menu->name);

  return 0;
}

/*
 *
 */
SDL_Renderer* screen_renderer_get(screen_t* screen)
{
  if(!screen)
  {
    error_print("Bad input");

    return NULL;
  }

  return screen->renderer;
}

/*
 *
 */
int screen_render(screen_t* screen)
{
  if(!screen)
  {
    error_print("Bad input");

    return 1;
  }

  SDL_Renderer* renderer = screen_renderer_get(screen);

  if(!renderer)
  {
    error_print("Failed to get renderer from screen: %s", screen->name);

    return 2;
  }

  render_target_set(renderer, NULL);

  SDL_RenderClear(renderer);

  menu_t* menu = screen_menu_get(screen, screen->menu_name);

  menu_render(menu);

  SDL_Rect rect =
  {
    .w = screen->width,
    .h = screen->height
  };

  texture_render(screen->renderer, menu->texture, NULL, &rect);

  SDL_RenderPresent(renderer);

  return 0;
}

/*
 * Create screen
 */
screen_t* screen_create(int width, int height, char* name)
{
  info_print("Creating screen: %s", name);

  screen_t* screen = malloc(sizeof(screen_t));

  screen->name = name;

  screen->window   = sdl_window_create(width, height, name);
  screen->renderer = sdl_renderer_create(screen->window);

  screen->width  = width;
  screen->height = height;

  screen->menus      = NULL;
  screen->menu_count = 0;

  info_print("Created screen: %s", name);

  return screen;
}

/*
 * Destroy screen
 */
void screen_destroy(screen_t** screen)
{
  if(!screen || !(*screen)) return;

  info_print("Destroying screen: %s", (*screen)->name);

  sdl_renderer_destroy(&(*screen)->renderer);

  sdl_window_destroy(&(*screen)->window);

  for(int index = 0; index < (*screen)->menu_count; index++)
  {
    menu_destroy(&(*screen)->menus[index]);
  }

  free((*screen)->menus);

  info_print("Destroyed screen: %s", (*screen)->name);

  free(*screen);

  *screen = NULL;
}
