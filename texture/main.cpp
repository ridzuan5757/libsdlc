#include "SDL_error.h"
#include "SDL_surface.h"
#include "SDL_video.h"
#include <SDL.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
SDL_Surface *splashSurface = NULL;

bool init() {
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize. SDL error: %s.\n", SDL_GetError());
    success = false;
  } else {
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
      printf("SDL window could not be created. SDL error: %s.\n",
             SDL_GetError());
      success = false;
    } else {
      surface = SDL_GetWindowSurface(window);
    }
  }
  return success;
}

SDL_Surface *loadSurface(std::string fpath) {
  SDL_Surface *optimizedSurface = NULL;
  SDL_Surface *loadedSurface = SDL_LoadBMP(fpath.c_str());

  if (loadedSurface == NULL) {
    printf("Unalbe to load %s image. SDL error: %s.\n", fpath.c_str(),
           SDL_GetError());
  } else {
    optimizedSurface = SDL_ConvertSurface(loadedSurface, surface->format, 0);

    if (optimizedSurface == NULL) {
      printf("Unable to optimize %s image. SDL_Error: %s.\n", fpath.c_str(),
             SDL_GetError());
    }

    printf("Optimization completed.");
    SDL_FreeSurface(loadedSurface);
  }
  return optimizedSurface;
}

bool loadMedia(std::string fpath) {
  bool success = true;
  splashSurface = loadSurface(fpath);

  if (splashSurface == NULL) {
    printf("Unable to load %s image. SDL error: %s.\n", fpath.c_str(),
           SDL_GetError());
    success = false;
  }
  return success;
}

void close() {
  SDL_FreeSurface(splashSurface);
  splashSurface = NULL;

  SDL_DestroyWindow(window);
  window = NULL;

  SDL_Quit();
}

int main(int arc, char *args[]) { return 0; }
