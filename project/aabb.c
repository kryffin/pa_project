#include "header.h"


floatpoint get_aabb_HG (AABB box){
  return box.HG;
}
floatpoint get_aabb_HD (AABB box){
  return box.HD;
}
floatpoint get_aabb_BG (AABB box){
  return box.BG;
}
floatpoint get_aabb_BD (AABB box){
  return box.BD;
}
floatpoint get_aabb_middle (AABB box){
  return box.middle;
}
vector get_aabb_size (AABB box){
  return box.size;
}

void set_aabb_HG (AABB *box, floatpoint hg){
  box->HG = hg;
}
void set_aabb_HD (AABB *box, floatpoint hd){
  box->HD = hd;
}
void set_aabb_BG (AABB *box, floatpoint bg){
  box->BG = bg;
}
void set_aabb_BD (AABB *box, floatpoint bd){
  box->BD = bd;
}
void set_aabb_middle (AABB *box, floatpoint middlePoint){
  box->middle = middlePoint;
}
void set_aabb_size (AABB *box, vector size){
  box->size = size;
}



bool is_colision (player *p, level *l)
{

  /*
  indiceX+0 indice Y+0 : haut gauche
  indiceX+0 indice Y+1 : milieu haut gauche
  indiceX+0 indice Y+2 : milieu bas gauche
  indiceX+0 indice Y+3 : bas gauche


  __________________________________

  indiceX+1 indice Y+0 : haut droite
  indiceX+1 indice Y+1 : milieu haut droite
  indiceX+1 indice Y+2 : milieu bas droite
  indiceX+1 indice Y+3 : bas droite



  */
  int indiceX, indiceY;
  bool collision;
  unsigned short int i, j;

  indiceX = get_player_screen_position(*p).x / BLOCK_WIDTH ;
  indiceY = get_player_screen_position(*p).y / BLOCK_HEIGHT;

  collision = check_collision_bb(get_player_hitbox(*p), l->blocks[indiceX][indiceY].hitbox)||
              check_collision_bb(get_player_hitbox(*p), l->blocks[indiceX][indiceY+1].hitbox)||
              check_collision_bb(get_player_hitbox(*p), l->blocks[indiceX][indiceY+2].hitbox)||
              check_collision_bb(get_player_hitbox(*p), l->blocks[indiceX][indiceY+3].hitbox)||
              check_collision_bb(get_player_hitbox(*p), l->blocks[indiceX+1][indiceY].hitbox)||
              check_collision_bb(get_player_hitbox(*p), l->blocks[indiceX+1][indiceY+1].hitbox)||
              check_collision_bb(get_player_hitbox(*p), l->blocks[indiceX+1][indiceY+2].hitbox)||
              check_collision_bb(get_player_hitbox(*p), l->blocks[indiceX+1][indiceY+3].hitbox);



  if (collision)
  {//collision plus fine
    //debug consol
    /*
    printf("*___________*\n");
    printf("  %d\t|", l->blocks[indiceX][indiceY].type);
    printf("  %d\n", l->blocks[indiceX+1][indiceY].type);
    printf("  %d\t|", l->blocks[indiceX][indiceY+1].type);
    printf("  %d\n", l->blocks[indiceX+1][indiceY+1].type);
    printf("  %d\t|", l->blocks[indiceX][indiceY+2].type);
    printf("  %d\n", l->blocks[indiceX+1][indiceY+2].type);
    printf("  %d\t|", l->blocks[indiceX][indiceY+3].type);
    printf("  %d\n", l->blocks[indiceX+1][indiceY+3].type);
    printf("___________\n\n");
    */

    for (i=0; i<2; i++)
    {
      for (j=0; j<4; j++)
      {
        if (check_collision_bb(get_player_hitbox(*p), l->blocks[indiceX+i][indiceY+j].hitbox) && l->blocks[indiceX+i][indiceY+j].type == 0)
        {
          correct_position(p, *l, i, j, indiceX, indiceY);
          set_player_dJump(p, true);
          set_player_vel_y(p, 0.);
          set_player_state(p, 0);
          return true;
        }
      }
    }


  }
  else {

    return false;
  }
  //printf("****\n");
  p->enableGravity = true;
  return false;
}


void correct_position (player *p, level l, unsigned int i, unsigned int j, int x, int y)
{
    p->enableGravity = false;
    set_player_real_position (p, get_player_real_position(*p).x, get_player_real_position(*p).y);
  /*
  //on remet le perso sur le bord bas de lecran
  //set_player_real_position (p, get_player_real_position(*p).x,  ((y-1)*BLOCK_HEIGHT)+16);
  //printf("x:%f | y:%f\n\n", get_player_real_position(*p).x, get_player_real_position(*p).y);

  if(i==0)
  //gauche
  {
    switch (j) {
      case 0:
        set_player_real_position (p, get_player_real_position(*p).x, get_player_real_position(*p).y + 3*BLOCK_HEIGHT);
      break;

      case 1:
        set_player_real_position (p, get_player_real_position(*p).x, get_player_real_position(*p).y + 2*BLOCK_HEIGHT);
      break;

      case 2:
        set_player_real_position (p, get_player_real_position(*p).x, get_player_real_position(*p).y + BLOCK_HEIGHT);
      break;

      case 3:
        set_player_real_position (p, get_player_real_position(*p).x, get_player_real_position(*p).y);
      break;

      default:
      break;
    }
  }

  else
  //droite
  {

    switch (j) {
      case 0:

      break;

      case 1:

      break;

      case 2:

      break;

      case 3:

      break;

      default:
      break;

    }
  }*/

}


bool check_collision_bb (SDL_Rect A, SDL_Rect B)
{
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  leftA = A.x;
  rightA = A.x + A.w;
  topA = A.y;
  bottomA = A.y + A.h;

  leftB = B.x;
  rightB = B.x + B.w;
  topB = B.y;
  bottomB = B.y + B.h;

  if (bottomA <= bottomB) { 
    return false;
  }
  if (topA >= bottomB) { return false; }
  if (rightA <= leftB) { return false; }
  if (leftA >= rightB) { return false; }
  return true;

}

/*
void player_colision (player *p, level* l)
{

  //RAW COLLISIONS
  if (get_player_screen_position(*p).y >= SCREEN_HEIGHT - IMG_HEIGHT -1)
  {
    //printf("pos limit : %d \t current pos : %d\n", SCREEN_HEIGHT - IMG_HEIGHT, get_player_screen_position(*p).y);
    set_player_real_position (p, get_player_real_position(*p).x, SCREEN_HEIGHT - IMG_HEIGHT -16);
    set_player_dJump(p, true);
    set_player_state(p, 0);
  }
  //////////////////////////////////////////////////////////


}*/

bool point_dans_aabb (floatpoint point, AABB box){
  return true;

}
/*

void adjust_vector_collision(vector V, player *hero, AABB box, double eps)
{
    double min,max,mid;
    min = 0.0;
    max = 1.0;
    mid = (max+min)/2;
    hero->box.middle.x = hero->box.middle.x-(V.x*mid);
    hero->box.middle.y = hero->box.middle.y-(V.y*mid);

    update_player(hero);


    while(max-min>eps)
    {
        if(point_dans_aabb(get_player_real_position(*hero), box))
        {
            max=mid;
        }
        else
        {
            min=mid;
        }

        mid = (max+min)/2;
        hero->box.middle.x = hero->box.middle.x-(V.x*mid);
        hero->box.middle.y = hero->box.middle.y-(V.y*mid);
        update_player(hero);

    }
    //printf("mid : %f\n", mid);
    hero->box.middle.x = hero->box.middle.x-(V.x*mid);
    hero->box.middle.y = hero->box.middle.y-(V.y*mid);
    update_player(hero);
}
*/
