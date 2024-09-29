/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-25
 */

#include "../minesweeper.h"

#include "m-intern.h"

/*
 *
 */
static void window_fps_resize(window_t* window, int parentw, int parenth)
{
  int width  = (float) parentw / 1.0f;
  int height = (float) parenth / 3.0f;

  window->rect = (SDL_Rect)
  {
    .x = 0,
    .y = height * 2,
    .w = width,
    .h = height
  };

  window_texture_resize(window, window->rect.w, window->rect.h);
}

/*
 *
 */
static void window_swept_resize(window_t* window, int parentw, int parenth)
{
  int width  = (float) parentw / 1.0f;
  int height = (float) parenth / 3.0f;

  window->rect = (SDL_Rect)
  {
    .x = 0,
    .y = 0,
    .w = width,
    .h = height
  };

  window_texture_resize(window, window->rect.w, window->rect.h);
}

/*
 *
 */
static void window_flags_resize(window_t* window, int parentw, int parenth)
{
  int width  = (float) parentw / 1.0f;
  int height = (float) parenth / 3.0f;

  window->rect = (SDL_Rect)
  {
    .x = 0,
    .y = height,
    .w = width,
    .h = height
  };

  window_texture_resize(window, window->rect.w, window->rect.h);
}

/*
 *
 */
void menu_field_window_data_resize(window_t* window, int parentw, int parenth)
{
  window->rect = (SDL_Rect)
  {
    .x = 0,
    .y = 0,
    .w = (float) parentw /  1.0f,
    .h = (float) parenth / 10.0f
  };

  window_texture_resize(window, window->rect.w, window->rect.h);

  window_t* window_swept = window_child_get(window, "swept");

  if(window_swept)
  {
    window_swept_resize(window_swept, window->rect.w, window->rect.h);
  }

  window_t* window_flags = window_child_get(window, "flags");

  if(window_flags)
  {
    window_flags_resize(window_flags, window->rect.w, window->rect.h);
  }

  window_t* window_fps = window_child_get(window, "fps");

  if(window_fps)
  {
    window_fps_resize(window_fps, window->rect.w, window->rect.h);
  }
}
