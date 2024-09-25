/*
 * minesweeper
 *
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-22
 */

#include "minesweeper.h"

/*
 *
 */
void menu_field_render(screen_t* screen, assets_t* assets)
{
  menu_t* field_menu = screen_menu_get(screen, "field");

  if(!field_menu)
  {
    error_print("Field menu doesn't exist");

    return;
  }

  menu_texture_render(field_menu, assets->field.textures.background, NULL);

  window_t* field_window = menu_window_get(field_menu, "field");

  if(!field_window)
  {
    error_print("Field window diesn't exist");

    return;
  }

  window_texture_render(field_window, assets->field.textures.mine, NULL);
}

/*
 *
 */
void game_render(screen_t* screen, assets_t* assets)
{
  if(strcmp(screen->menu_name, "field") == 0)
  {
    menu_field_render(screen, assets);
  }

  screen_render(screen);
}

/*
 *
 */
void game_routine(screen_t* screen, assets_t* assets)
{
  info_print("Start game routine");

  game_render(screen, assets);

  bool running = true;

  SDL_Event event;

  while(running && SDL_WaitEvent(&event))
  {
    if(event.type == SDL_QUIT)
    {
      running = false;
    }

    game_render(screen, assets);
  }

  info_print("Stop game routine");
}

/*
 *
 */
int main(int argc, char* argv[])
{
  info_print("Start of main");

  screen_t* screen = screen_create(800, 600, "Minesweeper");

  assets_t* assets = assets_create(screen->renderer);


  int width, height;
  SDL_GetWindowSize(screen->window, &width, &height);

  menu_t*   menu   = menu_create("field");

  window_t* window = window_create("field", (SDL_Rect) {0, 0, width, height});

  SDL_Rect child_rect = {(float) width / 4, (float) height / 4, (float) width / 2, (float) height / 2};

  window_t* child  = window_create("child", child_rect);

  window_child_add(window, child);

  menu_window_add(menu, window);

  screen_menu_add(screen, menu);

  screen->menu_name = menu->name;


  game_routine(screen, assets);


  assets_destroy(&assets);

  screen_destroy(&screen);

  info_print("End of main");

  return 0;
}
