/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#include "../screen.h"

/*
 * Create SDL Window
 */
static SDL_Window* sdl_window_create(int width, int height, const char* title)
{
  info_print("Creating SDL Window");

  SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

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

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

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
 * Create screen
 */
screen_t* screen_create(int width, int height, const char* title)
{
  info_print("Creating screen");

  screen_t* screen = malloc(sizeof(screen_t));

  screen->window = sdl_window_create(width, height, title);

  screen->renderer = sdl_renderer_create(screen->window);

  info_print("Created screen");

  return screen;
}

/*
 * Destroy screen
 */
void screen_destroy(screen_t** screen)
{
  if(!screen || !(*screen)) return;

  info_print("Destroying screen");

  sdl_window_destroy(&(*screen)->window);

  sdl_renderer_destroy(&(*screen)->renderer);

  free(*screen);

  *screen = NULL;

  info_print("Destroyed screen");
}
