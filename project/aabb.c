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





bool raw_test_aabb (player p, SDL_Rect hitboxWorld, unsigned short int type)
{
  /*penser a mettre tout ça en dynamique / ne plus décclarer dans le débyt
    de la fonction les strucutres AABB
   ie CF MTV research AABB collisions
     implanter dans la fonction player la struct AABB  ;)
  */
//si le type est un bloc dur test de la collision sinon on retourne faux
  if (type != 0){
    //printf("**\t%d\t\ttest2\n", type);
    return false;
  }
  else{
  //  AABB player;
    AABB* world;
    world = (AABB*)malloc(sizeof(AABB));
/*
    player.HG.x = get_player_real_position(p).x;
    player.HG.y = get_player_real_position(p).y;

    player.HD.x = get_player_real_position(p).x + get_player_hitbox(p).w;
    player.HD.y = get_player_real_position(p).y;

    player.BG.x = get_player_real_position(p).x + get_player_hitbox(p).h;
    player.BG.y = get_player_real_position(p).y + get_player_hitbox(p).h;

*/
    world->HG.x = hitboxWorld.x;
    world->HG.y = hitboxWorld.y;

    world->HD.x = hitboxWorld.x + hitboxWorld.w;
    world->HD.y = hitboxWorld.y;

    world->BG.x = hitboxWorld.x + hitboxWorld.h;
    world->BG.y = hitboxWorld.y + hitboxWorld.h;
    ///////////////////end initi var pour le traitement;
    printf("**\t%d\t\ttest1\n", type);
    free(world);
    if (point_dans_aabb(get_player_real_position(p), *world))
    {
      printf ("j'ai la kekette qui colle\n");
    }
    return (point_dans_aabb(get_player_real_position(p), *world));

    /* faire une fonction test du point dans aabb */

  }

}

bool point_dans_aabb (floatpoint realpos, AABB world)
{
  /*
    cette fonction bug elle ne renvoie pas le resultat esperer
  -/*/
    if (world.HG.x > realpos.x && realpos.x < world.HD.x){
      //dans l'intervale x
      if (world.HG.y > realpos.y && realpos.y < world.BG.y){
        return true;
      }
    }
    return false;

}

bool is_colision (player *p)
{
  if (get_player_screen_position(*p).y >= SCREEN_HEIGHT - IMG_HEIGHT)
  {
    return true;
  }
  return false;

}
void player_colision (player *p, level* l)
{

  //RAW COLLISIONS
  if (get_player_screen_position(*p).y >= SCREEN_HEIGHT - IMG_HEIGHT -1)
  {
    //printf("pos limit : %d \t current pos : %d\n", SCREEN_HEIGHT - IMG_HEIGHT, get_player_screen_position(*p).y);
    set_player_real_position (p, get_player_real_position(*p).x, SCREEN_HEIGHT - IMG_HEIGHT - 11);
    set_player_dJump(p, true);
    set_player_state(p, 0);
  }
  int indiceX, indiceY;
  indiceX = get_player_screen_position(*p).x / BLOCK_WIDTH ;
  indiceY = get_player_screen_position(*p).y / BLOCK_HEIGHT;

  if(raw_test_aabb(*p, l->blocks[indiceX-1][indiceY].hitbox, l->blocks[indiceX-1][indiceY].type))
    printf("collision bloc gauche\n");
    adjust_vector_collision(get_player_velocity(*p), p, l->blocks[indiceX-1][indiceY].box, 0.01);

  if(raw_test_aabb(*p, l->blocks[indiceX+1][indiceY].hitbox, l->blocks[indiceX+1][indiceY].type))
    printf("collision bloc droit\n");
    adjust_vector_collision(get_player_velocity(*p), p, l->blocks[indiceX+1][indiceY].box, 0.01);
    //set_player_real_position(p, get_player_screen_position(*p).x , get_player_screen_position(*p).y);

  if(raw_test_aabb(*p, l->blocks[indiceX][indiceY-1].hitbox, l->blocks[indiceX][indiceY-1].type))
    printf("collision bloc du haut\n");
    adjust_vector_collision(get_player_velocity(*p), p, l->blocks[indiceX][indiceY-1].box, 0.01);

  if(raw_test_aabb(*p, l->blocks[indiceX][indiceY+1].hitbox, l->blocks[indiceX-1][indiceY].type))
    printf("collision bloc du bas\n");
    adjust_vector_collision(get_player_velocity(*p), p, l->blocks[indiceX][indiceY+1].box, 0.01);

  //printf("___*\n%d\t%d\n%d\t%d\n*___\n", l->blocks[indiceX-1][indiceY-1].hitbox.x,  l->blocks[indiceX-1][indiceY-1].hitbox.y,  l->blocks[indiceX+1][indiceY-1].hitbox.x,  l->blocks[indiceX+1][indiceY-1].hitbox.y);

}

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
