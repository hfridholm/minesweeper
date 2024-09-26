/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-25
 */

#include "../field.h"

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

  field->squares = malloc(sizeof(square_t*) * width);

  for(int windex = 0; windex < width; windex++)
  {
    field->squares[windex] = malloc(sizeof(square_t) * height);

    for(int hindex = 0; hindex < height; hindex++)
    {
      square_t square =
      {
        .state  = STATE_INTACT,
        .mine   = true,
        .amount = 0
      };

      field->squares[windex][hindex] = square;
    }
  }

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
