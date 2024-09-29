/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-25
 */

#include "../minesweeper.h"

#include "m-intern.h"

/*
 * PARAMS
 * - int menuw | Width  of menu field
 * - int menuh | Height of menu field
 */
static void menu_field_window_field_resize(window_t* window, assets_t* assets, field_t* field, int menuw, int menuh)
{
  info_print("menuw:%d menuh:%d", menuw, menuh);

  SDL_Rect rect = 
  {
    .w = (float) menuw / 1.2f,
    .h = (float) menuh / 1.2f
  };

  int squarew = (float) rect.w / (float) field->width;
  int squareh = (float) rect.h / (float) field->height;

  int squarel = MIN(squarew, squareh);

  int width  = squarel * field->width;
  int height = squarel * field->height;
  
  window->rect = (SDL_Rect)
  {
    .x = (float) (menuw - width ) / 2.0f,
    .y = (float) (menuh - height) / 2.0f,
    .w = width,
    .h = height
  };

  info_print("window rect x:%d y:%d w:%d h:%d",
             window->rect.x,
             window->rect.y,
             window->rect.w,
             window->rect.h);

  window_texture_resize(window, window->rect.w, window->rect.h);
}

/*
 *
 */
static void menu_field_window_result_resize(window_t* window, assets_t* assets, field_t* field, int menuw, int menuh)
{
  window->rect = (SDL_Rect)
  {
    .x = 0,
    .y = 0,
    .w = menuw,
    .h = menuh
  };

  window_texture_resize(window, window->rect.w, window->rect.h);
}

/*
 *
 */
static void menu_field_window_data_resize(window_t* window, assets_t* assets, field_t* field, int menuw, int menuh)
{
  window->rect = (SDL_Rect)
  {
    .x = 0,
    .y = 0,
    .w = (float) menuw /  1.0f,
    .h = (float) menuh / 10.0f
  };

  window_texture_resize(window, window->rect.w, window->rect.h);
}

/*
 *
 */
static void menu_field_resize(menu_t* menu, assets_t* assets, field_t* field, int screenw, int screenh)
{
  window_t* window_field = menu_window_get(menu, "field");

  if(window_field)
  {
    menu_field_window_field_resize(window_field, assets, field, screenw, screenh);
  }

  window_t* window_result = menu_window_get(menu, "result");

  if(window_result)
  {
    menu_field_window_result_resize(window_result, assets, field, screenw, screenh);
  }

  window_t* window_data = menu_window_get(menu, "data");

  if(window_data)
  {
    menu_field_window_data_resize(window_data, assets, field, screenw, screenh);
  }
}

/*
 *
 */
static void menu_resize(menu_t* menu, assets_t* assets, field_t* field, int screenw, int screenh)
{
  menu_texture_resize(menu, screenw, screenh);

  if(strcmp(menu->name, "field") == 0)
  {
    menu_field_resize(menu, assets, field, screenw, screenh);
  }
}

/*
 *
 */
int screen_resize(screen_t* screen, assets_t* assets, field_t* field, int width, int height)
{
  SDL_RenderSetLogicalSize(screen->renderer, width, height);

  screen->width  = width;
  screen->height = height;

  for(int index = 0; index < screen->menu_count; index++)
  {
    menu_t* menu = screen->menus[index];

    menu_resize(menu, assets, field, screen->width, screen->height);
  }
}

/*
 *
 */
void event_resize_handler(screen_t* screen, assets_t* assets, field_t* field, SDL_Event* event)
{
  screen_resize(screen, assets, field, event->window.data1, event->window.data2);
}

