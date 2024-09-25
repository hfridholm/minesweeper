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
void game_routine(screen_t* screen)
{
  info_print("Start game routine");

  bool running = true;

  SDL_Event event;

  while(running && SDL_WaitEvent(&event))
  {
    if(event.type == SDL_QUIT)
    {
      running = false;
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

  screen_t* screen = screen_create(800, 600, "Minesweeper");

  menu_t*   menu   = menu_create("field");

  window_t* window = window_create("field");

  menu_window_add(menu, window);

  screen_menu_add(screen, menu);


  game_routine(screen);


  screen_destroy(&screen);

  info_print("End of main");

  return 0;
}
