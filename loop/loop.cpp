#include "SDL_error.h"
#include "SDL_events.h"
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

bool init();
bool loadMedia();
void close();

int main(int argc, char *argv[]) {
  if (!init()) {
    printf("Failed to initialize.\n");
  } else {
    if (!loadMedia()) {
      printf("Fail to load media.\n");
    } else {

      // main loop
      SDL_Event e;
      bool quit = false;
      while (!quit) {

        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          }
        }

        SDL_BlitSurface(splashSurface, NULL, surface, NULL);
        SDL_UpdateWindowSurface(window);
      }
    }
  }

  close();
  return 0;
}

bool init() {
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize. SDL_Error: %s\n.", SDL_GetError());
    success = false;
  } else {
    window = SDL_CreateWindow("Event", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      printf("SDL Window could not be created. SDL_Error: %s\n.",
             SDL_GetError());
      success = false;
    } else {
      surface = SDL_GetWindowSurface(window);
    }
  }
  return success;
}

bool loadMedia() {
  bool success = true;
  splashSurface = SDL_LoadBMP("./x.bmp");
  if (splashSurface == NULL) {
    printf("Unable to load splash image %s. SDL_Error: %s\n.", "./x.bmp",
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
