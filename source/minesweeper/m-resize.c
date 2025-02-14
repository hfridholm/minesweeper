/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-25
 */

#include "../minesweeper.h"

#include "m-intern.h"

/*
 * Create a rect with the bounds for the minefield window
 *
 * The bounds are the outer most edges that the minefield can stretch out to
 */
static SDL_Rect window_field_bound_rect_create(int parentw, int parenth)
{
  int x = (float) parentw * 0.25f;
  int y = 0;

  int w = (float) (parentw - x) * 0.90f;
  int h = (float) (parenth - y) * 0.90f;

  SDL_Rect rect = 
  {
    .x = x + (float) (parentw - x - w) / 2.f,
    .y = y + (float) (parenth - y - h) / 2.f,
    .w = w,
    .h = h
  };

  return rect;
}

/*
 * PARAMS
 * - int parentw | Width  of menu field
 * - int parenth | Height of menu field
 */
static void menu_field_window_field_resize(window_t* window, field_t* field, int parentw, int parenth)
{
  SDL_Rect rect = window_field_bound_rect_create(parentw, parenth);

  int squarew = (float) rect.w / (float) field->width;
  int squareh = (float) rect.h / (float) field->height;

  int squarel = MIN(squarew, squareh);

  int width  = squarel * field->width;
  int height = squarel * field->height;
  
  window->rect = (SDL_Rect)
  {
    .x = rect.x + ((float) (rect.w - width ) / 2.f),
    .y = rect.y + ((float) (rect.h - height) / 2.f),
    .w = width,
    .h = height
  };

  window_texture_resize(window, window->rect.w, window->rect.h);
}

/*
 *
 */
static void menu_field_window_result_resize(window_t* window, int parentw, int parenth)
{
  window->rect = (SDL_Rect)
  {
    .x = 0,
    .y = 0,
    .w = parentw,
    .h = parenth
  };

  window_texture_resize(window, window->rect.w, window->rect.h);
}

/*
 *
 */
static void menu_field_resize(menu_t* menu, field_t* field, int width, int height)
{
  window_t* window_field = menu_window_get(menu, "field");

  if(window_field)
  {
    menu_field_window_field_resize(window_field, field, width, height);
  }

  window_t* window_result = menu_window_get(menu, "result");

  if(window_result)
  {
    menu_field_window_result_resize(window_result, width, height);
  }

  window_t* window_data = menu_window_get(menu, "data");

  if(window_data)
  {
    menu_field_window_data_resize(window_data, width, height);
  }
}

/*
 *
 */
static void menu_resize(menu_t* menu, field_t* field, int width, int height)
{
  menu_texture_resize(menu, width, height);

  if(strcmp(menu->name, "field") == 0)
  {
    menu_field_resize(menu, field, width, height);
  }
}

/*
 *
 */
int screen_resize(screen_t* screen, field_t* field, int width, int height)
{
  SDL_RenderSetLogicalSize(screen->renderer, width, height);

  screen->width  = width;
  screen->height = height;

  for(int index = 0; index < screen->menu_count; index++)
  {
    menu_t* menu = screen->menus[index];

    menu_resize(menu, field, screen->width, screen->height);
  }
}

/*
 *
 */
void event_resize_handler(screen_t* screen, field_t* field, SDL_Event* event)
{
  screen_resize(screen, field, event->window.data1, event->window.data2);
}

