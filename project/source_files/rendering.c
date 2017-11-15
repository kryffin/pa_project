#include "../header_files/rendering.h"

void render_cursor (game_t game) {

  SDL_Rect temp;
  temp.x = get_intpoint_x(game.mouse_pos) - (CURSOR_WIDTH/2);
  temp.y = get_intpoint_y(game.mouse_pos) - (CURSOR_HEIGHT/2);
  temp.w = CURSOR_WIDTH;
  temp.h = CURSOR_HEIGHT;

  SDL_RenderCopy(game.renderer, game.cursor, NULL, &temp);

  return;
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

void rendering (game_t *game) {

  SDL_RenderCopy(game->renderer, get_level_background(game->currLevel), NULL, NULL);

  //render the background elements
  render_background_level(*game);

  //render the enemy projectile
  render_projectiles(*game);

  //render the player_t
  render_player(game->player, game->renderer, game->mouse_pos);
  int i = 0;
  for (i = 0; i < 10; i++) {
    if (is_alive(game->enemies[i])) {
      render_player(game->enemies[i], game->renderer, game->mouse_pos);
    }
  }

  //render the attack and process it
  if (get_player_state(game->player) == Attacking)  {
    player_melee(game->player, game->renderer);
  }

  //render the foreground
  render_foreground_level(*game);

  //render the cursor
  render_cursor(*game);

  SDL_Rect tempRect = {game->player.xGrid * 16, game->player.yGrid * 16, 16, 16};

  SDL_RenderCopy(game->renderer, game->playerProjectiles[0].img, NULL, &tempRect);
  tempRect.x+=16;
  SDL_RenderCopy(game->renderer, game->playerProjectiles[0].img, NULL, &tempRect);
  tempRect.x-=16;
  tempRect.y+=16;
  SDL_RenderCopy(game->renderer, game->playerProjectiles[0].img, NULL, &tempRect);
  tempRect.x+=16;
  SDL_RenderCopy(game->renderer, game->playerProjectiles[0].img, NULL, &tempRect);
  tempRect.x-=16;
  tempRect.y+=16;
  SDL_RenderCopy(game->renderer, game->playerProjectiles[0].img, NULL, &tempRect);
  tempRect.x+=16;
  SDL_RenderCopy(game->renderer, game->playerProjectiles[0].img, NULL, &tempRect);
  tempRect.x-=16;
  tempRect.y+=16;
  SDL_RenderCopy(game->renderer, game->playerProjectiles[0].img, NULL, &tempRect);
  tempRect.x+=16;
  SDL_RenderCopy(game->renderer, game->playerProjectiles[0].img, NULL, &tempRect);

  SDL_RenderPresent(game->renderer);

  return;
}

void render_foreground_level (game_t game) {

  unsigned short int type;
  SDL_Rect tempSpritePos = {0, 0, 16, 16};
  SDL_Rect tempPos = {0, 0, 16, 16};
  int i, j;
  for (i = 0; i < NB_BLOCKS_WIDTH; i++) {
    for (j = 0; j < NB_BLOCKS_HEIGHT; j++) {

      type = get_block_type(get_level_block(game.currLevel, i, j));
      tempPos.x = i * 16;
      tempPos.y = j * 16;

      switch (type) {

        case Solid:
          tempSpritePos.x = 0;
          SDL_RenderCopy(game.renderer, get_level_blocks_spritesheet(game.currLevel), &tempSpritePos, &tempPos);
          break;

        case Foreground:
          tempSpritePos.x = 32;
          SDL_RenderCopy(game.renderer, get_level_blocks_spritesheet(game.currLevel), &tempSpritePos, &tempPos);
          break;

        default:
          break;

      }
    }
  }

  return;
}

void render_background_level (game_t game) {

  SDL_Rect tempSpritePos = {16, 0, 16, 16};
  SDL_Rect tempPos = {0, 0, 16, 16};
  int i, j;
  for (i = 0; i < NB_BLOCKS_WIDTH; i++) {
    for (j = 0; j < NB_BLOCKS_HEIGHT; j++) {

      tempPos.x = i * 16;
      tempPos.y = j * 16;

      if (get_block_type(get_level_block(game.currLevel, i, j)) == Background) {
        SDL_RenderCopy(game.renderer, get_level_blocks_spritesheet(game.currLevel), &tempSpritePos, &tempPos);
      }
    }
  }

  return;
}

void render_projectiles (game_t game) {

  int i;

  for (i = 0; i < 100; i += 1) {

    //if the projectile_t exists
    if (get_projectile_direction(game.playerProjectiles[i]).x != 0.0 || get_projectile_direction(game.playerProjectiles[i]).y != 0.0) {

      SDL_Rect tempSpritePos = get_projectile_sprite_pos(game.playerProjectiles[i]);
      SDL_Rect tempPos = get_projectile_hitbox(game.playerProjectiles[i]);

      SDL_RenderCopy(game.renderer, get_projectile_image(game.playerProjectiles[i]), &tempSpritePos, &tempPos);

    }

    //if the projectile_t exists
    if (get_projectile_direction(game.enemyProjectiles[i]).x != 0.0 || get_projectile_direction(game.enemyProjectiles[i]).y != 0.0) {

      SDL_Rect tempSpritePos = get_projectile_sprite_pos(game.enemyProjectiles[i]);
      SDL_Rect tempPos = get_projectile_hitbox(game.enemyProjectiles[i]);

      SDL_RenderCopy(game.renderer, get_projectile_image(game.enemyProjectiles[i]), &tempSpritePos, &tempPos);

    }
  }

  return;

}

void render_player (player_t p, SDL_Renderer *renderer, intpoint_t mouse_pos) {

  SDL_Rect *temp = NULL;
  temp = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  temp->w = 32;
  temp->h = 64;
  short int step = get_player_step(p);
  short int state = get_player_state(p);

  if (get_player_dir(p) == Right) {
    //player facing right

    switch (state) {

      //stand-by/walking
      case Walking:

        if (get_player_velocity(p).x == 0) {

          //stand by sprite
          temp->x = 0;
          temp->y = 0;
          set_player_sprite_pos(&p, *temp);

        } else {

          //sprite moving
          switch (step) {

            case 0:
              temp->x = 32;
              temp->y = 0;
              set_player_sprite_pos(&p, *temp);
              break;

            case 1:
              temp->x = 0;
              temp->y = 0;
              set_player_sprite_pos(&p, *temp);
              break;

            case 2:
              temp->x = 64;
              temp->y = 0;
              set_player_sprite_pos(&p, *temp);
              break;

            case 3:
              temp->x = 0;
              temp->y = 0;
              set_player_sprite_pos(&p, *temp);
              break;

            default:
              break;

          }

        }

        break;

      //jumping or double-jumping
      case Jumping:
      case nouse:

      temp->x = 96;
      temp->y = 0;
      set_player_sprite_pos(&p, *temp);

        break;

      //attacking
      case Attacking:

      temp->x = 64;
      temp->y = 128;
      set_player_sprite_pos(&p, *temp);

        break;

      //crouching
      case Crouching:

        temp->x = 128;
        temp->y = 0;
        temp->h = 32;
        set_player_sprite_pos(&p, *temp);

        break;

      default:
        break;
    }

  } else {
    //player facing left

    switch (state) {

      //stand-by/walking
      case Walking:

        if (get_player_velocity(p).x == 0) {

          //stand by sprite
          temp->x = 0;
          temp->y = 64;
          set_player_sprite_pos(&p, *temp);

        } else {

          //sprite moving
          switch (step) {

            case 0:
              temp->x = 32;
              temp->y = 64;
              set_player_sprite_pos(&p, *temp);
              break;

            case 1:
              temp->x = 0;
              temp->y = 64;
              set_player_sprite_pos(&p, *temp);
              break;

            case 2:
              temp->x = 64;
              temp->y = 64;
              set_player_sprite_pos(&p, *temp);
              break;

            case 3:
              temp->x = 0;
              temp->y = 64;
              set_player_sprite_pos(&p, *temp);
              break;

            default:
              break;

          }

        }

        break;

      //jumping or double-jumping
      case Jumping:
      case nouse:

      temp->x = 96;
      temp->y = 64;
      set_player_sprite_pos(&p, *temp);

        break;

      //attacking
      case Attacking:

      temp->x = 96;
      temp->y = 128;
      set_player_sprite_pos(&p, *temp);

        break;

      //crouching
      case Crouching:

        temp->x = 128;
        temp->y = 32;
        temp->h = 32;
        set_player_sprite_pos(&p, *temp);

        break;

      default:
        break;
    }

  }

  SDL_Rect tempSpritePos = get_player_sprite_pos(p);
  SDL_Rect tempPos = get_player_hitbox(p);

  SDL_RenderCopy(renderer, get_player_img(p), &tempSpritePos, &tempPos);

  free(temp);

  return;
}
