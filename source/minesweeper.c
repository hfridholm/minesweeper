/*
 * minesweeper
 *
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-22
 */

#include "minesweeper.h"

#define FPS 5

/*
 *
 */
void game_routine(screen_t* screen, assets_t* assets, field_t* field)
{
  info_print("Start game routine");

  Uint32 end_ticks, start_ticks;

  bool running = true;

  SDL_Event event;
  SDL_memset(&event, 0, sizeof(event)); // Initialize all fields to zero

  game_render(screen, assets, field);

  while(running)
  {
    while(running && field->state == GAME_ACTIVE)
    {
      while(SDL_PollEvent(&event))
      {
        if(event.type == SDL_QUIT)
        {
          running = false;

          break;
        }

        event_handler(screen, assets, field, &event);
      }

      end_ticks = SDL_GetTicks();

      // Only render the screen number of FPS
      if(end_ticks - start_ticks >= 1000 / FPS)
      {
        game_render(screen, assets, field);

        start_ticks = end_ticks;
      }
    }

    if(running)
    {
      if(field->state == GAME_LOST)
      {
        mines_reveal(field);
      }

      game_render(screen, assets, field);

      while(SDL_WaitEvent(&event))
      {
        if(event.type == SDL_QUIT)
        {
          running = false;

          break;
        }
      }
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

  if(sdl_drivers_init() != 0)
  {
    sdl_drivers_quit();

    return 1;
  }

  field_t* field = field_create(30, 16, 100, 30);

  screen_t* screen = screen_create(800, 600, "Minesweeper");

  assets_t* assets = assets_create(screen->renderer);


  int width, height;
  SDL_GetWindowSize(screen->window, &width, &height);

  menu_t* menu = menu_create("field");

  screen_menu_add(screen, menu);

  screen->menu_name = menu->name;


  menu_window_add(menu, window_create("field", (SDL_Rect) {0, 0, width, height}));

  menu_window_add(menu, window_create("data", (SDL_Rect) {0, 0, width, 40}));

  menu_window_add(menu, window_create("result", (SDL_Rect) {0, 0, width, height}));


  screen_resize(screen, assets, field, width, height);


  game_routine(screen, assets, field);


  assets_destroy(&assets);

  screen_destroy(&screen);

  field_free(&field);

  sdl_drivers_quit();

  info_print("End of main");

  return 0;
}
