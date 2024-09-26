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
static int assets_field_chunks_init(assets_field_chunks_t* chunks)
{
  info_print("Initializing assets field chunks");

  chunks->swept   = chunk_load("../assets/sounds/square-swept.wav");
  chunks->flagged = chunk_load("../assets/sounds/square-flagged.wav");

  info_print("Initialized assets field chunks");

  return 0;
}

/*
 *
 */
static int assets_field_textures_init(SDL_Renderer* renderer, assets_field_textures_t* textures)
{
  info_print("Initializing assets field textures");

  textures->background = texture_load(renderer, "../assets/textures/background-field.png");
  textures->mine       = texture_load(renderer, "../assets/textures/symbol-mine.png");
  textures->flag       = texture_load(renderer, "../assets/textures/symbol-flag.png");
  textures->exploded   = texture_load(renderer, "../assets/textures/square-exploded.png");
  textures->swept      = texture_load(renderer, "../assets/textures/square-swept.png");
  textures->intact     = texture_load(renderer, "../assets/textures/square-intact.png");

  textures->digits[0]  = texture_load(renderer, "../assets/textures/symbol-one.png");
  textures->digits[1]  = texture_load(renderer, "../assets/textures/symbol-two.png");
  textures->digits[2]  = texture_load(renderer, "../assets/textures/symbol-three.png");
  textures->digits[3]  = texture_load(renderer, "../assets/textures/symbol-four.png");
  textures->digits[4]  = texture_load(renderer, "../assets/textures/symbol-five.png");
  textures->digits[5]  = texture_load(renderer, "../assets/textures/symbol-six.png");
  textures->digits[6]  = texture_load(renderer, "../assets/textures/symbol-seven.png");
  textures->digits[7]  = texture_load(renderer, "../assets/textures/symbol-eight.png");

  info_print("Initialized assets field textures");

  return 0;
}

/*
 *
 */
int assets_field_init(SDL_Renderer* renderer, assets_field_t* field)
{
  info_print("Initializing assets field");

  assets_field_chunks_init(&field->chunks);

  assets_field_textures_init(renderer, &field->textures);

  info_print("Initialized assets field");

  return 0;
}

/*
 *
 */
static void assets_field_textures_destroy(assets_field_textures_t* textures)
{
  info_print("Destroying assets field textures");

  texture_destroy(&textures->background);
  texture_destroy(&textures->mine);
  texture_destroy(&textures->flag);
  texture_destroy(&textures->swept);
  texture_destroy(&textures->exploded);
  texture_destroy(&textures->intact);

  for(int index = 0; index < 8; index++)
  {
    texture_destroy(&textures->digits[index]);
  }

  info_print("Destroyed assets field textures");
}

/*
 *
 */
static void assets_field_chunks_free(assets_field_chunks_t* chunks)
{
  info_print("Freeing assets field chunks");
  
  chunk_free(&chunks->flagged);
  chunk_free(&chunks->swept);

  info_print("Freed assets field chunks");
}

/*
 *
 */
void assets_field_destroy(assets_field_t* field)
{
  info_print("Destroying assets field");

  assets_field_textures_destroy(&field->textures);

  assets_field_chunks_free(&field->chunks);

  info_print("Destroyed assets field");
}
