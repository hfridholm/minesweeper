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

  screen_render(screen);

  bool running = true;

  SDL_Event event;

  while(running && SDL_WaitEvent(&event))
  {
    if(event.type == SDL_QUIT)
    {
      running = false;
    }

    screen_render(screen);
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


  SDL_Texture* texture = texture_load(screen->renderer, "../assets/textures/background-field.png");

  window_texture_render(window, texture, NULL);

  texture_destroy(&texture);


  game_routine(screen);


  screen_destroy(&screen);

  info_print("End of main");

  return 0;
}
