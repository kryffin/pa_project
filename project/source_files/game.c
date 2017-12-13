/*

game.c : contain every functions for the game creation

*/

#include "../header_files/game.h"

//create a new game
void create_game (game_t *g) {
  SDL_Surface *temp;

  //SDL initialization
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error while SDL initialization : %s\n", SDL_GetError());
    exit(1);
  }

  g->manager = malloc(sizeof(FPSmanager));
  g->event = malloc(sizeof(SDL_Event));

  SDL_initFramerate(g->manager);
  SDL_setFramerate(g->manager, SCREEN_FPS);

  //window initialization
  g->window = SDL_CreateWindow("MVt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
  if (g->window == NULL) {
    printf("Error during window creation : %s\n", SDL_GetError());
    exit(1);
  }

  //renderer initialization
  g->renderer = SDL_CreateRenderer(g->window, -1, SDL_RENDERER_ACCELERATED);
  if (g->renderer == NULL) {
    printf("Error during renderer creation : %s\n", SDL_GetError());
    exit(1);
  }
  //set the draw color of the renderer to black
  SDL_SetRenderDrawColor(g->renderer, 0, 0, 0, 255);

  //hide the computer cursor to only show the game's
  SDL_ShowCursor(SDL_DISABLE);

  IMG_Init(IMG_INIT_PNG);
  //cursor image loading through the temp surface to a texture
  temp = IMG_Load(PATH_CURSOR);
  g->cursor = SDL_CreateTextureFromSurface(g->renderer, temp);
  if (g->cursor == NULL) {
    printf("Error during cursor image loading : %s\n", SDL_GetError());
    exit(1);
  }
  SDL_FreeSurface(temp);
  temp = IMG_Load(PATH_SPRITES);
  g->spriteSheet = SDL_CreateTextureFromSurface(g->renderer, temp);
  if (g->spriteSheet == NULL) {
    printf("Error during sprite sheet image loading : %s\n", SDL_GetError());
    exit(1);
  }
  SDL_FreeSurface(temp);

  Mix_Init(MIX_INIT_MP3);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
  Mix_VolumeMusic(0);

  g->mouse_pos = set_intpoint(0, 0);

  g->mouse_btn = false;

  if (TTF_Init() != 0) {
    printf("Error while TTF initialization : %s\n", SDL_GetError());
    exit(1);
  }
  g->font = TTF_OpenFont(PATH_FONT, FONT_SIZE);
  if (g->font == NULL) {
    printf("Error opening the font : %s\n", SDL_GetError());
    exit(1);
  }

  init_palette2(g);

  floatpoint_t basePosition = set_floatpoint(0.0, 0.0);
  vector_t baseVelocity = set_vector(0.0, 0.0);
  SDL_Rect desRec = {0, 0, IMG_WIDTH, IMG_HEIGHT};
  g->player = set_character(PLAYER_BASE_HP, basePosition, baseVelocity, desRec, Player);

  g->quit = false;

  g->openMenu = false;

  reset_keys(g);

  g->menuMusic = Mix_LoadMUS(PATH_MENU_MUSIC);
  if (g->menuMusic == NULL) {
    printf("Error loading the menu music : %s\n", Mix_GetError());
    exit(1);
  }

  g->musicBox = set_music_box(PATH_RIFLE_SOUND_EFFECT, PATH_SHOTGUN_SOUND_EFFECT, PATH_MISSILE_SOUND_EFFECT);

  Mix_VolumeChunk(g->musicBox.rifleSoundEffect, 0);
  Mix_VolumeChunk(g->musicBox.shotgunSoundEffect, 0);
  Mix_VolumeChunk(g->musicBox.missileSoundEffect, 0);

  return;
}

//reset the player of the game
void reset_game(game_t *game) {
  floatpoint_t basePosition = set_floatpoint(0.0, 0.0);
  vector_t baseVelocity = set_vector(0.0, 0.0);
  SDL_Rect desRec = {0, 0, IMG_WIDTH, IMG_HEIGHT};
  projectile_list_free(game->player.projectiles);
  level_list_free(game->currLevel);
  game->player = set_character(PLAYER_BASE_HP, basePosition, baseVelocity, desRec, Player);

  reset_keys(game);

  return;
}

//reset the keys
void reset_keys (game_t *game) {
  int i = 0;
  for (i = 0; i < NB_MAX_KEYS; i++) {
    game->keys[i] = false;
  }
}

//initialize the palatte of colors
void init_palette2 (game_t *game) {

  game->colorPalette = (SDL_Color*)malloc(15 * sizeof(SDL_Color));
  if (game->colorPalette == NULL) {
    printf("Error allocating memory for the palette\n");
    exit(1);
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

//free a game
void free_game (game_t *g) {
  if (g->manager != NULL) free(g->manager);
  if (g->spriteSheet != NULL) SDL_DestroyTexture(g->spriteSheet);
  if (g->cursor != NULL) SDL_DestroyTexture(g->cursor);
  if (g->renderer != NULL) SDL_DestroyRenderer(g->renderer);
  if (g->window != NULL) SDL_DestroyWindow(g->window);
  if (g->event != NULL) free(g->event);
  if (g->font != NULL) TTF_CloseFont(g->font);
  if (g->colorPalette != NULL) free(g->colorPalette);
  if (g->menuMusic != NULL) Mix_FreeMusic(g->menuMusic);
  if (&g->musicBox != NULL) free_music_box(&g->musicBox);
  if (g != NULL) free(g);

  return;
}

//exit the game
void exit_game (game_t *g) {
  free_game(g);
  Mix_CloseAudio();
  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();

  return;
}
