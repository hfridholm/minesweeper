/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#ifndef A_INTERN_H
#define A_INTERN_H

#include "../assets.h"

extern int  assets_field_init(SDL_Renderer* renderer, assets_field_t* field);

extern void assets_field_destroy(assets_field_t* field);


extern int  assets_banners_init(SDL_Renderer* renderer, assets_banners_t* banners);

extern void assets_banners_destroy(assets_banners_t* banners);

#endif // A_INTERN_H
