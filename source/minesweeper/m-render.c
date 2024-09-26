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
  SDL_Texture* texture = text_texture_create(menu->screen->renderer, "Won!", assets->font, COLOR_GREEN);

  menu_texture_render(menu, texture, NULL);

  info_print("Game won!");
}

/*
 *
 */
void game_lost_render(menu_t* menu, assets_t* assets, field_t* field)
{
  SDL_Texture* texture = text_texture_create(menu->screen->renderer, "Lost!", assets->font, COLOR_RED);

  menu_texture_render(menu, texture, NULL);

  info_print("Game lost!");
}

/*
 *
 */
static void menu_field_render(screen_t* screen, assets_t* assets, field_t* field)
{
  menu_t* menu = screen_menu_get(screen, "field");

  if(!menu)
  {
    error_print("Field menu doesn't exist");

    return;
  }

  menu_texture_render(menu, assets->field.textures.background, NULL);

  window_t* field_window = menu_window_get(menu, "field");

  if(!field_window)
  {
    error_print("Field window diesn't exist");

    return;
  }

  minefield_render(field_window, assets, field);

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
}

/*
 * Render the screen
 */
void game_render(screen_t* screen, assets_t* assets, field_t* field)
{
  if(strcmp(screen->menu_name, "field") == 0)
  {
    menu_field_render(screen, assets, field);
  }

  screen_render(screen);
}
