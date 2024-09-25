/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#include "../screen.h"

/*
 * Create window
 */
window_t* window_create(char* name)
{
  info_print("Creating window: %s", name);

  window_t* window = malloc(sizeof(window_t));

  window->name = name;

  window->children    = NULL;
  window->child_count = 0;

  info_print("Created window: %s", name);

  return window;
}

/*
 * Destroy window
 */
void window_destroy(window_t** window)
{
  if(!window || !(*window)) return;

  info_print("Destroying window: %s", (*window)->name);

  // ...

  info_print("Destroyed window: %s", (*window)->name);

  free(*window);

  *window = NULL;
}
