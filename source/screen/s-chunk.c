/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#include "../screen.h"

#include "s-intern.h"

/*
 * Load chunk
 */
Mix_Chunk* chunk_load(const char* file)
{
  Mix_Chunk* chunk = Mix_LoadWAV(file);

  if(!chunk)
  {
    error_print("Failed to load chunk at: %s", file);
    error_print("Mix_LoadWAV: %s", Mix_GetError());

    return NULL;
  }

  return chunk;
}

/*
 * Play chunk
 */
int chunk_play(Mix_Chunk* chunk)
{
  int status = Mix_PlayChannel(-1, chunk, 0);

  if(status == -1)
  {
    error_print("Failed to play chunk");
    error_print("Mix_PlayChannel: %s", Mix_GetError());
  }

  return status;
}

/*
 * Free chunk
 */
void chunk_free(Mix_Chunk** chunk)
{
  if(*chunk == NULL) return;

  Mix_FreeChunk(*chunk);

  *chunk = NULL;
}
