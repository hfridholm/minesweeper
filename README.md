# minesweeper

## Design

The game engine is divided up into different modules that handles different things; screen_t, assets_t, field_t.
screen_t is a screen that assets can be rendered to, nothing more.
assets_t is a database of assets to use.
field_t is the game representation, to base the rendering on.

The destroy functions takes in a pointer to the allocated pointer.
After the memory has been freed, the pointer is sat to NULL.
That prevents the pointer from being used wrongly.

Efficiency: Passing large structures by value can be inefficient because it involves copying the entire structure. By passing pointers, you avoid this overhead and simply pass the memory address.

Consistency: Many SDL functions and APIs use pointers for structures, so using pointers can make your code more consistent with the SDL library’s conventions.
