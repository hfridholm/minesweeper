/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-25
 */

#include "../minesweeper.h"

#include "m-intern.h"

/*
 * PARAMS
 * - int parentw | Width  of menu field
 * - int parenth | Height of menu field
 */
static void menu_field_window_field_resize(window_t* window, field_t* field, int parentw, int parenth)
{
  SDL_Rect rect = 
  {
    .w = (float) parentw / 1.1f,
    .h = (float) parenth / 1.1f
  };

  int squarew = (float) rect.w / (float) field->width;
  int squareh = (float) rect.h / (float) field->height;

  int squarel = MIN(squarew, squareh);

  int width  = squarel * field->width;
  int height = squarel * field->height;
  
  window->rect = (SDL_Rect)
  {
    .x = (float) (parentw - width ) / 2.0f,
    .y = (float) (parenth - height) / 2.0f,
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

