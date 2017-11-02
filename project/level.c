#include "header.h"

intpoint_t closest_out (player_t player, int w, int h) {

  intpoint_t posBlock, distx, disty, distmx, distmy;
  int i;

  distx = set_intpoint((int)get_player_real_position(player).x, (int)get_player_real_position(player).y);
  disty = set_intpoint((int)get_player_real_position(player).x, (int)get_player_real_position(player).y);
  distmx = set_intpoint((int)get_player_real_position(player).x, (int)get_player_real_position(player).y);
  distmy = set_intpoint((int)get_player_real_position(player).x, (int)get_player_real_position(player).y);


  posBlock = set_intpoint(w, h);

  while (true) {

    for (i = 0; i < 4; i++) {
      switch (i) {
        case 0:
          set_intpoint_x(&distx, get_intpoint_x(distx) + 1);
          if (!collision_intpoint(posBlock, distx)) {
            printf("choix x+\n");
            return distx;
          }
          break;

        case 1:
          set_intpoint_y(&disty, get_intpoint_y(disty) + 1);
          if (!collision_intpoint(posBlock, disty)) {
            printf("choix y+\n");
            return disty;
          }
          break;

        case 2:
          set_intpoint_x(&distmx, get_intpoint_x(distmx) - 1);
          if (!collision_intpoint(posBlock, distmx)) {
            printf("choix x-\n");
            return distmx;
          }
          break;

        case 3:
          set_intpoint_y(&distmy, get_intpoint_y(distmy) - 1);
          if (!collision_intpoint(posBlock, distmy)) {
            printf("choix y-\n");
            return distmy;
          }
          break;

        default:
          break;
      }
    }

  }

}

bool collision_intpoint (intpoint_t a, intpoint_t b) {
  if (((get_intpoint_x(a) >= get_intpoint_x(b) && get_intpoint_x(a) <= get_intpoint_x(b) + IMG_WIDTH) || (get_intpoint_x(a) + 16 >= get_intpoint_x(b) && get_intpoint_x(a) + 16 <= get_intpoint_x(b) + IMG_WIDTH))) {

    if (((get_intpoint_y(a) >= get_intpoint_y(b) && get_intpoint_y(a) <= get_intpoint_y(b) + IMG_HEIGHT) || (get_intpoint_y(a) + 16 >= get_intpoint_y(b) && get_intpoint_y(a) + 16 <= get_intpoint_y(b) + IMG_HEIGHT))) {

      return true;

    }

  }

  return false;
}

bool colision (player_t player, block blocks[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT], int *width, int *height) {
  int w,h;
  intpoint_t posBlock;

  set_player_real_position(&player, get_player_real_position(player).x + get_player_velocity(player).x, get_player_real_position(player).y + get_player_velocity(player).y);

  for (w = 0; w < NB_BLOCKS_WIDTH; w++) {
    for (h = 0; h < NB_BLOCKS_HEIGHT; h++) {

      if (get_block_type(blocks[w][h]) == 0) {
        posBlock = set_intpoint(w*16, h*16);

        if ((get_intpoint_x(posBlock) >= get_player_real_position(player).x && get_intpoint_x(posBlock) <= get_player_real_position(player).x + IMG_WIDTH) || (get_intpoint_x(posBlock) + 16 >= get_player_real_position(player).x && get_intpoint_x(posBlock) + 16 <= get_player_real_position(player).x + IMG_WIDTH)) {

          if ((get_intpoint_y(posBlock) >= get_player_real_position(player).y && get_intpoint_y(posBlock) <= get_player_real_position(player).y + IMG_HEIGHT) || (get_intpoint_y(posBlock) + 16 >= get_player_real_position(player).y && get_intpoint_y(posBlock) + 16 <= get_player_real_position(player).y + IMG_HEIGHT)) {

            *width = w * 16;
            *height = h * 16;
            return true;

          }

        }

      }

    }
  }

  return false;
}

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

void rendering (player_t *player, player_t enemies[10], projectile bullets[100], projectile enemyProjectiles[100], SDL_Texture *cursor, level currLevel, intpoint_t *mouse_pos, SDL_Renderer *renderer) {

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
  SDL_Rect tempSpritePos = {0, 0, 16, 16};
  SDL_Rect tempPos = {0, 0, 16, 16};
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

level init_level (SDL_Texture *blocks_spritesheet, SDL_Texture *background, player_t *p, player_t enemies[10]) {

  level l;
  int i = 0;

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
