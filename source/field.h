/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#ifndef FIELD_H
#define FIELD_H

#include <stdlib.h>
#include <stdbool.h>

#include "debug.h"

typedef enum
{
  STATE_INTACT,  // Nothing has happend
  STATE_FLAGGED, // The user has flagged the square
  STATE_SWEPT    // The user has revealed (swept) the square
} square_state_t;

typedef struct square_t
{
  square_state_t state;  // The state of the square
  bool           mine;   // Mine is on square
  int            amount; // Amount of adjacent mines
} square_t;

typedef struct field_t
{
  int        width;
  int        height;
  int        max_flags;
  square_t** squares;
} field_t;

extern field_t* field_create(int width, int height, int mine_amount, int max_flags);

extern void     field_free(field_t** field);

#endif // FIELD_H
