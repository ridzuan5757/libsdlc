// Using SDL and standard IO
#include "SDL_video.h"
#include <SDL.h>
#include <stdio.h>

// screen dimension constant
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *args[]) {
  // Window that will be rendered
  SDL_Window *window = NULL;

  // Surface contained by the window
  SDL_Surface *screenSurface = NULL;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  } else {
    // Create window
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    } else {
      // get window Surface
      screenSurface = SDL_GetWindowSurface(window);

      // fill the surface white
      SDL_FillRect(screenSurface, NULL,
                   SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

      // update the surface
      SDL_UpdateWindowSurface(window);

      // force window to stay up
      SDL_Event e;
      bool quit = false;
      while (!quit) {
        while (SDL_PollEvent(&e)) {
          if (e.type == SDL_QUIT) {
            quit = true;
          }
        }
      }
    }
  }

  // Destroy window
  SDL_DestroyWindow(window);

  // Quit SDL subsystem
  SDL_Quit();

  return 0;
}
