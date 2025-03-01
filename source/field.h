/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#ifndef FIELD_H
#define FIELD_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "debug.h"

typedef enum
{
  STATE_INTACT,  // Nothing has happend
  STATE_FLAGGED, // User has flagged the square
  STATE_SWEPT    // User has revealed (swept) the square
} square_state_t;

typedef struct square_t
{
  int            windex; // Width position in minefield
  int            hindex; // Height position in minefield
  square_state_t state;  // State of the square
  bool           mine;   // Mine is on square
  union
  {
    bool exploded; // Mine has exploded
    int  amount;   // Amount of adjacent mines
  };
} square_t;

typedef enum
{
  GAME_ACTIVE, // Game is going on
  GAME_WON,    // Game is won
  GAME_LOST    // Game is lost 
} field_state_t;

typedef struct field_t
{
  int           width;
  int           height;
  int           mine_amount;
  int           swept_amount;
  int           max_flags;
  int           flag_amount;
  square_t**    squares;
  field_state_t state;
} field_t;

extern int square_sweep(field_t* field, square_t* square);

extern int square_flag(field_t* field, square_t* square);


extern void mines_reveal(field_t* field);


extern field_t* field_create(int width, int height, int mine_amount, int max_flags);

extern void     field_free(field_t** field);

#endif // FIELD_H
