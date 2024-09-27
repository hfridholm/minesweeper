/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#include "../screen.h"

#include "s-intern.h"

/*
 *
 */
window_t* menu_window_get(menu_t* menu, const char* name)
{
  if(!menu)
  {
    error_print("Bad input");
    
    return NULL;
  }

  for(int index = 0; index < menu->window_count; index++)
  {
    window_t* window = menu->windows[index];

    if(window && strcmp(window->name, name) == 0) return window;
  }

  return NULL;
}

/*
 *
 */
int menu_window_add(menu_t* menu, window_t* window)
{
  if(!menu || !window)
  {
    error_print("Bad input");
    
    return 1;
  }

  info_print("Adding window: %s", window->name);

  // 1. Add window to menu
  menu->windows = realloc(menu->windows, sizeof(window_t*) * (menu->window_count + 1));

  if(!menu->windows)
  {
    error_print("Failed to allocate added window");

    return 2;
  }

  menu->windows[menu->window_count++] = window;

  // 2. Add references to window
  window->menu = menu;

  window->texture = texture_create(menu->screen->renderer, window->rect.w, window->rect.h);

  info_print("Added window: %s", window->name);

  return 0;
}

/*
 *
 */
SDL_Renderer* menu_renderer_get(menu_t* menu)
{
  if(!menu)
  {
    error_print("Bad input");

    return NULL;
  }

  return screen_renderer_get(menu->screen);
}

/*
 *
 */
int menu_texture_render(menu_t* menu, SDL_Texture* texture, SDL_Rect* rect)
{
  if(!menu || !texture)
  {
    error_print("Bad input");

    return 1;
  }

  SDL_Renderer* renderer = menu_renderer_get(menu);

  if(!renderer)
  {
    error_print("Failed to get renderer from menu %s", menu->name);
    
    return 2;
  }

  render_target_set(renderer, menu->texture);

  texture_render(renderer, texture, NULL, rect);

  render_target_set(renderer, NULL);

  return 0;
}

/*
 * The for-loop decides which order to render the windows
 */
int menu_render(menu_t* menu)
{
  if(!menu)
  {
    error_print("Bad input");

    return 1;
  }

  SDL_Renderer* renderer = menu_renderer_get(menu);

  if(!renderer)
  {
    error_print("Failed to get renderer from menu %s", menu->name);
    
    return 2;
  }

  render_target_set(renderer, menu->texture);

  for(int index = 0; index < menu->window_count; index++)
  {
    window_t* window = menu->windows[index];

    window_render(window);

    menu_texture_render(menu, window->texture, &window->rect);
  }

  render_target_set(renderer, NULL);

  return 0;
}

/*
 * Create menu
 *
 * Maybe: Add menu directly to screen
 */
menu_t* menu_create(char* name)
{
  info_print("Creating menu: %s", name);

  menu_t* menu = malloc(sizeof(menu_t));

  menu->name = name;

  menu->windows      = NULL;
  menu->window_count = 0;

  menu->screen = NULL;

  menu->texture = NULL;

  info_print("Created menu: %s", name);

  return menu;
}

/*
 * Destroy menu
 */
void menu_destroy(menu_t** menu)
{
  if(!menu || !(*menu)) return;

  info_print("Destroying menu: %s", (*menu)->name);

  for(int index = 0; index < (*menu)->window_count; index++)
  {
    window_destroy(&(*menu)->windows[index]);
  }

  free((*menu)->windows);

  texture_destroy(&(*menu)->texture);

  info_print("Destroyed menu: %s", (*menu)->name);

  free(*menu);

  *menu = NULL;
}
