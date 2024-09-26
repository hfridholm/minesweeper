/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#include "../assets.h"

#include "a-intern.h"

/*
 *
 */
TTF_Font* font_load(const char* file, int size)
{
  TTF_Font* font = TTF_OpenFont(file, size);

  if(!font)
  {
    error_print("Failed to load font at: %s", file);
    error_print("TTF_OpenFont: %s", TTF_GetError());

    return NULL;
  }

  return font;
}


/*
 *
 */
void font_close(TTF_Font** font)
{
  if(*font == NULL) return;

  TTF_CloseFont(*font);

  *font = NULL;
}
