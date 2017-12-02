/*

menu.c : contain the menu loop and the displays

*/

#include "../header_files/menu.h"

//manages the menu
void menu (game_t *g) {
  int menuOption = render_menu(g);
  switch (menuOption) {

    case 1:
      g->currLevel = level_list_build(init_level(PATH_BLOCKS_SHEET, PATH_BACKGROUND_LEVEL_1, PATH_TXT_LEVEL_1, PATH_LEVEL1_MUSIC, &g->player, &g->enemies, g->renderer), level_list_build( init_level(PATH_BLOCKS_SHEET, PATH_BACKGROUND_LEVEL_2, PATH_TXT_LEVEL_2, PATH_LEVEL2_MUSIC, &g->player, &g->enemies, g->renderer), level_list_build( init_level(PATH_BLOCKS_SHEET, PATH_BACKGROUND_LEVEL_3, PATH_TXT_LEVEL_3, PATH_LEVEL3_MUSIC, &g->player, &g->enemies, g->renderer), level_list_empty())));
      Mix_PlayMusic(g->currLevel->head.levelMusic, -1);
      break;

    case 2:
      g->currLevel = level_list_build(init_level(PATH_BLOCKS_SHEET, PATH_BACKGROUND_ARENA, PATH_TXT_ARENA, PATH_ARENA_MUSIC, &g->player, &g->enemies, g->renderer), level_list_empty());
      Mix_PlayMusic(g->currLevel->head.levelMusic, -1);
      break;

    case 3:
      g->quit = true;
      break;

    default:
      break;
  }

  return;
}

//function returning the state of the mouse :
/* 0 : no motion
   1 : button down
   2 : button up
   10 : quit
*/
int menu_controls(game_t *game) {
  //controls
  while (SDL_PollEvent(game->event)) {
    switch(game->event->type) {
      case SDL_MOUSEMOTION:
        //movement of the mouse
        game->mouse_pos.x = game->event->motion.x;
        game->mouse_pos.y = game->event->motion.y;
        break;

      case SDL_MOUSEBUTTONDOWN:
        //clicking
        return 1;
        break;

      case SDL_MOUSEBUTTONUP:
        //releasing the click
        return 2;
        break;

      case SDL_KEYDOWN:
        if (game->event->key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
          //escape key
          return 10;
        }
        break;

      case SDL_QUIT:
        //closing the window
        return 10;
        break;

      default:
        break;
    }
  }

  return 0;
}

//returns true if the mouse is hovering the target
bool mouse_hover_menu (intpoint_t mouse_pos, int targetx, int targety, int width, int height) {
  if(mouse_pos.x >= targetx && mouse_pos.x <= targetx + width && mouse_pos.y >= targety && mouse_pos.y <= targety + height) {
    return true;
  }
  return false;
}

/*display of the menu which returns :
  1 : Story mode
  2 : Arena
  3 : Quit
*/
int main_menu_display (game_t *game) {

  int *control = NULL;
  control = (int*)malloc(sizeof(int));
  int option = 0;

  //message surfaces
  SDL_Surface *surPlay = NULL;
  SDL_Surface *surOptions = NULL;
  SDL_Surface *surQuit = NULL;
  SDL_Surface *temp;

  SDL_Texture *tempT = NULL;
  SDL_Texture *background;

  temp = IMG_Load(PATH_BACKGROUND);
  if (temp == NULL) {
    printf("Error loading the menu backgroung : %s\n", IMG_GetError());
    exit(1);
  }
  background = SDL_CreateTextureFromSurface(game->renderer, temp);
  SDL_FreeSurface(temp);

  //text strings
  char *strPlay = NULL;
  strPlay = (char*)malloc(12 * sizeof(char));
  sprintf(strPlay, "Story Mode");

  char *strOptions = NULL;
  strOptions = (char*)malloc(6 * sizeof(char));
  sprintf(strOptions, "Arena");

  char *strQuit = NULL;
  strQuit = (char*)malloc(5 * sizeof(char));
  sprintf(strQuit, "Quit");

  //text positions
  SDL_Rect *posPlay = NULL;
  posPlay = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  SDL_Rect *posOptions = NULL;
  posOptions = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  SDL_Rect *posQuit = NULL;
  posQuit = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  //event running the controls
  SDL_Event *event = NULL;
  event = (SDL_Event*)malloc(sizeof(SDL_Event));

  //render the messages
  surPlay = TTF_RenderText_Solid(game->font, strPlay, game->colorPalette[0]);
  surOptions = TTF_RenderText_Solid(game->font, strOptions, game->colorPalette[0]);
  surQuit = TTF_RenderText_Solid(game->font, strQuit, game->colorPalette[0]);

  //message positions
  posPlay->x = (SCREEN_WIDTH / 2) - (surPlay->clip_rect.w / 2);
  posPlay->y = (surPlay->clip_rect.h / 2) + (1 * (SCREEN_HEIGHT / 4));
  posOptions->x = (SCREEN_WIDTH / 2) - (surOptions->clip_rect.w / 2);
  posOptions->y = (surOptions->clip_rect.h / 2) + (2 * (SCREEN_HEIGHT / 4));
  posQuit->x = (SCREEN_WIDTH / 2) - (surQuit->clip_rect.w / 2);
  posQuit->y = (surQuit->clip_rect.h / 2) + (3 * (SCREEN_HEIGHT / 4));

  while (1) {

    //fill the screen with white
    SDL_RenderClear(game->renderer);

    //controls
    *control = menu_controls(game);

    if (mouse_hover_menu(game->mouse_pos, posPlay->x, posPlay->y, surPlay->clip_rect.w, surPlay->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(surPlay);
        surPlay = TTF_RenderText_Solid(game->font, strPlay, game->colorPalette[3]);

      } else if (*control == 1){

        SDL_FreeSurface(surPlay);
        surPlay = TTF_RenderText_Solid(game->font, strPlay, game->colorPalette[2]);

      } else if (*control == 2) {

        SDL_FreeSurface(surPlay);
        surPlay = TTF_RenderText_Solid(game->font, strPlay, game->colorPalette[3]);
        option = 1;

      }

    } else if (mouse_hover_menu(game->mouse_pos, posOptions->x, posOptions->y, surOptions->clip_rect.w, surOptions->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(surOptions);
        surOptions = TTF_RenderText_Solid(game->font, strOptions, game->colorPalette[3]);

      } else if (*control == 1){

        SDL_FreeSurface(surOptions);
        surOptions = TTF_RenderText_Solid(game->font, strOptions, game->colorPalette[2]);

      } else if (*control == 2) {

        SDL_FreeSurface(surOptions);
        surOptions = TTF_RenderText_Solid(game->font, strOptions, game->colorPalette[3]);
        option = 2;

      }

    } else if (mouse_hover_menu(game->mouse_pos, posQuit->x, posQuit->y, surQuit->clip_rect.w, surQuit->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(surQuit);
        surQuit = TTF_RenderText_Solid(game->font, strQuit, game->colorPalette[3]);

      } else if (*control == 1) {

        SDL_FreeSurface(surQuit);
        surQuit = TTF_RenderText_Solid(game->font, strQuit, game->colorPalette[2]);

      } else if (*control == 2) {

        SDL_FreeSurface(surPlay);
        surPlay = TTF_RenderText_Solid(game->font, strPlay, game->colorPalette[3]);
        option = 3;

      }

    } else {
      //render the messages
      SDL_FreeSurface(surPlay);
      surPlay = TTF_RenderText_Solid(game->font, strPlay, game->colorPalette[0]);
      SDL_FreeSurface(surOptions);
      surOptions = TTF_RenderText_Solid(game->font, strOptions, game->colorPalette[0]);
      SDL_FreeSurface(surQuit);
      surQuit = TTF_RenderText_Solid(game->font, strQuit, game->colorPalette[0]);

    }

    SDL_RenderCopy(game->renderer, background, NULL, NULL);

    //blitting the options on the window
    tempT = SDL_CreateTextureFromSurface(game->renderer, surPlay);
    SDL_QueryTexture(tempT, NULL, NULL, &(posPlay->w), &(posPlay->h));
    SDL_RenderCopy(game->renderer, tempT, NULL, posPlay);

    tempT = SDL_CreateTextureFromSurface(game->renderer, surOptions);
    SDL_QueryTexture(tempT, NULL, NULL, &(posOptions->w), &(posOptions->h));
    SDL_RenderCopy(game->renderer, tempT, NULL, posOptions);

    tempT = SDL_CreateTextureFromSurface(game->renderer, surQuit);
    SDL_QueryTexture(tempT, NULL, NULL, &(posQuit->w), &(posQuit->h));
    SDL_RenderCopy(game->renderer, tempT, NULL, posQuit);

    render_cursor(*game);

    SDL_RenderPresent(game->renderer);

    SDL_Delay(1000 / SCREEN_FPS);

    //if we escape
    if (*control == 10) {
      option = 3;
    }

    if (option != 0) {
      free(control);
      SDL_FreeSurface(surPlay);
      SDL_FreeSurface(surOptions);
      SDL_FreeSurface(surQuit);
      SDL_DestroyTexture(background);
      SDL_DestroyTexture(tempT);
      free(strPlay);
      free(strOptions);
      free(strQuit);
      free(posPlay);
      free(posOptions);
      free(posQuit);
      free(event);
      return option;
    }
  }
}

//loop managing the menus
int render_menu (game_t *game) {

  int mainMenuOption = 0;

  Mix_PlayMusic(game->menuMusic, -1);

  //while we are in the main or option menu
  while (mainMenuOption == 0) {

    //getting the option selected from the main menu
    mainMenuOption = main_menu_display (game);

  }

  Mix_HaltMusic();

  return mainMenuOption;
}
