/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-25
 */

#include "../assets.h"

#include "a-intern.h"

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

  // assets->font = font_load("../assets/fonts/font.ttf", 24);

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

  // font_close(&(*assets)->font);

  free(*assets);

  info_print("Destroyed assets");
}
