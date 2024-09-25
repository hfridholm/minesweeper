/*
 * minesweeper
 *
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-22
 */

#include "minesweeper.h"

int main(int argc, char* argv[])
{
  info_print("Start of main");

  screen_t* screen = screen_create(800, 600, "Minesweeper");

  sleep(5);

  screen_destroy(&screen);

  info_print("End of main");

  return 0;
}
