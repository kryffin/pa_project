#include "../header_files/level.h"

void game_over (SDL_Renderer *renderer) {
  SDL_Surface *temp;
  SDL_Texture *panel;

  temp = IMG_Load(PATH_YOU_DIED);
  panel = SDL_CreateTextureFromSurface(renderer, temp);
  SDL_FreeSurface(temp);

  SDL_RenderCopy(renderer, panel, NULL, NULL);

  SDL_RenderPresent(renderer);

  SDL_Delay(1000);
  return;
}

void rendering (player_t *player, player_t enemies[10], projectile_t bullets[100], projectile_t enemyProjectiles[100], SDL_Texture *cursor, level_t currLevel, intpoint_t *mouse_pos, SDL_Renderer *renderer) {

  SDL_RenderCopy(renderer, get_level_background(currLevel), NULL, NULL);

  //render the background elements
  render_background_level(currLevel, renderer);

  //render the projectile
  render_projectile(bullets, renderer);

  //render the enemy projectile
  render_projectile(enemyProjectiles, renderer);

  //render the player_t
  render_player(*player, renderer, *mouse_pos);
  int i = 0;
  for (i = 0; i < 10; i++) {
    if (is_alive(enemies[i])) {
      render_player(enemies[i], renderer, *mouse_pos);
    }
  }

  //render the attack and process it
  if (get_player_state(*player) == Attacking)  {
    player_melee(*player, renderer);
  }

  //render the foreground
  render_foreground_level(currLevel, renderer);

  //render the cursor
  render_cursor(cursor, renderer, *mouse_pos);

  SDL_RenderPresent(renderer);

  return;
}

void render_foreground_level (level_t l, SDL_Renderer *renderer) {

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

        case Solid:
          tempSpritePos.x = 0;
          SDL_RenderCopy(renderer, get_level_blocks_spritesheet(l), &tempSpritePos, &tempPos);
          break;

        case Foreground:
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

void render_background_level (level_t l, SDL_Renderer *renderer) {

  SDL_Rect tempSpritePos = {16, 0, 16, 16};
  SDL_Rect tempPos = {0, 0, 16, 16};
  int i, j;
  for (i = 0; i < NB_BLOCKS_WIDTH; i++) {
    for (j = 0; j < NB_BLOCKS_HEIGHT; j++) {

      tempPos.x = i * 16;
      tempPos.y = j * 16;

      if (get_block_type(get_level_block(l, i, j)) == Background) {
        SDL_RenderCopy(renderer, get_level_blocks_spritesheet(l), &tempSpritePos, &tempPos);
      }
    }
  }

  return;
}

level_t init_level (SDL_Texture *blocks_spritesheet, SDL_Texture *background, player_t *p, player_t enemies[10]) {

  level_t l;
  int i = 0;

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
          set_player_real_position(p, x * 16, (y * 16) - 48);
          break;

        case 'e':
          set_player_real_position(&(enemies)[i], x * 16, (y * 16) - 48);
          set_player_hp(&(enemies)[i], 10);
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

  l = set_level(matrix, blocks_spritesheet, background);

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
