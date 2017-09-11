#ifndef _LEVEL_H_
#define _LEVEL_H_

struct Level {
  SDL_Color col; //background color of the level (change to SDL_Surface for an image)

  short int nbBlocks; //number of used blocks
  block blocks[10]; //10 blocks to make a level (temporary)

  /* player p; //the player (player : WIP) */

  /*short int nbEnemies; //number of existing enemies
  enemy enemies[10]; //10 enemies max on a level (temporary) (enemy : WIP) */

  /*short int nbItems; //number of existing items
  item items[10]; //10 items max o a level (temporary) (item : WIP) */
};

typedef struct Level level;

void level_blit (level l, SDL_Surface *screen);

#endif
