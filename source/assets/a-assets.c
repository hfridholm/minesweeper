/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-25
 */

#include "../assets.h"

#include "a-intern.h"

/*
 *
 */
static void assets_chunks_init(assets_chunks_t* chunks)
{
  info_print("Initializing assets chunks");

  chunks->won  = chunk_load("../assets/sounds/game-won.wav");
  chunks->lost = chunk_load("../assets/sounds/game-lost.wav");

  info_print("Initialized assets chunks");
}

/*
 *
 */
static void assets_chunks_free(assets_chunks_t* chunks)
{
  info_print("Freeing assets chunks");

  chunk_free(&chunks->won);
  chunk_free(&chunks->lost);

  info_print("Freed assets chunks");
}

/*
 * Create assets
 */
assets_t* assets_create(SDL_Renderer* renderer)
{
  info_print("Creating assets");

  assets_t* assets = malloc(sizeof(assets_t));
  memset(assets, 0, sizeof(assets_t));

  assets_field_init(renderer,   &assets->field);
  assets_banners_init(renderer, &assets->banners);

  assets_chunks_init(&assets->chunks);

  assets->font = font_load("../assets/fonts/font.ttf", 24);

  info_print("Created assets");

  return assets;
}

/*
 * Destroy assets
 */
void assets_destroy(assets_t** assets)
{
  info_print("Destroying assets");

  assets_field_destroy(&(*assets)->field);
  assets_banners_destroy(&(*assets)->banners);

  assets_chunks_free(&(*assets)->chunks);

  font_close(&(*assets)->font);

  free(*assets);

  info_print("Destroyed assets");
}
