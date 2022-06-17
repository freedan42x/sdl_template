#include "SDL2/SDL.h"
#include <stdbool.h>

#define WIDTH 1366
#define HEIGHT 768
#define FPS 30

void *checknull(void *result)
{
  if (result == NULL) {
    fprintf(stderr, "ERROR: %s", SDL_GetError());
    exit(1);
  }
  return result;
}

void checkneg(int result)
{
  if (result < 0) (void) checknull(NULL);
}

int main(void)
{
  checkneg(SDL_Init(SDL_INIT_VIDEO));

  SDL_Window *window = checknull(SDL_CreateWindow(
				   "Title",
				   SDL_WINDOWPOS_UNDEFINED,
				   SDL_WINDOWPOS_UNDEFINED,
				   WIDTH,
				   HEIGHT,
				   SDL_WINDOW_FULLSCREEN_DESKTOP));

  SDL_Renderer *renderer = checknull(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
  checkneg(SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT));

  bool shouldQuit = false;
  while (!shouldQuit) {
    Uint64 start = SDL_GetPerformanceCounter();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
	shouldQuit = true;
	break;
      }
    }
    
    checkneg(SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255));
    checkneg(SDL_RenderClear(renderer));
    SDL_RenderPresent(renderer);

    Uint64 end = SDL_GetPerformanceCounter();
    float elapsed = (end - start) / (float) SDL_GetPerformanceFrequency() * 1000;
    SDL_Delay(floor(1000.0f / FPS - elapsed));
  }
  
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return 0;
}
