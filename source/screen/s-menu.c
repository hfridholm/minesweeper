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
int menu_texture_resize(menu_t* menu, int width, int height)
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

  texture_resize(&menu->texture, renderer, width, height);

  return 0;
}

/*
 * Render a texture directly to the menu, in the background
 *
 * The textures of windows will be rendered over this texture
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

  render_target_texture_render(renderer, menu->texture, texture, rect);

  return 0;
}

/*
 * Render menu with all of it's windows and child windows
 *
 * Clear the textures of the windows that are rendered
 *
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

  for(int index = 0; index < menu->window_count; index++)
  {
    window_t* window = menu->windows[index];

    window_render(window);

    render_target_texture_render(renderer, menu->texture, window->texture, &window->rect);

    render_target_clear(renderer, window->texture);
  }

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
  memset(menu, 0, sizeof(menu_t));

  menu->name = name;

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
