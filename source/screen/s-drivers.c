/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#include "../screen.h"

#include "s-intern.h"

/*
 *
 */
int sdl_drivers_init(void)
{
  info_print("Initializing SDL drivers");

  if(SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    error_print("Failed to initialize SDL");
    error_print("SDL_Init: %s", SDL_GetError());

    return 1;
  }

  if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
  {
    error_print("Failed to initialize IMG");
    error_print("IMG_Init: %s", IMG_GetError());

    return 2;
  }

  if(TTF_Init() == -1)
  {
    error_print("Failed to initialize TTF");
    error_print("TTF_Init: %s", TTF_GetError());

    return 3;
  }

  if(Mix_Init(0) != 0)
  {
    error_print("Failed to initialize Mix");
    error_print("Mix_Init: %s", Mix_GetError());

    return 4;
  }

  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
  {
    error_print("Failed to open audio");
    error_print("Mix_OpenAudio: %s", Mix_GetError());

    return 5;
  }

  info_print("Initialized SDL drivers");

  return 0;
}

/*
 *
 */
void sdl_drivers_quit(void)
{
  info_print("Quitting SDL drivers");

  SDL_Quit();
  IMG_Quit();
  TTF_Quit();
  Mix_Quit();

  Mix_CloseAudio();

  info_print("Quitted SDL drivers");
}
