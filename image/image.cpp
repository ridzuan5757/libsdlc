#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_surface.h"
#include "SDL_video.h"
#include <SDL.h>
#include <iostream>
#include <stdio.h>

// screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// starts up sdl and creates window
bool init();

// loads media
bool loadMedia();

// frees media and shuts down SDL
void close();

// window rendering
SDL_Window *gWindow = NULL;

// screen surface
SDL_Surface *gScreenSurface = NULL;

// image loader
SDL_Surface *gHelloWorld = NULL;

int main(int argc, char *args[]) {
  std::cout << "hello\n";
  if (!init()) {
    printf("Failed to initialize.\n");
  } else {
    if (!loadMedia()) {
    } else {
      std::cout << "media load success" << std::endl;
      SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

      // update the surface
      SDL_UpdateWindowSurface(gWindow);

      SDL_Event e;
      bool quit = false;
      while (quit == false) {
        while (SDL_PollEvent(&e)) {
          if (e.type == SDL_QUIT) {
            quit = true;
          }
        }
      }
    }
  }
  close();
  return 0;
}

bool init() {
  // initialization flag
  bool success = true;

  // initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // create window
    gWindow = SDL_CreateWindow("Image", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (gWindow == NULL) {
      printf("Window cannot be created. SDL_Error: %s\n.", SDL_GetError());
      success = false;
    } else {
      // get window surface
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }

  return success;
}

bool loadMedia() {
  // load success flag
  bool success = true;

  // load splash image
  gHelloWorld = SDL_LoadBMP("./hello_world.bmp");
  if (gHelloWorld == NULL) {
    printf("Unable to laod image %s. SDL Error: %s\n", "hello_world.bmp",
           SDL_GetError());
    success = true;
  }
  return success;
}

void close() {
  // deallocate surface
  SDL_FreeSurface(gHelloWorld);
  gHelloWorld = NULL;

  // destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  // quit sdl subsystem
  SDL_Quit();
}
