/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#include "../screen.h"

/*
 * Create menu
 */
menu_t* menu_create()
{
  info_print("Creating menu");

  menu_t* menu = malloc(sizeof(menu_t));

  info_print("Created menu");

  return menu;
}

/*
 * Destroy menu
 */
void menu_destroy(menu_t** menu)
{
  if(!menu || !(*menu)) return;

  info_print("Destroying menu");

  free(*menu);

  *menu = NULL;

  info_print("Destroyed menu");
}
