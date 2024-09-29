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
bool event_is_inside_rect(SDL_Event* event, SDL_Rect* rect)
{
  int x = event->button.x;
  int y = event->button.y;

  return (x >= rect->x && x <= (rect->x + rect->w) &&
          y >= rect->y && y <= (rect->y + rect->h));
}

/*
 * EXPECT:
 * - menu is allocated
 */
window_t* event_window_get(menu_t* menu, SDL_Event* event)
{
  for(int index = 0; index < menu->window_count; index++)
  {
    window_t* window = menu->windows[index];

    if(event_is_inside_rect(event, &window->rect)) return window;
  }
  
  return NULL;
}

/*
 *
 */
void menu_event_handler(menu_t* menu, assets_t* assets, field_t* field, SDL_Event* event)
{
  if(strcmp(menu->name, "field") == 0)
  {
    menu_field_event_handler(menu, assets, field, event);
  }
}

/*
 *
 */
void event_key_down_handler(screen_t* screen, assets_t* assets, field_t* field, SDL_Event* event)
{

}

/*
 *
 */
void event_mouse_motion_handler(screen_t* screen, assets_t* assets, field_t* field, SDL_Event* event)
{

}

/*
 *
 */
void event_window_handler(screen_t* screen, assets_t* assets, field_t* field, SDL_Event* event)
{
  switch(event->window.event)
  {
    case SDL_WINDOWEVENT_RESIZED: case SDL_WINDOWEVENT_SIZE_CHANGED:
      event_resize_handler(screen, assets, field, event);
      break;

    default:
      break;
  }
}

/*
 * Handle an event
 */
void event_handler(screen_t* screen, assets_t* assets, field_t* field, SDL_Event* event)
{
  if(!event) return;

  switch(event->type)
  {
    case SDL_KEYDOWN:
      event_key_down_handler(screen, assets, field, event);
      break;

    case SDL_MOUSEMOTION:
      event_mouse_motion_handler(screen, assets, field, event);
      break;

    case SDL_WINDOWEVENT:
      event_window_handler(screen, assets, field, event);
      break;

    default:
      break;
  }

  menu_t* menu = screen_menu_get(screen, screen->menu_name);

  if(menu)
  {
    menu_event_handler(menu, assets, field, event);
  }
}
