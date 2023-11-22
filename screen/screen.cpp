#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_image.h"
#include "SDL_surface.h"
#include "SDL_video.h"
#include <SDL.h>
#include <stdio.h>
#include <string>

bool init();
bool loadMedia();
SDL_Surface *loadSurface(std::string path);
void close();

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
      printf("SDL Window could not be created. SDL_Error: %s\n",
             SDL_GetError());
    } else {

      if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_Image could not initialize. SDL Error: %s\n.",
               SDL_GetError());
        success = false;
      } else {
        surface = SDL_GetWindowSurface(window);
      }
    }
  }
  return success;
}

bool loadMedia() {
  bool success = true;
  std::string fname = "./png.png";
  splashSurface = loadSurface(fname);
  if (splashSurface == NULL) {
    printf("Unable to load splash image %s. SDL_Error: %s\n.", fname.c_str(),
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

SDL_Surface *loadSurface(std::string path) {
  // final image
  SDL_Surface *optimizedSurface = NULL;

  // load image
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    printf("Unable to load image %s. SDL_Error: %s\n.", path.c_str(),
           SDL_GetError());
  } else {
    // convert surface to screen format
    optimizedSurface = SDL_ConvertSurface(loadedSurface, surface->format, 0);

    if (optimizedSurface == NULL) {
      printf("Unable to optimize image %s. SDL_Error: %s.\n", path.c_str(),
             SDL_GetError());
    }

    printf("optimize success\n");
    // destroy old loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  return optimizedSurface;
}

int main(int argc, char *args[]) {
  if (!init()) {
    printf("Failed to initialize.\n");
  } else {
    if (!loadMedia()) {
      printf("Failed to load media.\n");
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
