/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-25
 */

#include "../field.h"

/*
 *
 */
void mines_reveal(field_t* field)
{
  for(int windex = 0; windex < field->width; windex++)
  {
    for(int hindex = 0; hindex < field->height; hindex++)
    {
      square_t* square = &field->squares[windex][hindex];

      if(square->mine && square->state == STATE_INTACT)
      {
        square->state = STATE_SWEPT;
      }
    }
  }
}

/*
 *
 */
static void index_remove(int* indexes, int count, int target)
{
  for(int index = target; index < (count - 1); index++)
  {
    indexes[index] = indexes[index + 1];
  }
}

/*
 * Place down some mines in the minefield
 */
static int mines_place(field_t* field, int mine_amount)
{
  int square_count = field->width * field->height;

  if(mine_amount < 0 || mine_amount > square_count)
  {
    error_print("Mine amount not valid");

    return 1;
  }

  // 1. Initialize array of indexes to pick from
  int indexes[square_count];

  for(int index = 0; index < square_count; index++)
  {
    indexes[index] = index;
  }

  for(int count = 0; count < mine_amount; count++)
  {
    int array_index = (rand() % (square_count - count));

    int square_index = indexes[array_index];

    int windex = square_index % field->width;
    int hindex = square_index / field->width;

    square_t* square = &field->squares[windex][hindex];

    square->mine     = true;
    square->exploded = false;

    index_remove(indexes, square_count, array_index);
  }

  return 0;
}

/*
 * Mark how many adjacent mines there are around a square
 */
static void square_mines_mark(field_t* field, int origo_windex, int origo_hindex)
{
  square_t* origo_square = &field->squares[origo_windex][origo_hindex];

  for(int windex = (origo_windex - 1); windex <= (origo_windex + 1); windex++)
  {
    for(int hindex = (origo_hindex - 1); hindex <= (origo_hindex + 1); hindex++)
    {
      if((windex < 0 || windex >= field->width)  ||
         (hindex < 0 || hindex >= field->height) ||
         (windex == origo_windex && hindex == origo_hindex)) continue;

      square_t* square = &field->squares[windex][hindex];

      if(square->mine) origo_square->amount++;
    }
  }
}

/*
 * Mark how many adjacent mines there are around every square in minefield
 */
static void mines_mark(field_t* field)
{
  for(int windex = 0; windex < field->width; windex++)
  {
    for(int hindex = 0; hindex < field->height; hindex++)
    {
      square_t* square = &field->squares[windex][hindex];

      if(!square->mine)
      {
        square_mines_mark(field, windex, hindex);
      }
    }
  }
}

/*
 * Create minefield
 */
field_t* field_create(int width, int height, int mine_amount, int max_flags)
{
  info_print("Creating minefield");
  
  field_t* field = malloc(sizeof(field_t));

  field->width     = width;
  field->height    = height;
  field->max_flags = max_flags;

  field->state = GAME_ACTIVE;

  field->squares = malloc(sizeof(square_t*) * width);

  for(int windex = 0; windex < width; windex++)
  {
    field->squares[windex] = malloc(sizeof(square_t) * height);

    for(int hindex = 0; hindex < height; hindex++)
    {
      square_t square =
      {
        .windex = windex,
        .hindex = hindex,
        .state  = STATE_INTACT,
        .mine   = false,
        .amount = 0
      };

      field->squares[windex][hindex] = square;
    }
  }

  mines_place(field, mine_amount);

  mines_mark(field);

  info_print("Created minefield");

  return field;
}

/*
 * Free minefield
 */
void field_free(field_t** field)
{
  if(!field || !(*field)) return;

  info_print("Freeing minefield");

  for(int windex = 0; windex < (*field)->width; windex++)
  {
    free((*field)->squares[windex]);
  }

  free((*field)->squares);

  free(*field);

  *field = NULL;

  info_print("Freed minefield");
}
