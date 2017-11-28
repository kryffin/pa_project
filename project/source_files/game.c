/*

game.c : contain every functions for the game creation

*/

#include "../header_files/game.h"

#define BASE_HP 10000
//create a new game
game_t *create_game () {
  SDL_Surface *temp;
  SDL_Texture *texture;
  game_t *g = malloc(sizeof(game_t));

  //SDL initialization
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error while SDL initialization : %s\n", SDL_GetError());
    exit(0);
  }

  g->manager = malloc(sizeof(FPSmanager));
  g->event = malloc(sizeof(SDL_Event));

  SDL_initFramerate(g->manager);
  SDL_setFramerate(g->manager, SCREEN_FPS);

  //window initialization
  g->window = SDL_CreateWindow("MVt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
  if (g->window == NULL) {
    printf("Error during window creation : %s\n", SDL_GetError());
    exit(0);
  }

  //renderer initialization
  g->renderer = SDL_CreateRenderer(g->window, -1, SDL_RENDERER_ACCELERATED);
  if (g->renderer == NULL) {
    printf("Error during renderer creation : %s\n", SDL_GetError());
    exit(0);
  }
  //set the draw color of the renderer to white
  SDL_SetRenderDrawColor(g->renderer, 255, 255, 255, 255);

  //hide the computer cursor to only show the game's
  SDL_ShowCursor(SDL_DISABLE);

  IMG_Init(IMG_INIT_PNG);
  //cursor image loading through the temp surface to a texture
  temp = IMG_Load(PATH_CURSOR);
  g->cursor = SDL_CreateTextureFromSurface(g->renderer, temp);
  if (g->cursor == NULL) {
    printf("Error during cursor image loading : %s\n", SDL_GetError());
    exit(0);
  }
  SDL_FreeSurface(temp);
  temp = IMG_Load(PATH_SPRITES);
  g->spriteSheet = SDL_CreateTextureFromSurface(g->renderer, temp);
  if (g->spriteSheet == NULL) {
    printf("Error during sprite sheet image loading : %s\n", SDL_GetError());
    exit(0);
  }
  SDL_FreeSurface(temp);
  IMG_Quit();

  g->mouse_pos = set_intpoint(0, 0);

  g->mouse_btn = false;

  if (TTF_Init() != 0) {
    printf("Error while TTF initialization : %s\n", SDL_GetError());
    exit(0);
  }
  g->font = TTF_OpenFont(PATH_FONT, FONT_SIZE);
  if (g->font == NULL) {
    printf("Error opening the font : %s\n", SDL_GetError());
    exit(0);
  }

  init_palette2(g);

  floatpoint_t basePosition = set_floatpoint(0.0, 0.0);
  vector_t baseVelocity = set_vector(0.0, 0.0);
  SDL_Rect desRec = {0, 0, IMG_WIDTH, IMG_HEIGHT};
  g->player = set_character(BASE_HP, basePosition, baseVelocity, desRec, desRec, Player);

  g->enemies = character_list_empty();

  desRec.w = BULLET_WIDTH;
  desRec.h = BULLET_HEIGHT;
  temp = IMG_Load(PATH_SPRITES);
  texture = SDL_CreateTextureFromSurface(g->renderer, temp);
  if (texture == NULL) {
    printf("Error during bullet image loading : %s\n", SDL_GetError());
    exit(0);
  }
  SDL_FreeSurface(temp);

  g->quit = false;

  g->keys[SDL_SCANCODE_A] = 0;
  g->keys[SDL_SCANCODE_D] = 0;
  g->keys[SDL_SCANCODE_SPACE] = 0;
  g->keys[SDL_SCANCODE_F] = 0;
  g->keys[SDL_SCANCODE_S] = 0;

  return g;
}

//initialize the palatte of colors
void init_palette2 (game_t *game) {

  game->colorPalette = (SDL_Color*)malloc(15 * sizeof(SDL_Color));
  if (game->colorPalette == NULL) {
    printf("Error allocating memory for the palette\n");
    exit(0);
  }

  //black
  game->colorPalette[0].r = 0;
  game->colorPalette[0].g = 0;
  game->colorPalette[0].b = 0;

  //white
  game->colorPalette[1].r = 255;
  game->colorPalette[1].g = 255;
  game->colorPalette[1].b = 255;

  //red
  game->colorPalette[2].r = 255;
  game->colorPalette[2].g = 0;
  game->colorPalette[2].b = 0;

  //green
  game->colorPalette[3].r = 0;
  game->colorPalette[3].g = 255;
  game->colorPalette[3].b = 0;

  //blue
  game->colorPalette[4].r = 0;
  game->colorPalette[4].g = 0;
  game->colorPalette[4].b = 255;

  //yellow
  game->colorPalette[5].r = 255;
  game->colorPalette[5].g = 255;
  game->colorPalette[5].b = 0;

  //purple
  game->colorPalette[6].r = 255;
  game->colorPalette[6].g = 0;
  game->colorPalette[6].b = 255;

  //cyan
  game->colorPalette[7].r = 0;
  game->colorPalette[7].g = 255;
  game->colorPalette[7].b = 255;

  //grey
  game->colorPalette[8].r = 128;
  game->colorPalette[8].g = 128;
  game->colorPalette[8].b = 128;

  //dark red
  game->colorPalette[9].r = 128;
  game->colorPalette[9].g = 0;
  game->colorPalette[9].b = 0;

  //light red
  game->colorPalette[10].r = 255;
  game->colorPalette[10].g = 128;
  game->colorPalette[10].b = 128;

  //dark green
  game->colorPalette[11].r = 0;
  game->colorPalette[11].g = 128;
  game->colorPalette[11].b = 0;

  //light green
  game->colorPalette[12].r = 128;
  game->colorPalette[12].g = 255;
  game->colorPalette[12].b = 128;

  //dark blue
  game->colorPalette[13].r = 0;
  game->colorPalette[13].g = 0;
  game->colorPalette[13].b = 128;

  //light blue
  game->colorPalette[14].r = 128;
  game->colorPalette[14].g = 128;
  game->colorPalette[14].b = 255;

  return;
}
