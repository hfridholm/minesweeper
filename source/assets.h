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
typedef struct assets_field_textures_t
{
  SDL_Texture* background;
  SDL_Texture* digits[8];
  SDL_Texture* mine;
  SDL_Texture* exploded;
  SDL_Texture* intact;
  SDL_Texture* swept;
  SDL_Texture* flag;
} assets_field_textures_t;

/*
 *
 */
typedef struct assets_field_t
{
  assets_field_chunks_t   chunks;
  assets_field_textures_t textures;
} assets_field_t;

/*
 *
 */
typedef struct assets_banners_t
{
  SDL_Texture* background;
  SDL_Texture* expert;
  SDL_Texture* normal;
  SDL_Texture* stupid;
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

extern assets_t* assets_create(SDL_Renderer* renderer);

extern void      assets_destroy(assets_t** assets);

extern SDL_Texture* texture_load(SDL_Renderer* renderer, const char* path);

extern void         texture_destroy(SDL_Texture** texture);

#endif // ASSETS_H
