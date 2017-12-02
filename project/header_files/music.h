#ifndef MUSIC_H
#define MUSIC_H

/************/
/* INCLUDES */
/************/

#include <SDL/SDL_mixer.h>

/**************/
/* STRUCTURES */
/**************/

typedef struct MusicBox {

  Mix_Chunk *rifleSoundEffect; //sound effect for the 1st weapon
  Mix_Chunk *shotgunSoundEffect; //sound effect for the 2nd weapon
  Mix_Chunk *missileSoundEffect; //sound effect for the 3rd weapon

} musicbox_t;

/*************/
/* FUNCTIONS */
/*************/

/* set */

//create a music box
musicbox_t set_music_box (char *rifle, char *shotgun, char *missile);

//setthe rifle sound effect
void set_rifle_sound_effect (musicbox_t *box, char *path);

//set the shotgun sound effect
void set_shotgun_sound_effect (musicbox_t *box, char *path);

//set the missile sound effect
void set_missile_sound_effect (musicbox_t *box, char *path);

#endif
