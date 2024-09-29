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
int assets_banners_init(SDL_Renderer* renderer, assets_banners_t* banners)
{
  info_print("Initializing assets banners");

  banners->background = texture_load(renderer, "../assets/textures/background-banner.png");

  info_print("Initialized assets banners");

  return 0;
}

/*
 *
 */
void assets_banners_destroy(assets_banners_t* banners)
{
  info_print("Destroying assets banners");

  texture_destroy(&banners->background);

  info_print("Destroyed assets banners");
}
