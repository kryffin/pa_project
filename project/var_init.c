#include "header.h"

int init_palette (SDL_Color **palette) {

  *palette = (SDL_Color*)malloc(15 * sizeof(SDL_Color));
  if (palette == NULL) {
    printf("Error allocating memory for the palette\n");
    return 0;
  }

  //black
  (*palette)[0].r = 0;
  (*palette)[0].g = 0;
  (*palette)[0].b = 0;

  //white
  (*palette)[1].r = 255;
  (*palette)[1].g = 255;
  (*palette)[1].b = 255;

  //red
  (*palette)[2].r = 255;
  (*palette)[2].g = 0;
  (*palette)[2].b = 0;

  //green
  (*palette)[3].r = 0;
  (*palette)[3].g = 255;
  (*palette)[3].b = 0;

  //blue
  (*palette)[4].r = 0;
  (*palette)[4].g = 0;
  (*palette)[4].b = 255;

  //yellow
  (*palette)[5].r = 255;
  (*palette)[5].g = 255;
  (*palette)[5].b = 0;

  //purple
  (*palette)[6].r = 255;
  (*palette)[6].g = 0;
  (*palette)[6].b = 255;

  //cyan
  (*palette)[7].r = 0;
  (*palette)[7].g = 255;
  (*palette)[7].b = 255;

  //grey
  (*palette)[8].r = 128;
  (*palette)[8].g = 128;
  (*palette)[8].b = 128;

  //dark red
  (*palette)[9].r = 128;
  (*palette)[9].g = 0;
  (*palette)[9].b = 0;

  //light red
  (*palette)[10].r = 255;
  (*palette)[10].g = 128;
  (*palette)[10].b = 128;

  //dark green
  (*palette)[11].r = 0;
  (*palette)[11].g = 128;
  (*palette)[11].b = 0;

  //light green
  (*palette)[12].r = 128;
  (*palette)[12].g = 255;
  (*palette)[12].b = 128;

  //dark blue
  (*palette)[13].r = 0;
  (*palette)[13].g = 0;
  (*palette)[13].b = 128;

  //light blue
  (*palette)[14].r = 128;
  (*palette)[14].g = 128;
  (*palette)[14].b = 255;

  return 1;

}

int init_font (TTF_Font **font) {

  if (TTF_Init() != 0) {
    printf("Error while TTF initialization : %s\n", SDL_GetError());
    return 0;
  }

  *font = TTF_OpenFont(PATH_FONT, FONT_SIZE);
  if (*font == NULL) {
    printf("Error opening the font : %s\n", SDL_GetError());
    return 0;
  }

  return 1;

}

int init_window (SDL_Window **window) {

  //window initialization
  *window = SDL_CreateWindow("MVt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
  if (*window == NULL) {
    printf("Error during window creating : %s\n", SDL_GetError());
    return 0;
  }

  return 1;

}

int init_renderer (SDL_Renderer **renderer, SDL_Window *window) {

  //renderer initialization
  *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (*renderer == NULL) {
    printf("Error during renderer creating : %s\n", SDL_GetError());
    return 0;
  }

  //set the draw color of the renderer to white
  SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);

  return 1;

}

int init_sdl (SDL_Window **window, SDL_Renderer **renderer) {

  //SDL initialization
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error while SDL initialization : %s\n", SDL_GetError());
    return 0;
  }

  //hide the computer cursor to only show the game's
  SDL_ShowCursor(SDL_DISABLE);

  if (init_window(window) == 0) {
    return 0;
  }

  if (init_renderer(renderer, *window) == 0) {
    return 0;
  }

  return 1;

}

int init_images (SDL_Surface **temp, SDL_Texture **player_tSprite, SDL_Texture **cursor, SDL_Texture **blocks_spritesheet, SDL_Texture **background, SDL_Renderer *renderer) {

  IMG_Init(IMG_INIT_PNG);

  //spritesheet image loading through the temp surface to a texture
  *temp = IMG_Load(PATH_SPRITES);
  *player_tSprite = SDL_CreateTextureFromSurface(renderer, *temp);
  if (*player_tSprite == NULL) {
    printf("Error during sprite sheet image loading : %s\n", IMG_GetError());
    return 0;
  }

  //freeing the temp to use it again
  SDL_FreeSurface(*temp);

  //cursor image loading through the temp surface to a texture
  *temp = IMG_Load(PATH_CURSOR);
  *cursor = SDL_CreateTextureFromSurface(renderer, *temp);
  if (*cursor == NULL) {
    printf("Error during cursor image loading : %s\n", SDL_GetError());
    return 0;
  }

  //temp won't be used again
  SDL_FreeSurface(*temp);

  //blocks_spritesheet image loading through the temp surface to a texture
  *temp = IMG_Load(PATH_BLOCKS_SHEET);
  *blocks_spritesheet = SDL_CreateTextureFromSurface(renderer, *temp);
  if (*blocks_spritesheet == NULL) {
    printf("Error during blocks_spritesheet image loading : %s\n", SDL_GetError());
    return 0;
  }

  //temp won't be used again
  SDL_FreeSurface(*temp);

  //background image loading through the temp surface to a texture
  *temp = IMG_Load(PATH_BACKGROUND);
  *background = SDL_CreateTextureFromSurface(renderer, *temp);
  if (*background == NULL) {
    printf("Error during background image loading : %s\n", SDL_GetError());
    return 0;
  }

  //temp won't be used again
  SDL_FreeSurface(*temp);

  IMG_Quit();

  return 1;

}

int init_projectiles (projectile_t *projectiles[100], SDL_Texture *img, int x, int y) {

  //main projectiles
  *projectiles = (projectile_t *)malloc(100 * sizeof(projectile_t ));
  if (*projectiles == NULL) {
    printf("Error allocating memory for the projectiles\n");
    return 0;
  }

  vector_t *dir = NULL;
  dir = (vector_t*)malloc(sizeof(vector_t));
  *dir = set_vector(0.0, 0.0);

  SDL_Rect *hitbox = NULL;
  hitbox = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  hitbox->x = 0;
  hitbox->y = 0;
  hitbox->w = 16;
  hitbox->h = 16;

  SDL_Rect *spritePos = NULL;
  spritePos = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  spritePos->x = x;
  spritePos->y = y;
  spritePos->w = 16;
  spritePos->h = 16;

  int *i = NULL;
  i = (int*)malloc(sizeof(int));

  for (*i = 0; *i < 100; *i += 1) {
    (*projectiles)[*i] = set_projectile(0.0, 0.0, *dir, *hitbox, *spritePos, img);
  }

  free(dir);
  free(hitbox);
  free(spritePos);
  free(i);

  return 1;
}

int init_variables (Uint32 **initTimer, FPSmanager **manager, SDL_Window **window, SDL_Renderer **renderer, intpoint_t **mouse_pos, SDL_Event **event, bool **jumped, bool **mouse_btn, int **i, TTF_Font **font, SDL_Color **palette, player_t **p, projectile_t **projectiles, int **stepDelay, bool **quit, SDL_Surface **temp, SDL_Texture **player_tSprite, SDL_Texture **cursor, Uint32 **timeN_A, Uint32 **timeN_B, level_t **currLevel, SDL_Texture **blocks_spritesheet, SDL_Texture **background, player_t **enemies, projectile_t **enemyProjectiles) {

  //used to print the initialization time
  *initTimer = (Uint32*)malloc(sizeof(Uint32));
  if (*initTimer == NULL) {
    printf("Error allocating memory for the initTimer\n");
    return 0;
  }
  **initTimer = SDL_GetTicks(); //init the timer to the current time

  //used to manage the fps
  *manager = (FPSmanager*)malloc(sizeof(FPSmanager));
  if (*manager == NULL) {
    printf("Error allocating memory for the manager\n");
    return 0;
  }
  SDL_initFramerate(*manager);
  SDL_setFramerate(*manager, SCREEN_FPS);

  //initialization of sdl, window and renderer
  if (init_sdl(window, renderer) == 0) {
    return 0;
  }

  //mouse position
  *mouse_pos = (intpoint_t*)malloc(sizeof(intpoint_t));
  if (*mouse_pos == NULL) {
    printf("Error allocating memory for the mouse_pos\n");
    return 0;
  }
  **mouse_pos = set_intpoint(0, 0);

  //event running the controls
  *event = (SDL_Event*)malloc(sizeof(SDL_Event));
  if (*event == NULL) {
    printf("Error allocating memory for the event\n");
    return 0;
  }

  //keeps track of the jump
  *jumped = (bool*)malloc(sizeof(bool));
  if (*jumped == NULL) {
    printf("Error allocating memory for the jumped\n");
    return 0;
  }
  **jumped = false;

  //button pushed or not
  *mouse_btn = (bool*)malloc(sizeof(bool));
  if (*mouse_btn == NULL) {
    printf("Error allocating memory for the mouse_btn\n");
    return 0;
  }
  **mouse_btn = false;

  //simple counter
  *i = (int*)malloc(sizeof(int));
  if (*i == NULL) {
    printf("Error allocating memory for the i\n");
    return 0;
  }
  **i = 0;

  //initialization of the font
  if (init_font(font) == 0) {
    return 0;
  }

  //initialization of the color palette
  if (init_palette(palette) == 0) {
    return 0;
  }

  //main player_t
  *p = (player_t*)malloc(sizeof(player_t));
  if (*p == NULL) {
    printf("Error allocating memory for the player\n");
    return 0;
  }

  //enemies
  *enemies = (player_t*)malloc(10 * sizeof(player_t));
  if (*enemies == NULL) {
    printf("Error allocating memory for the enemies\n");
    return 0;
  }

  //delay between each sprite step
  *stepDelay = (int*)malloc(sizeof(int));
  if (*stepDelay == NULL) {
    printf("Error allocating memory for the stepDelay\n");
    return 0;
  }
  **stepDelay = 0;

  //main boolean running the game
  *quit = (bool*)malloc(sizeof(bool));
  if (*quit == NULL) {
    printf("Error allocating memory for the quit\n");
    return 0;
  }
  **quit = false;

  //initialization of the sprite sheet and cursor
  if (init_images(temp, player_tSprite, cursor, blocks_spritesheet, background, *renderer) == 0) {
    return 0;
  }

  if (init_projectiles(projectiles, *player_tSprite, 128, 64) == 0) {
    return 0;
  }

  if (init_projectiles(enemyProjectiles, *player_tSprite, 144, 64) == 0) {
    return 0;
  }

  *timeN_A = (Uint32*)malloc(sizeof(Uint32));
  if (*timeN_A == NULL) {
    printf("Error allocating memory for the timeN_A\n");
    return 0;
  }

  *timeN_B = (Uint32*)malloc(sizeof(Uint32));
  if (*timeN_B == NULL) {
    printf("Error allocating memory for the timeN_B\n");
    return 0;
  }

  *currLevel = (level_t*)malloc(sizeof(level_t));
  if (*currLevel == NULL) {
    printf("Error allocating memory for the level\n");
    return 0;
  }

  return 1;

}

void free_variables (SDL_Texture *player_tSprite, SDL_Renderer *renderer, SDL_Window *window, TTF_Font *font, int *i, projectile_t *projectiles, player_t *p, FPSmanager *manager, SDL_Color *colorPalette, SDL_Event *event, bool *quit, bool *jumped, intpoint_t *mouse_pos, bool *mouse_btn, Uint32 *timeN_A, Uint32 *timeN_B, level_t *currLevel, SDL_Texture *blocks_spritesheet, SDL_Texture *background, int *stepDelay, player_t *enemies, projectile_t *enemyProjectiles) {

  SDL_DestroyTexture(player_tSprite);
  SDL_DestroyTexture(blocks_spritesheet);
  SDL_DestroyTexture(background);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_CloseFont(font);

  TTF_Quit();
  SDL_Quit();

  free(i);
  free(projectiles);
  free(p);
  free(manager);
  free(colorPalette);
  free(event);
  free(quit);
  free(jumped);
  free(mouse_pos);
  free(mouse_btn);
  free(timeN_A);
  free(timeN_B);
  free(currLevel);
  free(stepDelay);
  free(enemies);
  free(enemyProjectiles);

  return;
}
