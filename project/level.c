#include "header.h"

void rendering (player *player, projectile bullets[100], SDL_Texture *cursor, level currLevel, intpoint *mouse_pos, SDL_Renderer *renderer) {

  SDL_RenderCopy(renderer, get_level_background(currLevel), NULL, NULL);

  //render the background elements
  render_background_level(currLevel, renderer);

  //render the projectile
  render_projectile(bullets, renderer);

  //render the player
  render_player(*player, renderer, *mouse_pos);

  //render the attack and process it
  if (get_player_state(*player) == 3)  {
    player_melee(*player, renderer);
  }

  //render the foreground
  render_foreground_level(currLevel, renderer);

  //render the cursor
  render_cursor(cursor, renderer, *mouse_pos);

  SDL_RenderPresent(renderer);

  return;
}

void render_foreground_level (level l, SDL_Renderer *renderer) {

  unsigned short int type;
  SDL_Rect tempSpritePos = {0, 0, BLOCK_WIDTH, BLOCK_HEIGHT};
  SDL_Rect tempPos = {0, 0, BLOCK_WIDTH, BLOCK_HEIGHT};
  int i, j;
  for (i = 0; i < NB_BLOCKS_WIDTH; i++) {
    for (j = 0; j < NB_BLOCKS_HEIGHT; j++) {

      type = get_block_type(get_level_block(l, i, j));
      tempPos.x = i * 16;
      tempPos.y = j * 16;

      switch (type) {

        case 0:
          tempSpritePos.x = 0;
          SDL_RenderCopy(renderer, get_level_blocks_spritesheet(l), &tempSpritePos, &tempPos);
          break;

        case 2:
          tempSpritePos.x = 32;
          SDL_RenderCopy(renderer, get_level_blocks_spritesheet(l), &tempSpritePos, &tempPos);
          break;

        default:
          break;

      }
    }
  }

  return;
}

void render_background_level (level l, SDL_Renderer *renderer) {

  unsigned short int type;
  SDL_Rect tempSpritePos = {0, 0, 16, 16};
  SDL_Rect tempPos = {0, 0, 16, 16};
  int i, j;
  for (i = 0; i < NB_BLOCKS_WIDTH; i++) {
    for (j = 0; j < NB_BLOCKS_HEIGHT; j++) {

      type = get_block_type(get_level_block(l, i, j));
      tempPos.x = i * 16;
      tempPos.y = j * 16;

      switch (type) {

        case 1:
          tempSpritePos.x = 16;
          SDL_RenderCopy(renderer, get_level_blocks_spritesheet(l), &tempSpritePos, &tempPos);
          break;

        default:
          break;

      }
    }
  }

  return;
}

level init_level (SDL_Texture *blocks_spritesheet, SDL_Texture *background, player *p) {

  level l;

  FILE *txtFile = fopen(PATH_TXT_FILE, "r");
  if (txtFile == NULL) {
    printf("Error opening the txt file\n");
    exit(0);
  }

  block matrix[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT];
  char curr;
  block b;
  SDL_Rect hitbox = {0, 0, 16, 16};
  SDL_Rect spritesheet_pos = {0, 0, 16, 16};

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
          b = set_block(hitbox, spritesheet_pos, 0);
          break;

        case '1':
          spritesheet_pos.x = 16;
          spritesheet_pos.y = 0;
          b = set_block(hitbox, spritesheet_pos, 1);
          break;

        case '2':
          spritesheet_pos.x = 32;
          spritesheet_pos.y = 0;
          b = set_block(hitbox, spritesheet_pos, 2);
          break;

        case 'p':
        b = set_block(hitbox, spritesheet_pos, 5);
          set_player_real_position(p, x * 16, (y * 16) - 48);
          break;

        default:
        b = set_block(hitbox, spritesheet_pos, 5);
          break;

      }
      matrix[x][y] = b;
      x++;

    }

  }
  fclose(txtFile);

  l = set_level(matrix, blocks_spritesheet, background);

  return l;
}

/* SET */

level set_level (block blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT], SDL_Texture *blocks_spritesheet, SDL_Texture *background) {
  level l;

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

void set_level_block (level *l, int x, int y, block b) {
  l->blocks[x][y] = b;

  return;
}

void set_level_blocks_spritesheet (level *l, SDL_Texture *blocks_spritesheet) {
  l->blocks_spritesheet = blocks_spritesheet;

  return;
}

void set_level_background (level *l, SDL_Texture *background) {
  l->background = background;

  return;
}

/* GET */

block get_level_block (level l, int x, int y) {

  return l.blocks[x][y];
}

SDL_Texture *get_level_blocks_spritesheet (level l) {

  return l.blocks_spritesheet;
}

SDL_Texture *get_level_background (level l) {

  return l.background;
}
