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
static void square_swept_render(window_t* window, assets_t* assets, square_t square, SDL_Rect rect)
{
  assets_field_textures_t* textures = &assets->field.textures;

  window_texture_render(window, textures->swept, &rect);

  if(square.mine)
  {
    if(square.exploded)
    {
      window_texture_render(window, textures->exploded, &rect);
    }

    window_texture_render(window, textures->mine, &rect);
  }
  else
  {
    if(square.amount < 1 || square.amount > 8) return;

    int index = square.amount - 1;

    window_texture_render(window, textures->digits[index], &rect);
  }
}

/*
 *
 */
static void square_render(window_t* window, assets_t* assets, square_t square, SDL_Rect rect)
{
  assets_field_textures_t* textures = &assets->field.textures;

  switch(square.state)
  {
    case STATE_INTACT:
      window_texture_render(window, textures->intact, &rect);
      break;

    case STATE_FLAGGED:
      window_texture_render(window, textures->intact, &rect);

      window_texture_render(window, textures->flag, &rect);
      break;

    case STATE_SWEPT:
      square_swept_render(window, assets, square, rect);
      break;

    default:
      break;
  }
}

/*
 * Change index arguments to square
 */
SDL_Rect square_rect_get(window_t* window, field_t* field, int windex, int hindex)
{
  int width  = window->rect.w / field->width;
  int height = window->rect.h / field->height;

  return (SDL_Rect) {
    .w = width,
    .h = height,
    .x = windex * width,
    .y = hindex * height
  };
}

/*
 *
 */
static void minefield_render(window_t* window, assets_t* assets, field_t* field)
{
  for(int windex = 0; windex < field->width; windex++)
  {
    for(int hindex = 0; hindex < field->height; hindex++)
    {
      square_t square = field->squares[windex][hindex];

      SDL_Rect rect = square_rect_get(window, field, windex, hindex);

      square_render(window, assets, square, rect);
    }
  }
}

/*
 *
 */
void game_won_render(menu_t* menu, assets_t* assets, field_t* field)
{
  window_t* window = menu_window_get(menu, "result");

  if(window)
  {
    window_text_render(window, "You won!", assets->font, COLOR_GREEN, NULL, SIDE_CENTER, SIDE_CENTER);
  }

  chunk_play(assets->chunks.won);
}

/*
 *
 */
void game_lost_render(menu_t* menu, assets_t* assets, field_t* field)
{
  window_t* window = menu_window_get(menu, "result");

  if(window)
  {
    window_text_render(window, "You lost!", assets->font, COLOR_RED, NULL, SIDE_CENTER, SIDE_CENTER);
  }

  chunk_play(assets->chunks.lost);
}

Uint32 start_ticks = 0, end_ticks = 0;
int    frame_count = 0, fps = 0;

/*
 *
 */
static int current_fps_get(void)
{
  frame_count++;

  end_ticks = SDL_GetTicks();

  if(end_ticks - start_ticks >= 1000)
  {
    fps = (float) frame_count / (float) ((end_ticks - start_ticks) / 1000);

    frame_count = 0;
    start_ticks = end_ticks;
  }

  return fps;
}

/*
 *
 */
static void window_fps_render(window_t* window, assets_t* assets)
{
  int fps = current_fps_get();

  char string[32];

  sprintf(string, "FPS: %d", fps);

  window_text_render(window, string, assets->font, COLOR_WHITE, NULL, SIDE_LEFT, SIDE_TOP);
}

/*
 *
 */
static void window_swept_render(window_t* window, assets_t* assets, field_t* field)
{
  char string[32];

  int square_count = field->width * field->height;

  sprintf(string, "SWEPT: %03d/%03d", field->swept_amount, square_count - field->mine_amount);

  window_text_render(window, string, assets->font, COLOR_WHITE, NULL, SIDE_LEFT, SIDE_BOTTOM);
}

/*
 *
 */
static void window_flags_render(window_t* window, assets_t* assets, field_t* field)
{
  char string[32];

  sprintf(string, "FLAGS: %03d/%03d", field->flag_amount, field->max_flags);

  window_text_render(window, string, assets->font, COLOR_WHITE, NULL, SIDE_LEFT, SIDE_CENTER);
}

/*
 *
 */
static void menu_field_window_data_render(window_t* window, assets_t* assets, field_t* field)
{
  window_t* window_fps = window_child_get(window, "fps");

  if(window_fps)
  {
    window_fps_render(window_fps, assets);
  }

  window_t* window_swept = window_child_get(window, "swept");

  if(window_swept)
  {
    window_swept_render(window_swept, assets, field);
  }

  window_t* window_flags = window_child_get(window, "flags");

  if(window_flags)
  {
    window_flags_render(window_flags, assets, field);
  }
}

/*
 *
 */
static void menu_field_render(menu_t* menu, assets_t* assets, field_t* field)
{
  menu_texture_render(menu, assets->field.textures.background, NULL);

  window_t* window_field = menu_window_get(menu, "field");

  if(!window_field)
  {
    error_print("Field window diesn't exist");

    return;
  }

  minefield_render(window_field, assets, field);

  switch(field->state)
  {
    case GAME_WON:
      game_won_render(menu, assets, field);
      break;

    case GAME_LOST:
      game_lost_render(menu, assets, field);
      break;

    default:
      break;
  }

  window_t* window_data = menu_window_get(menu, "data");

  if(window_data)
  {
    menu_field_window_data_render(window_data, assets, field);
  }
}

/*
 * Render the screen
 */
void game_render(screen_t* screen, assets_t* assets, field_t* field)
{
  menu_t* menu = screen_menu_get(screen, screen->menu_name);

  if(!menu) return;

  if(strcmp(menu->name, "field") == 0)
  {
    menu_field_render(menu, assets, field);
  }

  screen_render(screen);
}
