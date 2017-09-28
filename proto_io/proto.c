#include "proto.h"

int main () {

  //window
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;

  bool *quit = NULL;
  quit = (bool*)malloc(sizeof(bool));
  *quit = false;

  SDL_Rect source;
  source.y = 0;
  source.w = 32;
  source.h = 32;
  SDL_Rect destination;
  destination.w = 32;
  destination.h = 32;

  /*SDL_Event *event = NULL;
  event = (SDL_Event*)malloc(sizeof(SDL_Event));*/

  FILE *txtfile = fopen("./file.txt", "r");
  if (txtfile == NULL) {
    printf("error opening the text file\n");
    return EXIT_FAILURE;
  }

  SDL_Surface *temp = NULL;
  temp = (SDL_Surface*)malloc(sizeof(SDL_Surface));

  SDL_Texture *tiles;

  int *lig = NULL;
  lig = (int*)malloc(sizeof(int));
  *lig = 0;
  int *col = NULL;
  col = (int*)malloc(sizeof(int));
  *col = 0;

  char matrice[5][40];
  char c;

  SDL_Event *event = NULL;
  event = (SDL_Event*)malloc(sizeof(SDL_Event));

  /*************/

  //SDL initialization
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error while SDL initialization : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  //window initialization to 640x480
  window = SDL_CreateWindow("proto", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
  if (window == NULL) {
    printf("Error during window creating : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("Error during renderer creating : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  temp = SDL_LoadBMP("./tiles.bmp");
  if (temp == NULL) {
    printf("error loading the tiles : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  tiles = SDL_CreateTextureFromSurface(renderer, temp);
  if (tiles == NULL) {
    printf("Error during sprite sheet image loading : %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }
  free(temp);

  *lig = 0;
  *col = 0;

  while ((c = getc(txtfile)) != EOF) {
    if (c == '\n') {
      *lig += 1;
      *col = 0;
    } else {
      matrice[*lig][*col] = c;
      *col += 1;
    }
  }
  fclose(txtfile);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  for (*lig = 0; *lig < 5; *lig += 1 ) {
    for (*col = 0; *col < 40; *col += 1) {
      printf("%c", matrice[*lig][*col]);
      if (matrice[*lig][*col] == '0') {
        source.x = 32;
      } else if (matrice[*lig][*col] == '1') {
        source.x = 0;
      } else {
        source.x = 64;
      }
      destination.x = 32 * (*col);
      destination.y = 32 * (*lig);
      SDL_RenderCopy(renderer, tiles, &source, &destination);
    }
    printf("\n");
  }

  SDL_RenderPresent(renderer);

  while (*quit == false) {

    while (SDL_PollEvent(event)) {
      switch (event->type) {
        case SDL_QUIT:
          *quit = true;
          break;

        default:
          break;
      }
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(100);

  }

  /* FREE */

  SDL_Quit();

  return EXIT_SUCCESS;
}
