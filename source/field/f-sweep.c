/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-25
 */

#include "../field.h"

/*
 * Sweep adjacent squares
 */
static void adjacent_squares_sweep(field_t* field, square_t* square)
{
  for(int windex = (square->windex - 1); windex <= (square->windex + 1); windex++)
  {
    for(int hindex = (square->hindex - 1); hindex <= (square->hindex + 1); hindex++)
    {
      if((windex < 0 || windex >= field->width)  ||
         (hindex < 0 || hindex >= field->height) ||
         (windex == square->windex && hindex == square->hindex)) continue;

      square_t* next_square = &field->squares[windex][hindex];

      square_sweep(field, next_square);
    }
  }
}

/*
 * Sweep square, and adjacent squares if the square is empty
 *
 * EXPECT:
 * - field and square is allocated
 * - square is inside minefield
 *
 * Don't sweep square if it is flagged or already swept
 * 
 * If it is a mine, it will explode
 *
 * If the square is empty, sweep adjacent squares
 *
 * RETURN (int status)
 * - 0 | Success
 * - 1 | Square is flagged
 * - 2 | Square is already swept
 *
 * Note: Maybe change the return value to ex (int amount of swept squares)?
 */
int square_sweep(field_t* field, square_t* square)
{
  if(square->state == STATE_FLAGGED) return 1;

  if(square->state == STATE_SWEPT  ) return 2;

  square->state = STATE_SWEPT;

  if(square->mine)
  {
    square->exploded = true;

    field->state = GAME_LOST;
  }
  else if(square->amount == 0) 
  {
    adjacent_squares_sweep(field, square);
  }

  return 0;
}

/*
 * Flag square
 *
 * RETURN (int status)
 * - 0 | Nothing was done
 * - 1 | Flagged   square
 * - 2 | Unflagged square
 */
int square_flag(square_t* square)
{
  if(square->state == STATE_INTACT)
  {
    square->state = STATE_FLAGGED;

    return 1;
  }
  else if(square->state == STATE_FLAGGED)
  {
    square->state = STATE_INTACT;

    return 2;
  }

  return 0;
}
