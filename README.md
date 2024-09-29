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


## Rendering

You can render textures to the screen and menu directly, which will put them in the background. You can also render textures to windows. Depending on the structure of the windows and the window order, the textures will be rendered upon each other based on the hiarchy.

Both screen, menu and window have textures, which is local canvases that everything under in the hiarchy gets rendered to. For example, all of the menu windows's textures will be rendered to the menus texture when the screen is rendered.

## Structs
- screen_t | Screen
- assets_t | Loaded Textures and Sounds
- field_t  | Minefield

## Resizing

When resizing a window, the window will set it's size depending on the menu's size. When resizing a child window, the child window will set it's size to it's parent window's size. This allows groups of windows to be indipendently sized and moved around easily.
