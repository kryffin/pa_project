#include "header.h"

/* BLITTING */

void player_blit (player p, SDL_Texture *img, SDL_Renderer *renderer) {

  SDL_Rect *temp = NULL;
  temp = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  temp->w = 32;
  temp->h = 64;

  if (get_player_dir(p) == 1) {
    //player facing right

    switch (get_player_state(p)) {

      //stand-by/walking
      case 0:

        if (get_player_vel_x(p) == 0 && get_player_vel_y(p) == 0) {
          //stand by sprite
          temp->x = 0;
          temp->y = 0;
          set_player_sprite_pos(&p, *temp);

        } else {

          //sprite moving
          temp->x = 32;
          temp->y = 0;
          set_player_sprite_pos(&p, *temp);

        }

        break;

      //jumping or double-jumping
      case 1:
      case 2:

      temp->x = 96;
      temp->y = 0;
      set_player_sprite_pos(&p, *temp);

        break;

      //attacking
      case 3:

      temp->x = 64;
      temp->y = 128;
      set_player_sprite_pos(&p, *temp);

        break;

      //crouching
      case 4:

        temp->x = 128;
        temp->y = 0;
        set_player_sprite_pos(&p, *temp);

        break;

      default:
        break;
    }

  } else {
    //player facing left

    switch (get_player_state(p)) {

      //stand-by/walking
      case 0:

        if (get_player_vel_x(p) == 0 && get_player_vel_y(p) == 0) {

          //stand by sprite
          temp->x = 0;
          temp->y = 64;
	  
          set_player_sprite_pos(&p, *temp);

        } else {

          //sprite moving
          temp->x = 32;
          temp->y = 64;
          set_player_sprite_pos(&p, *temp);

        }

        break;

      //jumping or double-jumping
      case 1:
      case 2:

      temp->x = 96;
      temp->y = 64;
      set_player_sprite_pos(&p, *temp);

        break;

      //attacking
      case 3:

      temp->x = 96;
      temp->y = 128;
      set_player_sprite_pos(&p, *temp);

        break;

      //crouching
      case 4:

        temp->x = 128;
        temp->y = 64;
        set_player_sprite_pos(&p, *temp);

        break;

      default:
        break;
    }

  }

  SDL_RenderCopy(renderer, p.img, &(p.spritePos), &(p.posAbs));

  free(temp);
}

/* BEHAVIOR */

void player_melee (player p, SDL_Renderer *renderer) {

  SDL_Rect *target = NULL;
  target = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  *target = get_player_posAbs(p);

  SDL_Rect *effect = NULL;
  effect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  effect->y = 128;
  effect->w = 32;
  effect->h = 64;

  if (get_player_dir(p) == 0) {
    //facing left
    target->x -= IMG_WIDTH;
    effect->x = 32;

  } else {
    //facing right
    target->x += IMG_WIDTH;
    effect->x = 0;

  }

  SDL_RenderCopy(renderer, p.img, effect, target);

  free(target);
  free(effect);

}

void player_apply_velocity (player *p, Uint32* timeN_A, Uint32* timeN_B) {
  
  set_player_posAbs(p, get_player_posAbs(*p).x + get_player_vel_x(*p), get_player_posAbs(*p).y + get_player_vel_y(*p), get_player_posAbs(*p).w, get_player_posAbs(*p).h);
  return;
}

void player_jumping (player *p, Uint32* timeN_A, Uint32* timeN_B) {
  //SDL_Rect* prevPos = NULL;
  //prevPos = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  // *prevPos = get_player_posAbs(*p); //enregistrement de la derniere position
  set_player_posRel (p, 0, 0); //on init le repere
  /* l'entité est en train de sauté */
  if (get_player_state(*p) == 1 || get_player_state(*p) == 2)
    {
      //premiere phase du saut (500ms)
      if (*timeN_A +500 < *timeN_B){
	printf("premiere demi seconde\n");
	//premier cas le joueur va vers la droite
	if (get_player_dir(*p) == 1)
	  {  
	    set_player_posRel (p, get_player_posRel(*p).x +1, (COEF_A*(pow(get_player_posRel(*p).x, 2)+COEF_C)));
	  }
	else
	  {
	    set_player_posRel (p, get_player_posRel(*p).x -1, (COEF_A*(pow(get_player_posRel(*p).x, 2)+COEF_C)));
	  }
	//TODO FONCTION COLISION EADGES SCREEN
	/*..
	  ..
	  ..
	*/

	// pos.x = x+1, pos.y = posAbs + posRel
    	set_player_posAbs(p, get_player_posAbs(*p).x + get_player_posRel(*p).x, get_player_posAbs(*p).y + get_player_posRel(*p).y, 32, 32); 
	return;
      }
      
      else if (*timeN_A < *timeN_B)// timeN_A + 500 >= timeN_B
	{
	  //deuxieme phase du saut (+500ms)
	  printf("deuxieme demi seconde\n");
	  if (get_player_dir(*p) == 1) //direction droite
	    {
	      set_player_posRel (p, get_player_posRel(*p).x +1, (COEF_A*(pow(get_player_posRel(*p).x, 2)+COEF_C)));
	    }
	  else
	    {
	    set_player_posRel (p, get_player_posRel(*p).x -1, (COEF_A*(pow(get_player_posRel(*p).x, 2)+COEF_C)));
	    }
	  
	  //TODO FONCTION COLISION EADGES SCREEN
	  /*..
	    ..
	    ..
	  */
	  
	  // pos.x = x+1, pos.y = posAbs - posRel
	  set_player_posAbs(p, get_player_posAbs(*p).x + get_player_posRel(*p).x, get_player_posAbs(*p).y - get_player_posRel(*p).y, 32, 32);
	  return;
	}
      else//timeN_A > timeN_B
	{// fin de la seconde de saut
	  set_player_state(p, 0);
	  *timeN_A = *timeN_B;
	  *timeN_B = SDL_GetTicks();
	  set_player_posRel (p, 0, 0);
	  return;
	}
      
     
    }//l'entitée ne saute pas
  printf("doesnt jump\n");
  //free (prevPos);
  //set_player_state (p, 0);
  return;
}


/* SET */

//create a new player
player set_player (short int maxHealthPoints, short int healthPoints, short int direction, bool doubleJump, SDL_Rect position, SDL_Rect velocity, SDL_Texture *image, SDL_Rect posSprite) {
  player p;
  vector* tempVector;
  tempVector = (vector*)malloc(sizeof(vector));
  tempVector->x = 0;
  tempVector->y = 0;
  
  set_player_maxhp(&p, maxHealthPoints);
  set_player_hp(&p, healthPoints);
  set_player_dir(&p, direction);
  set_player_dJump(&p, doubleJump);
  set_player_jumpPoint(&p, *tempVector);
  set_player_highPoint(&p, *tempVector);
  set_player_state(&p, 0);
  set_player_posAbs(&p, position.x, position.y, position.w, position.h);
  set_player_vel_x(&p, velocity.x);
  set_player_vel_y(&p, velocity.y);
  set_player_img(&p, image);
  set_player_sprite_pos(&p, posSprite);

  free(tempVector);
  return p;
}

//copy a target player p into player q
player set_player_copy (player p) {
  player *q = (player*)malloc(sizeof(player));
  set_player_maxhp(q, get_player_maxhp(p));
  set_player_hp(q, get_player_hp(p));
  set_player_dir(q, get_player_dir(p));
  set_player_dJump(q, get_player_dJump(p));
  set_player_vel_x(q, get_player_vel_x(p));
  set_player_vel_y(q, get_player_vel_y(p));
  set_player_img(q, get_player_img(p));

  return *q;
}

//set the player's max health points
void set_player_maxhp (player *p, short int maxhp) {
  p->maxhp = maxhp;
  return;
}

//set the player's health points
void set_player_hp (player *p, short int hp) {
  p->hp = hp;
  return;
}

//set the current direction
void set_player_dir (player *p, short int dir) {
  p->dir = dir;
  return;
}

//set the player's ability to double jump
void set_player_dJump (player *p, bool dJump) {
  p->dJump = dJump;
  return;
}

//set the player's jump point
void set_player_jumpPoint (player *p, vector jumpPoint) {
  p->jumpPoint = jumpPoint;
  return;
}

//set the player's high point
void set_player_highPoint (player *p, vector highPoint) {
  p->highPoint = highPoint;
  return;
}

//set the player's state
void set_player_state (player *p, short int state) {
  p->state = state;
  return;
}

//set the player's position
void set_player_posAbs (player *p, int pos_x, int pos_y, int pos_w, int pos_h) {
  p->posAbs.x = pos_x;
  p->posAbs.y = pos_y;
  p->posAbs.w = pos_w;
  p->posAbs.h = pos_h;
  return;
}

void set_player_posRel (player *p, int pos_x, int pos_y){
  p->posRel.x = pos_x;
  p->posRel.y = pos_y;
}
//set the player's x velocity
void set_player_vel_x (player *p, int vel_x) {
  p->vel.x = vel_x;
  return;
}

//set the player's y velocity
void set_player_vel_y (player *p, int vel_y) {
  p->vel.y = vel_y;
  return;
}

//set the player's image
void set_player_img (player *p, SDL_Texture *img) {
  p->img = img;
  return;
}

//set the player sprite position on the spritesheet
void set_player_sprite_pos (player *p, SDL_Rect posSprite) {
  p->spritePos = posSprite;
  return;
}

/* GET */

//get the player's max health points
short int get_player_maxhp (player p) {
  return p.maxhp;
}

//get the player's health points
short int get_player_hp (player p) {
  return p.hp;
}

//get the current direction
short int get_player_dir (player p) {
  return p.dir;
}

//get the player's ability to double jump
bool get_player_dJump (player p) {
  return p.dJump;
}

//get the player's jump point
vector get_player_jumpPoint (player p) {
  return p.jumpPoint;
}

//get the player's high point
vector get_player_highPoint (player p) {
  return p.highPoint;
}

//get the player's state
short int get_player_state (player p) {
  return p.state;
}

//get the player's position
SDL_Rect get_player_posAbs (player p) {
  return p.posAbs;
}

//get the player's real postion
vector get_player_posRel (player p) {
  return p.posRel;
}

//get the player's x velocity
int get_player_vel_x (player p) {
  return p.vel.x;
}

//get the player's y velocity
int get_player_vel_y (player p) {
  return p.vel.y;
}


//get the player's image
SDL_Texture* get_player_img (player p) {
  return p.img;
}

//get the player's sprite position on the sprite sheet
SDL_Rect get_player_sprite_pos (player p) {
  return p.spritePos;
}
