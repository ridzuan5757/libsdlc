#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_surface.h"
#include "SDL_video.h"
#include <SDL.h>
#include <stdio.h>
#include <string>

enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gCurrentSurface = NULL;
SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

bool init() {
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL cannot be initialized, SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window cannot be created, SDL_Error: %s.\n", SDL_GetError());
      success = false;
    } else {
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }
  return success;
}

SDL_Surface *loadSurface(std::string path) {
  SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
  if (loadedSurface == NULL) {
    printf("Unable to load image %s. SDL_Error: %s\n.", path.c_str(),
           SDL_GetError());
  }
  return loadedSurface;
}

bool loadMedia() {
  bool success = true;

  gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("./press.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
    printf("Failed to load default image.\n");
    success = false;
  }

  gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("./up.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
    printf("Failed to load up image.\n");
    success = false;
  }

  gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("./down.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
    printf("Failed to load default image.\n");
    success = false;
  }

  gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("./left.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
    printf("Failed to load default image.\n");
    success = false;
  }

  gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("./right.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
    printf("Failed to load default image.\n");
    success = false;
  }

  return success;
}

void close() {
  SDL_FreeSurface(gCurrentSurface);
  gCurrentSurface = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  SDL_Quit();
}

int main(int argc, char *args[]) {
  if (!init()) {
    printf("Failed to initialize.\n");
  } else {
    if (!loadMedia()) {
      printf("Failed to load media.\n");
    } else {

      // load init splash image
      gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

      bool quit = false;
      SDL_Event e;
      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {

            case SDLK_UP:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
              break;

            case SDLK_DOWN:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
              break;

            case SDLK_LEFT:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
              break;

            case SDLK_RIGHT:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
              break;

            default:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
              break;
            }
          }
        }

        SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
        SDL_UpdateWindowSurface(gWindow);
      }
    }
  }
  close();
  return 0;
}
