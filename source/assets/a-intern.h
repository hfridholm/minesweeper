/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#ifndef A_INTERN_H
#define A_INTERN_H

#include "../assets.h"

extern SDL_Texture* texture_load(SDL_Renderer* renderer, const char* file);

extern void         texture_destroy(SDL_Texture** texture);


extern Mix_Chunk* chunk_load(const char* file);

extern void       chunk_free(Mix_Chunk** chunk);


extern TTF_Font* font_load(const char* file, int size);

extern void      font_close(TTF_Font** font);


extern int  assets_field_init(SDL_Renderer* renderer, assets_field_t* field);

extern void assets_field_destroy(assets_field_t* field);


extern int  assets_banners_init(SDL_Renderer* renderer, assets_banners_t* banners);

extern void assets_banners_destroy(assets_banners_t* banners);

#endif // A_INTERN_H
