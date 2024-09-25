/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#include "../screen.h"

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

  menu->windows = realloc(menu->windows, sizeof(window_t*) * (menu->window_count + 1));

  if(!menu->windows)
  {
    error_print("Failed to allocate added window");

    return 2;
  }

  menu->windows[menu->window_count++] = window;

  info_print("Added window: %s", window->name);

  return 0;
}

/*
 * Create menu
 */
menu_t* menu_create(char* name)
{
  info_print("Creating menu: %s", name);

  menu_t* menu = malloc(sizeof(menu_t));

  menu->name = name;

  menu->windows      = NULL;
  menu->window_count = 0;

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

  info_print("Destroyed menu: %s", (*menu)->name);

  free(*menu);

  *menu = NULL;
}
