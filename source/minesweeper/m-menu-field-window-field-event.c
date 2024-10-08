/*
 * Handle an event inside the minefield window
 *
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-26
 */

#include "../minesweeper.h"

#include "m-intern.h"

/*
 * Get the local x and y coordinates of event in window
 *
 * RETURN (int status)
 * - 0 | Success
 * - 1 | Event is not inside window
 */
int event_window_x_and_y_get(int* x, int* y, window_t* window, SDL_Event* event)
{
  if(!event_is_inside_rect(event, &window->rect))
  {
    return 1;
  }

  *x = event->button.x - window->rect.x;
  *y = event->button.y - window->rect.y;

  return 0;
}

/*
 * Get the minefield square at the mouse location of event
 */
static square_t* event_square_get(window_t* window, field_t* field, SDL_Event* event)
{
  int x, y;

  if(event_window_x_and_y_get(&x, &y, window, event) != 0)
  {
    return NULL;
  }

  int windex = x * field->width  / window->rect.w;
  int hindex = y * field->height / window->rect.h;

  return &field->squares[windex][hindex];
}

/*
 *
 */
static void event_mouse_down_left_handler(window_t* window, assets_t* assets, field_t* field, SDL_Event* event)
{
  info_print("Minefield mouse down left");

  square_t* square = event_square_get(window, field, event);

  if(!square)
  {
    error_print("No square was clicked in minefield");

    return;
  }

  if(square_sweep(field, square) == 0 && !square->mine)
  {
    chunk_play(assets->field.chunks.swept);
  }
}

/*
 *
 */
static void event_mouse_down_right_handler(window_t* window, assets_t* assets, field_t* field, SDL_Event* event)
{
  info_print("Minefield mouse down right");

  square_t* square = event_square_get(window, field, event);

  if(!square)
  {
    error_print("No square was clicked in minefield");

    return;
  }

  if(square_flag(field, square) != 0)
  {
    chunk_play(assets->field.chunks.flagged);
  }
}

/*
 *
 */
static void event_mouse_down_handler(window_t* window, assets_t* assets, field_t* field, SDL_Event* event)
{
  switch(event->button.button)
  {
    case SDL_BUTTON_LEFT:
      event_mouse_down_left_handler(window, assets, field, event);
      break;

    case SDL_BUTTON_RIGHT:
      event_mouse_down_right_handler(window, assets, field, event);
      break;

    default:
      break;
  }
}

/*
 *
 */
static void event_mouse_up_left_handler(window_t* window, assets_t* assets, field_t* field, SDL_Event* event)
{
  info_print("Minefield mouse up left");
}

/*
 *
 */
static void event_mouse_up_right_handler(window_t* window, assets_t* assets, field_t* field, SDL_Event* event)
{
  info_print("Minefield mouse up right");
}

/*
 *
 */
static void event_mouse_up_handler(window_t* window, assets_t* assets, field_t* field, SDL_Event* event)
{
  switch(event->button.button)
  {
    case SDL_BUTTON_LEFT:
      event_mouse_up_left_handler(window, assets, field, event);
      break;

    case SDL_BUTTON_RIGHT:
      event_mouse_up_right_handler(window, assets, field, event);
      break;

    default:
      break;
  }
}

/*
 *
 */
void menu_field_window_field_event_handler(window_t* window, assets_t* assets, field_t* field, SDL_Event* event)
{
  switch(event->type)
  {
    case SDL_MOUSEBUTTONDOWN:
      event_mouse_down_handler(window, assets, field, event);
      break;

    case SDL_MOUSEBUTTONUP:
      event_mouse_up_handler(window, assets, field, event);
      break;

    default:
      break;
  }
}
