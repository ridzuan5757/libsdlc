#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_rect.h"
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
    printf("SDL could not initialize. SDL_Error: %s\n.", SDL_GetError());
    success = false;
  } else {
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
      printf("SDL window could not be created. SDL_Error: %s\n.",
             SDL_GetError());
    } else {
      surface = SDL_GetWindowSurface(window);
    }
  }
  return success;
}

SDL_Surface *loadSurface(std::string fpath) {
  SDL_Surface *optimizedSurface = NULL;
  SDL_Surface *loadedSurface = SDL_LoadBMP(fpath.c_str());

  if (loadSurface == NULL) {
    printf("Unable to load %s. SDL_Error: %s", fpath.c_str(), SDL_GetError());
  } else {
    optimizedSurface = SDL_ConvertSurface(loadedSurface, surface->format, 0);

    if (optimizedSurface == NULL) {
      printf("Unable to optimize image %s. SDL_Error: %s", fpath.c_str(),
             SDL_GetError());
    }

    printf("Optimization complete");
    SDL_FreeSurface(loadedSurface);
  }
  return optimizedSurface;
}

bool loadMedia(std::string fpath) {
  bool success = true;
  splashSurface = loadSurface(fpath);

  if (splashSurface == NULL) {
    printf("Unable to load image %s. SDL_Error: %s", fpath.c_str(),
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

int main(int argc, char *args[]) {
  if (!init()) {
    std::printf("Initialization failed.");
  } else {
    if (!loadMedia("./test.bmp")) {
      printf("Media load failed");
    } else {
      SDL_Event e;
      bool quit = false;

      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          }

          SDL_Rect stretchRect;
          stretchRect.x = 0;
          stretchRect.y = 0;
          stretchRect.w = SCREEN_WIDTH;
          stretchRect.h = SCREEN_HEIGHT;
          SDL_BlitScaled(splashSurface, NULL, surface, &stretchRect);
          SDL_UpdateWindowSurface(window);
        }
      }
    }
  }
  close();
  return 0;
}
