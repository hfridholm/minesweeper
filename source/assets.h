/*
 * The assets struct is where all the assets is stored
 *
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-25
 */

#ifndef ASSETS_H
#define ASSETS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "debug.h"

/*
 *
 */
typedef struct assets_field_chunks_t
{
  Mix_Chunk* swept;
  Mix_Chunk* flagged;
} assets_field_chunks_t;

/*
 *
 */
typedef struct assets_field_surfaces_t
{
  SDL_Surface* background;
  SDL_Surface* digits[8];
  SDL_Surface* mine;
  SDL_Surface* exploded;
  SDL_Surface* intact;
  SDL_Surface* swept;
  SDL_Surface* flag;
} assets_field_surfaces_t;

/*
 *
 */
typedef struct assets_field_t
{
  assets_field_chunks_t   chunks;
  assets_field_surfaces_t surfaces;
} assets_field_t;

/*
 *
 */
typedef struct assets_banners_t
{
  SDL_Surface* background;
  SDL_Surface* expert;
  SDL_Surface* normal;
  SDL_Surface* stupid;
} assets_banners_t;

/*
 *
 */
typedef struct assets_chunks_t
{
  Mix_Chunk* lost;
  Mix_Chunk* won;
} assets_chunks_t;

/*
 *
 */
typedef struct assets_t
{
  TTF_Font*        font;
  assets_chunks_t  chunks;
  assets_banners_t banners;
  assets_field_t   field;
} assets_t;

#endif // ASSETS_H
