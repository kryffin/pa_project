/*

menu.c : contain the menu loop and the displays

*/

#include "../header_files/menu.h"

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
  1 : Continue
  2 : Options
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
  background = SDL_CreateTextureFromSurface(game->renderer, temp);
  SDL_FreeSurface(temp);

  //text strings
  char *strPlay = NULL;
  strPlay = (char*)malloc(5 * sizeof(char));
  sprintf(strPlay, "Play");

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

//display of the option menu
int option_menu_display (game_t *game) {

  int *control = NULL;
  control = (int*)malloc(sizeof(int));
  int option = 0;

  //message surfaces
  SDL_Surface *surFull = NULL;
  SDL_Surface *sur43 = NULL;
  SDL_Surface *sur1610 = NULL;
  SDL_Surface *sur169 = NULL;
  SDL_Surface *surAd = NULL;
  SDL_Surface *surBack = NULL;
  SDL_Surface *temp;

  SDL_Texture *tempT = NULL;
  SDL_Texture *background;

  temp = IMG_Load(PATH_BACKGROUND);
  background = SDL_CreateTextureFromSurface(game->renderer, temp);
  SDL_FreeSurface(temp);

  //text strings
  char *strFull = NULL;
  strFull = (char*)malloc(9 * sizeof(char));
  sprintf(strFull, "Full Screen");

  char *str43 = NULL;
  str43 = (char*)malloc(8 * sizeof(char));
  sprintf(str43, "640 x 480 (4:3)");

  char *str1610 = NULL;
  str1610 = (char*)malloc(5 * sizeof(char));
  sprintf(str1610, "1440 x 900 (16:10)");

  char *str169 = NULL;
  str169 = (char*)malloc(9 * sizeof(char));
  sprintf(str169, "1920 x 1080 (16:9)");

  char *strAd = NULL;
  strAd = (char*)malloc(8 * sizeof(char));
  sprintf(strAd, "Adjust");

  char *strBack = NULL;
  strBack = (char*)malloc(5 * sizeof(char));
  sprintf(strBack, "Back");

  //text positions
  SDL_Rect *posFull = NULL;
  posFull = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  SDL_Rect *pos43 = NULL;
  pos43 = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  SDL_Rect *pos1610 = NULL;
  pos1610 = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  SDL_Rect *pos169 = NULL;
  pos169 = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  SDL_Rect *posAd = NULL;
  posAd = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  SDL_Rect *posBack = NULL;
  posBack = (SDL_Rect*)malloc(sizeof(SDL_Rect));

  //event running the controls
  SDL_Event *event = NULL;
  event = (SDL_Event*)malloc(sizeof(SDL_Event));

  //render the messages
  surFull = TTF_RenderText_Solid(game->font, strFull, game->colorPalette[0]);
  sur43 = TTF_RenderText_Solid(game->font, str43, game->colorPalette[0]);
  sur1610 = TTF_RenderText_Solid(game->font, str1610, game->colorPalette[0]);
  sur169 = TTF_RenderText_Solid(game->font, str169, game->colorPalette[0]);
  surAd = TTF_RenderText_Solid(game->font, strAd, game->colorPalette[0]);
  surBack = TTF_RenderText_Solid(game->font, strBack, game->colorPalette[0]);

  int *span = NULL;
  span = (int*)malloc(sizeof(int));
  *span = (SCREEN_HEIGHT / 6);

  //message positions
  posFull->x = (SCREEN_WIDTH / 2) - (surFull->clip_rect.w / 2);
  posFull->y = 0;
  pos43->x = (SCREEN_WIDTH / 2) - (sur43->clip_rect.w / 2);
  pos43->y = (*span * 1);
  pos1610->x = (SCREEN_WIDTH / 2) - (sur1610->clip_rect.w / 2);
  pos1610->y = (*span * 2);
  pos169->x = (SCREEN_WIDTH / 2) - (sur169->clip_rect.w / 2);
  pos169->y = (*span * 3);
  posAd->x = (SCREEN_WIDTH / 2) - (surAd->clip_rect.w / 2);
  posAd->y = (*span * 4);
  posBack->x = (SCREEN_WIDTH / 2) - (surBack->clip_rect.w / 2);
  posBack->y = (*span * 5);

  free(span);

  while (1) {

    //fill the screen with white
    SDL_RenderClear(game->renderer);

    //controls
    *control = menu_controls(game);

    if (mouse_hover_menu(game->mouse_pos, posFull->x, posFull->y, surFull->clip_rect.w, surFull->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(surFull);
        surFull = TTF_RenderText_Solid(game->font, strFull, game->colorPalette[3]);

      } else if (*control == 1){

        SDL_FreeSurface(surFull);
        surFull = TTF_RenderText_Solid(game->font, strFull, game->colorPalette[2]);

      } else if (*control == 2) {

        SDL_FreeSurface(surFull);
        surFull = TTF_RenderText_Solid(game->font, strFull, game->colorPalette[3]);
        option = 1;

      }

    } else if (mouse_hover_menu(game->mouse_pos, pos43->x, pos43->y, sur43->clip_rect.w, sur43->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(sur43);
        sur43 = TTF_RenderText_Solid(game->font, str43, game->colorPalette[3]);

      } else if (*control == 1){

        SDL_FreeSurface(sur43);
        sur43 = TTF_RenderText_Solid(game->font, str43, game->colorPalette[2]);

      } else if (*control == 2) {

        SDL_FreeSurface(sur43);
        sur43 = TTF_RenderText_Solid(game->font, str43, game->colorPalette[3]);
        option = 2;

      }

    } else if (mouse_hover_menu(game->mouse_pos, pos1610->x, pos1610->y, sur1610->clip_rect.w, sur1610->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(sur1610);
        sur1610 = TTF_RenderText_Solid(game->font, str1610, game->colorPalette[3]);

      } else if (*control == 1) {

        SDL_FreeSurface(sur1610);
        sur1610 = TTF_RenderText_Solid(game->font, str1610, game->colorPalette[2]);

      } else if (*control == 2) {

        SDL_FreeSurface(sur1610);
        sur1610 = TTF_RenderText_Solid(game->font, str1610, game->colorPalette[3]);
        option = 3;

      }

    } else if (mouse_hover_menu(game->mouse_pos, pos169->x, pos169->y, sur169->clip_rect.w, sur169->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(sur169);
        sur169 = TTF_RenderText_Solid(game->font, str169, game->colorPalette[3]);

      } else if (*control == 1) {

        SDL_FreeSurface(sur169);
        sur169 = TTF_RenderText_Solid(game->font, str169, game->colorPalette[2]);

      } else if (*control == 2) {

        SDL_FreeSurface(sur169);
        sur169 = TTF_RenderText_Solid(game->font, str169, game->colorPalette[3]);
        option = 4;

      }

    } else if (mouse_hover_menu(game->mouse_pos, posAd->x, posAd->y, surAd->clip_rect.w, surAd->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(surAd);
        surAd = TTF_RenderText_Solid(game->font, strAd, game->colorPalette[3]);

      } else if (*control == 1) {

        SDL_FreeSurface(surAd);
        surAd = TTF_RenderText_Solid(game->font, strAd, game->colorPalette[2]);

      } else if (*control == 2) {

        SDL_FreeSurface(surAd);
        surAd = TTF_RenderText_Solid(game->font, strAd, game->colorPalette[3]);
        option = 5;

      }

    } else if (mouse_hover_menu(game->mouse_pos, posBack->x, posBack->y, surBack->clip_rect.w, surBack->clip_rect.h)) {

      if (*control == 0) {

        SDL_FreeSurface(surBack);
        surBack = TTF_RenderText_Solid(game->font, strBack, game->colorPalette[3]);

      } else if (*control == 1) {

        SDL_FreeSurface(surBack);
        surBack = TTF_RenderText_Solid(game->font, strBack, game->colorPalette[2]);

      } else if (*control == 2) {

        SDL_FreeSurface(surBack);
        surBack = TTF_RenderText_Solid(game->font, strBack, game->colorPalette[3]);
        option = 6;

      }

    } else {

      //reset the messages
      SDL_FreeSurface(surFull);
      surFull = TTF_RenderText_Solid(game->font, strFull, game->colorPalette[0]);
      SDL_FreeSurface(sur43);
      sur43 = TTF_RenderText_Solid(game->font, str43, game->colorPalette[0]);
      SDL_FreeSurface(sur1610);
      sur1610 = TTF_RenderText_Solid(game->font, str1610, game->colorPalette[0]);
      SDL_FreeSurface(sur169);
      sur169 = TTF_RenderText_Solid(game->font, str169, game->colorPalette[0]);
      SDL_FreeSurface(surAd);
      surAd = TTF_RenderText_Solid(game->font, strAd, game->colorPalette[0]);
      SDL_FreeSurface(surBack);
      surBack = TTF_RenderText_Solid(game->font, strBack, game->colorPalette[0]);

    }

    SDL_RenderCopy(game->renderer, background, NULL, NULL);

    //blitting the options on the window
    tempT = SDL_CreateTextureFromSurface(game->renderer, surFull);
    SDL_QueryTexture(tempT, NULL, NULL, &(posFull->w), &(posFull->h));
    SDL_RenderCopy(game->renderer, tempT, NULL, posFull);

    tempT = SDL_CreateTextureFromSurface(game->renderer, sur43);
    SDL_QueryTexture(tempT, NULL, NULL, &(pos43->w), &(pos43->h));
    SDL_RenderCopy(game->renderer, tempT, NULL, pos43);

    tempT = SDL_CreateTextureFromSurface(game->renderer, sur1610);
    SDL_QueryTexture(tempT, NULL, NULL, &(pos1610->w), &(pos1610->h));
    SDL_RenderCopy(game->renderer, tempT, NULL, pos1610);

    tempT = SDL_CreateTextureFromSurface(game->renderer, sur169);
    SDL_QueryTexture(tempT, NULL, NULL, &(pos169->w), &(pos169->h));
    SDL_RenderCopy(game->renderer, tempT, NULL, pos169);

    tempT = SDL_CreateTextureFromSurface(game->renderer, surAd);
    SDL_QueryTexture(tempT, NULL, NULL, &(posAd->w), &(posAd->h));
    SDL_RenderCopy(game->renderer, tempT, NULL, posAd);

    tempT = SDL_CreateTextureFromSurface(game->renderer, surBack);
    SDL_QueryTexture(tempT, NULL, NULL, &(posBack->w), &(posBack->h));
    SDL_RenderCopy(game->renderer, tempT, NULL, posBack);

    render_cursor(*game);

    SDL_RenderPresent(game->renderer);

    SDL_Delay(1000 / SCREEN_FPS);

    //if we escape
    if (*control == 10) {
      option = 6;
    }

    if (option != 0) {
      free(control);
      SDL_FreeSurface(surFull);
      SDL_FreeSurface(sur43);
      SDL_FreeSurface(sur1610);
      SDL_FreeSurface(sur169);
      SDL_FreeSurface(surAd);
      SDL_FreeSurface(surBack);
      SDL_DestroyTexture(background);
      SDL_DestroyTexture(tempT);
      free(strFull);
      free(str43);
      free(str1610);
      free(str169);
      free(strAd);
      free(strBack);
      free(posFull);
      free(pos43);
      free(pos1610);
      free(pos169);
      free(posAd);
      free(posBack);
      free(event);
      return option;
    }
  }
}

//loop managing the menus
int render_menu (game_t *game) {

  //keeps the option in the main menu
  int *mainMenuOption = NULL;
  mainMenuOption = (int*)malloc(sizeof(int));
  if (mainMenuOption == NULL) {
    printf("Error allocating memory for the mainMenuOption\n");
    return 0;
  }
  *mainMenuOption = 0;

  //keeps the option in the option menu
  int *optionMenuOption = NULL;
  optionMenuOption = (int*)malloc(sizeof(int));
  if (optionMenuOption == NULL) {
    printf("Error allocating memory for the *optionMenuOption\n");
    return 0;
  }
  *optionMenuOption = 0;

  //while we are in the main or option menu
  while (*mainMenuOption == 0 || *mainMenuOption == 2) {

    //set the option menu to 0, which means nothing have been selected
    *optionMenuOption = 0;

    //getting the option selected from the main menu
    *mainMenuOption = main_menu_display (game);

    //if we wanna enter the option menu
    if (*mainMenuOption == 2) {

      //while we don't select back in the option menu
      while (*optionMenuOption != 6) {

        //getting the option selected from the option menu
        *optionMenuOption = option_menu_display (game);

        //depending on the choice selected
        switch (*optionMenuOption) {

          case 1:
            //option 1
            break;

          case 2:
            //option 2
            break;

          case 3:
            //option 3
            break;

          case 4:
            //option 4
            break;

          case 5:
            //option 5
            break;

          case 6:
            //option 6 : quitting the option menu
            *mainMenuOption = 0;
            *optionMenuOption = 6;
            break;

        }

      }
    }

    //if we choose "quit" in the main menu
    if (*mainMenuOption == 3) {
      //quitting the game
      game->quit = true;

      free(mainMenuOption);
      free(optionMenuOption);

      return 1;
    }

    //if we wanna Continue
    if (*mainMenuOption == 1) {

      free(mainMenuOption);
      free(optionMenuOption);

      return 1;
    }

  }

  //security check
  free(mainMenuOption);
  free(optionMenuOption);

  return 1;

}
