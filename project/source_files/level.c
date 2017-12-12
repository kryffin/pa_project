/*

level.c : every functions regarding the levels

*/

#include "../header_files/level.h"

//free the head of a level list
void free_level (level_list_t l) {
  SDL_DestroyTexture(l->head.background);
  SDL_DestroyTexture(l->head.blocks_spritesheet);
  character_list_free(l->head.enemies);
  Mix_FreeMusic(l->head.levelMusic);
  free(l);

  return;
}

//go to next level if enemies are all dead
level_list_t next_level (level_list_t l, int *flag) {

  //if the next level isn't empty and there are no more enemies
  if (!level_list_is_empty(level_list_rest(l)) && character_list_is_empty(l->head.enemies)) {

    level_list_t tmp = level_list_rest(l);
    free_level(l);

    *flag = 1;

    return tmp;
  }

  *flag = 0;

  return l;
}

//set the level music
void set_level_music (level_t *l, char *path) {
  l->levelMusic = Mix_LoadMUS(path);
  if (l->levelMusic == NULL) {
    printf("Error while setting level music : %s\n", Mix_GetError());
    exit(0);
  }

  return;
}

//read the txt file to complete the block array, create the enemies and place the player
level_t init_level (char *path_blocks, char *path_background, char *path_file, char *path_music, character_t *p, SDL_Renderer *renderer) {

  level_t l;
  int i = 0;
  SDL_Surface *temp;

  /* loading */

  //loading the blocks srpite sheet for this level
  temp = IMG_Load(path_blocks);
  l.blocks_spritesheet = SDL_CreateTextureFromSurface(renderer, temp);
  if (l.blocks_spritesheet == NULL) {
    printf("Error during blocks_spritesheet image loading : %s\n", SDL_GetError());
    exit(1);
  }
  SDL_FreeSurface(temp);

  //loading the background image
  temp = IMG_Load(path_background);
  l.background = SDL_CreateTextureFromSurface(renderer, temp);
  if (l.background == NULL) {
    printf("Error during background image loading : %s\n", SDL_GetError());
    exit(1);
  }
  SDL_FreeSurface(temp);

  l.enemies = character_list_empty();

  //loading the txt file
  FILE *txtFile = fopen(path_file, "r");
  if (txtFile == NULL) {
    printf("Error opening the txt file\n");
    exit(1);
  }

  //the array of block that we will fill
  block_t matrix[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT];

  //the current char
  char curr;

  //the block to add to the array
  block_t b;

  //hitbox of the block
  SDL_Rect hitbox = {0, 0, BLOCK_SIZE, BLOCK_SIZE};

  //the position on the sprite sheet
  SDL_Rect spritesheet_pos = {0, 0, 16, 16};

  //hitbox and position used for the enemies
  SDL_Rect cSpritePos = {0, 0, IMG_WIDTH, IMG_HEIGHT};

  /* reading */

  //x is the column and y the line
  int x = 0, y = 0;

  //while the txt file isn't finished
  while ((curr = getc(txtFile)) != EOF && y < NB_BLOCKS_HEIGHT) {

    if (curr == '\n')
    {

      //new line
      y++;
      x = 0;

    } else {

      //setting the block to the x and y coordinates * BLOCK_SIZE
      hitbox.x = x * BLOCK_SIZE;
      hitbox.y = y * BLOCK_SIZE;
      b = set_block(hitbox, spritesheet_pos, Blank);

      switch (curr) {

        case '0':
          //Solid
          spritesheet_pos.x = 0;
          spritesheet_pos.y = 0;
          b = set_block(hitbox, spritesheet_pos, Solid);
          break;

        case '1':
          //Background
          spritesheet_pos.x = 16;
          spritesheet_pos.y = 0;
          b = set_block(hitbox, spritesheet_pos, Background);
          break;

        case '2':
          //Foreground
          spritesheet_pos.x = 32;
          spritesheet_pos.y = 0;
          b = set_block(hitbox, spritesheet_pos, Foreground);
          break;

        case 'p':
          //player
          set_character_real_position(p, x * BLOCK_SIZE, (y * BLOCK_SIZE) - IMG_HEIGHT);
          break;

        case 'e':
          //enemy
          l.enemies = character_list_build(set_character(10, set_floatpoint(x * BLOCK_SIZE, (y * BLOCK_SIZE) - IMG_HEIGHT), set_vector(0.0, 0.0), cSpritePos, Enemy), l.enemies);
          i++;
          break;

        default:
          break;

      }

      //affecting the block to the array
      matrix[x][y] = b;
      x++;

    }

  }

  //closing the txt file
  fclose(txtFile);

  //completing the array of the level with the one we just created
  int j;
  for (i = 0; i < NB_BLOCKS_WIDTH; i++) {
    for (j = 0; j < NB_BLOCKS_HEIGHT; j++) {

      set_level_block(&l, i, j, matrix[i][j]);

    }
  }

  set_level_music(&l, path_music);

  return l;
}

/* LIST */

//build a new level on the list
level_list_t level_list_build (level_t l, level_list_t ll) {
  level_list_t temp;
  temp = malloc(sizeof(*temp));
  temp->head = l;
  temp->next = ll;
  return temp;
}

//returns the head of the list
level_t level_list_head (level_list_t l) {
  return l->head;
}

//returns the rest of the list
level_list_t level_list_rest (level_list_t l) {
  return l->next;
}

//returns if the list is empty or not
bool level_list_is_empty (level_list_t l) {
  return l == NULL;
}

//returns an empty list
level_list_t level_list_empty () {
  return NULL;
}

//copy the list of level
level_list_t level_list_copy (level_list_t l) {
  if (level_list_is_empty(l)) {
    return level_list_empty();
  }

  return level_list_build(level_list_head(l), level_list_copy(level_list_rest(l)));
}

//free the entire list
void level_list_free (level_list_t l) {
  if (level_list_is_empty(l)) {
    return;
  }

  level_list_free(level_list_rest(l));

  character_list_free(l->head.enemies);
  SDL_DestroyTexture(l->head.blocks_spritesheet);
  SDL_DestroyTexture(l->head.background);
  Mix_FreeMusic(l->head.levelMusic);

  if (l == NULL) {
    printf("level_list_t already freed!\n");
    exit(1);
  } else {
    free(l);
    l = NULL;
  }

  return;
}

/* SET */

//create a new level
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

//change one block
void set_level_block (level_t *l, int x, int y, block_t b) {
  l->blocks[x][y] = b;

  return;
}

//change the sprite sheet
void set_level_blocks_spritesheet (level_t *l, SDL_Texture *blocks_spritesheet) {
  l->blocks_spritesheet = blocks_spritesheet;

  return;
}

//set a new background
void set_level_background (level_t *l, SDL_Texture *background) {
  l->background = background;

  return;
}

/* GET */

//get the block at a specific position
block_t get_level_block (level_t l, int x, int y) {

  return l.blocks[x][y];
}

//get the sprite sheet
SDL_Texture *get_level_blocks_spritesheet (level_t l) {

  return l.blocks_spritesheet;
}

//get the background
SDL_Texture *get_level_background (level_t l) {

  return l.background;
}
