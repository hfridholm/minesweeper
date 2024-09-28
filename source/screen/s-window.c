/*
 * Written by Hampus Fridholm
 *
 * Last updated: 2024-09-23
 */

#include "../screen.h"

#include "s-intern.h"

/*
 *
 */
int window_child_add(window_t* window, window_t* child)
{
  if(!window || !child)
  {
    error_print("Bad input");
    
    return 1;
  }

  info_print("Adding child: %s", child->name);

  // 1. Add child to window
  window->children = realloc(window->children, sizeof(window_t*) * (window->child_count + 1));

  if(!window->children)
  {
    error_print("Failed to allocate added child");

    return 2;
  }

  window->children[window->child_count++] = child;

  // 2. Add references to child
  child->parent = window;

  info_print("Added child: %s", child->name);

  return 0;
}

/*
 *
 */
SDL_Renderer* window_renderer_get(window_t* window)
{
  if(!window)
  {
    error_print("Bad input");

    return NULL;
  }

  if(window->parent)
  {
    return window_renderer_get(window->parent);
  }
  else
  {
    return menu_renderer_get(window->menu);
  }
}

/*
 * Render text in window
 */
int window_text_render(window_t* window, const char* text, TTF_Font* font, SDL_Color color, SDL_Rect* rect)
{
  if(!window || !text || !font)
  {
    error_print("Bad input");

    return 1;
  }

  SDL_Renderer* renderer = window_renderer_get(window);

  if(!renderer)
  {
    error_print("Failed to get renderer from window %s", window->name);
    
    return 2;
  }

  render_target_text_render(renderer, window->texture, text, font, color, rect);

  return 0;
}

/*
 * Render texture to window
 *
 * The textures of child windows will be rendered over this texture
 */
int window_texture_render(window_t* window, SDL_Texture* texture, SDL_Rect* rect)
{
  if(!window || !texture)
  {
    error_print("Bad input");

    return 1;
  }

  SDL_Renderer* renderer = window_renderer_get(window);

  if(!renderer)
  {
    error_print("Failed to get renderer from window %s", window->name);
    
    return 2;
  }

  render_target_texture_render(renderer, window->texture, texture, rect);

  return 0;
}

/*
 * Render window with all of it's child windows
 */
int window_render(window_t* window)
{
  if(!window)
  {
    error_print("Bad input");

    return 1;
  }

  SDL_Renderer* renderer = window_renderer_get(window);

  if(!renderer)
  {
    error_print("Failed to get renderer from window %s", window->name);
    
    return 2;
  }

  for(int index = 0; index < window->child_count; index++)
  {
    window_t* child = window->children[index];

    window_render(child);

    render_target_texture_render(renderer, window->texture, child->texture, &child->rect);

    render_target_clear(renderer, child->texture);
  }

  return 0;
}

/*
 * Create window
 */
window_t* window_create(char* name, SDL_Rect rect)
{
  info_print("Creating window: %s", name);

  window_t* window = malloc(sizeof(window_t));
  memset(window, 0, sizeof(window_t));

  window->name = name;
  window->rect = rect;

  info_print("Created window: %s", name);

  return window;
}

/*
 * Destroy window
 */
void window_destroy(window_t** window)
{
  if(!window || !(*window)) return;

  info_print("Destroying window: %s", (*window)->name);

  for(int index = 0; index < (*window)->child_count; index++)
  {
    window_destroy(&(*window)->children[index]);
  }

  free((*window)->children);

  texture_destroy(&(*window)->texture);

  info_print("Destroyed window: %s", (*window)->name);

  free(*window);

  *window = NULL;
}
