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
  int w = parentw;
  int h = (float) parenth / 3.f;

  window->rect = (SDL_Rect)
  {
    .x = 0,
    .y = h * 2,
    .w = w,
    .h = h
  };

  window_texture_resize(window, window->rect.w, window->rect.h);
}

/*
 *
 */
static void window_swept_resize(window_t* window, int parentw, int parenth)
{
  int w = parentw;
  int h = (float) parenth / 3.f;

  window->rect = (SDL_Rect)
  {
    .x = 0,
    .y = 0,
    .w = w,
    .h = h
  };

  window_texture_resize(window, window->rect.w, window->rect.h);
}

/*
 *
 */
static void window_flags_resize(window_t* window, int parentw, int parenth)
{
  int w = parentw;
  int h = (float) parenth / 3.f;

  window->rect = (SDL_Rect)
  {
    .x = 0,
    .y = h,
    .w = w,
    .h = h
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
    .w = (float) parentw * 0.25f,
    .h = parenth
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
