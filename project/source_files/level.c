#include "../header_files/level.h"

level_t init_level (char *path_blocks, char *path_background, character_t *p, character_list_t *enemies, SDL_Renderer *renderer) {

  level_t l;
  int i = 0;
  SDL_Surface *temp;

  temp = IMG_Load(path_blocks);
  l.blocks_spritesheet = SDL_CreateTextureFromSurface(renderer, temp);
  if (l.blocks_spritesheet == NULL) {
    printf("Error during blocks_spritesheet image loading : %s\n", SDL_GetError());
  }
  //temp won't be used again
  SDL_FreeSurface(temp);

  //background image loading through the temp surface to a texture
  temp = IMG_Load(path_background);
  l.background = SDL_CreateTextureFromSurface(renderer, temp);
  if (l.background == NULL) {
    printf("Error during background image loading : %s\n", SDL_GetError());
  }
  //temp won't be used again
  SDL_FreeSurface(temp);

  FILE *txtFile = fopen(PATH_TXT_FILE, "r");
  if (txtFile == NULL) {
    printf("Error opening the txt file\n");
    exit(0);
  }

  block_t matrix[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT];
  char curr;
  block_t b;
  SDL_Rect hitbox = {0, 0, 16, 16};
  SDL_Rect spritesheet_pos = {0, 0, 16, 16};

  SDL_Rect cHitbox = {0, 0, IMG_WIDTH, IMG_HEIGHT};
  SDL_Rect cSpritePos = {0, 0, IMG_WIDTH, IMG_HEIGHT};

  int x = 0, y = 0;
  while ((curr = getc(txtFile)) != EOF && y < NB_BLOCKS_HEIGHT) {

    if (curr == '\n')
    {

      y++;
      x = 0;

    } else {

      hitbox.x = x * 16;
      hitbox.y = y * 16;
      b = set_block(hitbox, spritesheet_pos, 3);

      switch (curr) {

        case '0':
          spritesheet_pos.x = 0;
          spritesheet_pos.y = 0;
          b = set_block(hitbox, spritesheet_pos, Solid);
          break;

        case '1':
          spritesheet_pos.x = 16;
          spritesheet_pos.y = 0;
          b = set_block(hitbox, spritesheet_pos, Background);
          break;

        case '2':
          spritesheet_pos.x = 32;
          spritesheet_pos.y = 0;
          b = set_block(hitbox, spritesheet_pos, Foreground);
          break;

        case 'p':
          set_character_real_position(p, x * 16, (y * 16) - IMG_HEIGHT);
          break;

        case 'e':
          cHitbox.x = x * 16;
          cHitbox.y = (y * 16) - IMG_HEIGHT;
          *enemies = character_list_build(set_character(10, set_floatpoint(x * 16, (y * 16) - IMG_HEIGHT), set_vector(0.0, 0.0), cSpritePos, cHitbox, Enemy), *enemies);
          i++;
          break;

        default:
          break;

      }
      matrix[x][y] = b;
      x++;

    }

  }
  fclose(txtFile);

  int j;
  for (i = 0; i < NB_BLOCKS_WIDTH; i++) {
    for (j = 0; j < NB_BLOCKS_HEIGHT; j++) {

      set_level_block(&l, i, j, matrix[i][j]);

    }
  }

  return l;
}

/* SET */

level_t set_level (block_t blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT], SDL_Texture *blocks_spritesheet, SDL_Texture *background) {
  level_t l;

  int i, j;
  for (i = 0; i < NB_BLOCKS_WIDTH; i++) {
    for (j = 0; j < NB_BLOCKS_HEIGHT; j++) {

      set_level_block(&l, i, j, blocks[i][j]);

    }
  }

  set_level_blocks_spritesheet(&l, blocks_spritesheet);
  set_level_background(&l, background);

  return l;
}

void set_level_block (level_t *l, int x, int y, block_t b) {
  l->blocks[x][y] = b;

  return;
}

void set_level_blocks_spritesheet (level_t *l, SDL_Texture *blocks_spritesheet) {
  l->blocks_spritesheet = blocks_spritesheet;

  return;
}

void set_level_background (level_t *l, SDL_Texture *background) {
  l->background = background;

  return;
}

/* GET */

block_t get_level_block (level_t l, int x, int y) {

  return l.blocks[x][y];
}

SDL_Texture *get_level_blocks_spritesheet (level_t l) {

  return l.blocks_spritesheet;
}

SDL_Texture *get_level_background (level_t l) {

  return l.background;
}
