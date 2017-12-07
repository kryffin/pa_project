/*

rendering.c : contain the functions to display everything

*/

#include "../header_files/rendering.h"

//render the melee attacks
void render_melee (character_t p, SDL_Renderer *renderer, SDL_Texture *img) {

  SDL_Rect *target = NULL;
  target = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  target->x = get_character_hitbox(p).x;
  target->y = get_character_hitbox(p).y;
  target->w = get_character_hitbox(p).w;
  target->h = get_character_hitbox(p).h;

  SDL_Rect *effect = NULL;
  effect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  effect->y = 128;
  effect->w = 32;
  effect->h = 64;

  if (get_character_dir(p) == Left) {
    //facing left
    target->x -= IMG_WIDTH;
    effect->x = 32;

  } else {
    //facing right
    target->x += IMG_WIDTH;
    effect->x = 0;

  }

  SDL_RenderCopy(renderer, img, effect, target);

  free(target);
  free(effect);

  return;
}

//render the cursor
void render_cursor (game_t game) {

  SDL_Rect temp;
  temp.x = get_intpoint_x(game.mouse_pos) - (CURSOR_WIDTH / 2);
  temp.y = get_intpoint_y(game.mouse_pos) - (CURSOR_HEIGHT / 2);
  temp.w = CURSOR_WIDTH;
  temp.h = CURSOR_HEIGHT;

  SDL_RenderCopy(game.renderer, game.cursor, NULL, &temp);

  return;
}

//render the death screen
void game_over (game_t g) {
  SDL_Surface *temp = NULL;
  SDL_Texture *panel, *background, *img;
  SDL_Rect tempSpritePos = {128, 128, IMG_WIDTH, IMG_HEIGHT}, spritePos = get_character_hitbox(g.player);

  temp = IMG_Load(PATH_YOU_DIED);
  panel = SDL_CreateTextureFromSurface(g.renderer, temp);
  SDL_FreeSurface(temp);

  background = g.currLevel->head.background;
  img = g.spriteSheet;

  int currTime = SDL_GetTicks();

  /* fade in */

  int opacity = 0;
  for (opacity = 0; opacity <= 240; opacity += 20) {
    SDL_RenderCopy(g.renderer, background, NULL, NULL);
    SDL_RenderCopy(g.renderer, img, &tempSpritePos, &spritePos);
    SDL_SetTextureAlphaMod(panel, (Uint8)opacity);
    SDL_RenderCopy(g.renderer, panel, NULL, NULL);
    SDL_RenderPresent(g.renderer);
    currTime = SDL_GetTicks();
    while (SDL_GetTicks() < currTime + 50);
  }

  /* stand by */

  currTime = SDL_GetTicks();
  while (SDL_GetTicks() < currTime + 1500);

  /* fade out */

  for (opacity = 240; opacity >= 0; opacity -= 20) {
    SDL_RenderCopy(g.renderer, background, NULL, NULL);
    SDL_RenderCopy(g.renderer, img, &tempSpritePos, &spritePos);
    SDL_SetTextureAlphaMod(panel, (Uint8)opacity);
    SDL_RenderCopy(g.renderer, panel, NULL, NULL);
    SDL_RenderPresent(g.renderer);
    currTime = SDL_GetTicks();
    while (SDL_GetTicks() < currTime + 50);
  }

  SDL_DestroyTexture(panel);

  return;
}

//render the foreground level
void render_foreground_level (game_t game) {

  unsigned short int type;
  SDL_Rect tempSpritePos = {0, 0, 16, 16};
  SDL_Rect tempPos = {0, 0, BLOCK_SIZE, BLOCK_SIZE};
  int i, j;
  for (i = 0; i < NB_BLOCKS_WIDTH; i++) {
    for (j = 0; j < NB_BLOCKS_HEIGHT; j++) {

      type = get_block_type(get_level_block(game.currLevel->head, i, j));
      tempPos.x = i * BLOCK_SIZE;
      tempPos.y = j * BLOCK_SIZE;

      switch (type) {

        case Solid:
          tempSpritePos.x = 0;
          SDL_RenderCopy(game.renderer, get_level_blocks_spritesheet(game.currLevel->head), &tempSpritePos, &tempPos);
          break;

        case Foreground:
          tempSpritePos.x = 32;
          SDL_RenderCopy(game.renderer, get_level_blocks_spritesheet(game.currLevel->head), &tempSpritePos, &tempPos);
          break;

        default:
          break;

      }
    }
  }

  return;
}

//render the background level as well as the background image
void render_background_level (game_t game) {

  SDL_Rect tempSpritePos = {16, 0, 16, 16};
  SDL_Rect tempPos = {0, 0, BLOCK_SIZE, BLOCK_SIZE};
  int i, j;
  for (i = 0; i < NB_BLOCKS_WIDTH; i++) {
    for (j = 0; j < NB_BLOCKS_HEIGHT; j++) {

      tempPos.x = i * BLOCK_SIZE;
      tempPos.y = j * BLOCK_SIZE;

      if (get_block_type(get_level_block(game.currLevel->head, i, j)) == Background) {
        SDL_RenderCopy(game.renderer, get_level_blocks_spritesheet(game.currLevel->head), &tempSpritePos, &tempPos);
      }
    }
  }

  return;
}

//render the projectiles of a projectile list
void render_projectiles (projectile_list_t p, SDL_Renderer *renderer, SDL_Texture *img) {

  if (projectile_list_is_empty(p)) {
    return;
  }

  SDL_Rect tempPos = p->head.hitbox;
  tempPos.x -= BULLET_WIDTH / 2;
  tempPos.y -= BULLET_HEIGHT / 2;
  SDL_Rect tempSpritePos = get_projectile_sprite_pos(projectile_list_head(p));

  SDL_RenderCopy(renderer, img, &tempSpritePos, &tempPos);

  render_projectiles(projectile_list_rest(p), renderer, img);

  return;

}

//render a character
void render_character (character_t p, SDL_Renderer *renderer, SDL_Texture *img) {

  SDL_Rect temp;
  temp.w = 32;
  temp.h = 64;
  short int step = get_character_step(p);
  short int state = get_character_state(p);

  SDL_Rect tempSpritePos;
  SDL_Rect tempPos = get_character_hitbox(p);

  if (p.hp < 1) {
    tempSpritePos.x = 128;
    tempSpritePos.y = 128;
    tempSpritePos.w = IMG_WIDTH;
    tempSpritePos.h = IMG_HEIGHT;
    SDL_SetTextureAlphaMod(img, (Uint8)p.tts);
    SDL_RenderCopy(renderer, img, &tempSpritePos, &tempPos);
    SDL_SetTextureAlphaMod(img, 255);

    tempSpritePos.x = 128;
    tempSpritePos.y = 116;
    tempSpritePos.w = 30;
    tempSpritePos.h = 2;

    tempPos.x += 1;
    tempPos.y -= 10;
    tempPos.w = 30;
    tempPos.h = 2;

    SDL_RenderCopy(renderer, img, &tempSpritePos, &tempPos);

    return;
  }

  if (get_character_dir(p) == Right) {
    //character facing right

    switch (state) {

      //stand-by/walking
      case Walking:

        if (get_character_velocity(p).x == 0) {

          //stand by sprite
          temp.x = 0;
          temp.y = 0;
          set_character_sprite_pos(&p, temp);

        } else {

          //sprite moving
          switch (step) {

            case 0:
              temp.x = 32;
              temp.y = 0;
              set_character_sprite_pos(&p, temp);
              break;

            case 1:
              temp.x = 0;
              temp.y = 0;
              set_character_sprite_pos(&p, temp);
              break;

            case 2:
              temp.x = 64;
              temp.y = 0;
              set_character_sprite_pos(&p, temp);
              break;

            case 3:
              temp.x = 0;
              temp.y = 0;
              set_character_sprite_pos(&p, temp);
              break;

            default:
              break;

          }

        }

        break;

      //jumping or double-jumping
      case Jumping:
      case nouse:

      temp.x = 96;
      temp.y = 0;
      set_character_sprite_pos(&p, temp);

        break;

      //attacking
      case Attacking:

      temp.x = 64;
      temp.y = 128;
      set_character_sprite_pos(&p, temp);

        break;

      //crouching
      case Crouching:

        temp.x = 128;
        temp.y = 0;
        temp.h = 32;
        set_character_sprite_pos(&p, temp);

        break;

      default:
        break;
    }

  } else {
    //character facing left

    switch (state) {

      //stand-by/walking
      case Walking:

        if (get_character_velocity(p).x == 0) {

          //stand by sprite
          temp.x = 0;
          temp.y = 64;
          set_character_sprite_pos(&p, temp);

        } else {

          //sprite moving
          switch (step) {

            case 0:
              temp.x = 32;
              temp.y = 64;
              set_character_sprite_pos(&p, temp);
              break;

            case 1:
              temp.x = 0;
              temp.y = 64;
              set_character_sprite_pos(&p, temp);
              break;

            case 2:
              temp.x = 64;
              temp.y = 64;
              set_character_sprite_pos(&p, temp);
              break;

            case 3:
              temp.x = 0;
              temp.y = 64;
              set_character_sprite_pos(&p, temp);
              break;

            default:
              break;

          }

        }

        break;

      //jumping or double-jumping
      case Jumping:
      case nouse:

      temp.x = 96;
      temp.y = 64;
      set_character_sprite_pos(&p, temp);

        break;

      //attacking
      case Attacking:

      temp.x = 96;
      temp.y = 128;
      set_character_sprite_pos(&p, temp);

        break;

      //crouching
      case Crouching:

        temp.x = 128;
        temp.y = 32;
        temp.h = 32;
        set_character_sprite_pos(&p, temp);

        break;

      default:
        break;
    }

  }

  tempSpritePos = get_character_sprite_pos(p);

  if (!(get_i_frames_invincible(get_character_i_frames(p)) && !get_i_frames_display(get_character_i_frames(p)))) {

    SDL_RenderCopy(renderer, img, &tempSpritePos, &tempPos);

  }

  tempSpritePos.x = 128;
  tempSpritePos.y = 116 - (2 * p.hp);
  tempSpritePos.w = 30;
  tempSpritePos.h = 2;

  tempPos.x += 1;
  tempPos.y -= 10;
  tempPos.w = 30;
  tempPos.h = 2;

  SDL_RenderCopy(renderer, img, &tempSpritePos, &tempPos);

  return;
}

//calls every functions to render
void rendering (game_t *game) {

  SDL_RenderCopy(game->renderer, get_level_background(game->currLevel->head), NULL, NULL);

  //render the background elements
  render_background_level(*game);

  //render the enemy projectile
  character_list_t c;
  c = game->enemies;
  while (!character_list_is_empty(c)) {
    render_character(character_list_head(c), game->renderer, game->spriteSheet);
    render_projectiles(character_list_head(c).projectiles, game->renderer, game->spriteSheet);
    c = c->next;
  }
  character_list_free(c);

  //render the character_t
  if (is_alive(game->player)) {
    render_character(game->player, game->renderer, game->spriteSheet);
  }
  render_projectiles(game->player.projectiles, game->renderer, game->spriteSheet);

  //render the foreground
  render_foreground_level(*game);

  //render the attack and process it
  if (get_character_state(game->player) == Attacking)  {
    render_melee(game->player, game->renderer, game->spriteSheet);
  }

  //render the cursor
  render_cursor(*game);

  //DEBUG
  /*SDL_Rect tempRect = {game->player.gridPos.x * 16, game->player.gridPos.y * 16, 16, 16};

  SDL_RenderCopy(game->renderer, game->spriteSheet, NULL, &tempRect);
  tempRect.y+=16;
  SDL_RenderCopy(game->renderer, game->spriteSheet, NULL, &tempRect);
  tempRect.y+=16;
  SDL_RenderCopy(game->renderer, game->spriteSheet, NULL, &tempRect);
  tempRect.y+=16;
  SDL_RenderCopy(game->renderer, game->spriteSheet, NULL, &tempRect);*/

  SDL_RenderPresent(game->renderer);

  return;
}
