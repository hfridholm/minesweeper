/*
 * Handle an event
 *
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-26
 */

#include "../minesweeper.h"

#include "m-intern.h"

/*
 *
 */
static void window_event_handler(window_t* window, assets_t* assets, field_t* field, SDL_Event* event)
{
  if(strcmp(window->name, "field") == 0)
  {
    menu_field_window_field_event_handler(window, assets, field, event);
  }
}

/*
 *
 */
void menu_field_event_handler(menu_t* menu, assets_t* assets, field_t* field, SDL_Event* event)
{
  window_t* window = event_window_get(menu, event);

  if(window)
  {
    window_event_handler(window, assets, field, event);
  }
}

