/*
 * minesweeper
 *
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-22
 */

#include "minesweeper.h"

#define FPS 10

/*
 *
 */
void game_routine(screen_t* screen, assets_t* assets, field_t* field)
{
  info_print("Start game routine");

  Uint32 start_ticks, last_ticks;


  game_render(screen, assets, field);

  bool running = true;

  SDL_Event event;

  while(running)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT) running = false;

      event_handler(screen, assets, field, &event);
    }

    start_ticks = SDL_GetTicks();

    // Only render the screen number of FPS
    if(start_ticks - last_ticks >= 1000 / FPS)
    {
      game_render(screen, assets, field);

      last_ticks = start_ticks;
    }
  }

  info_print("Stop game routine");
}

/*
 *
 */
int main(int argc, char* argv[])
{
  info_print("Start of main");

  field_t* field = field_create(8, 6, 10, 5);

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


  game_routine(screen, assets, field);


  assets_destroy(&assets);

  screen_destroy(&screen);

  field_free(&field);

  info_print("End of main");

  return 0;
}
