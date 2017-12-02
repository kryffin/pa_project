#include "../header_files/music.h"

/* set */

//create a music box
musicbox_t set_music_box (char *rifle, char *shotgun, char *missile) {

  musicbox_t box;
  set_rifle_sound_effect(&box, rifle);
  set_shotgun_sound_effect(&box, shotgun);
  set_missile_sound_effect(&box, missile);

  return box;
}

//set the rifle sound effect
void set_rifle_sound_effect (musicbox_t *box, char *path) {
  box->rifleSoundEffect = Mix_LoadWAV(path);
  if (box->rifleSoundEffect == NULL) {
    printf("Error while setting rifle sound effect : %s\n", Mix_GetError());
    exit(0);
  }

  return;
}

//set the shotgun sound effect
void set_shotgun_sound_effect (musicbox_t *box, char *path) {
  box->shotgunSoundEffect = Mix_LoadWAV(path);
  if (box->shotgunSoundEffect == NULL) {
    printf("Error while setting shotgun sound effect : %s\n", Mix_GetError());
    exit(0);
  }

  return;
}

//set the missile sound effect
void set_missile_sound_effect (musicbox_t *box, char *path) {
  box->missileSoundEffect = Mix_LoadWAV(path);
  if (box->missileSoundEffect == NULL) {
    printf("Error while setting missile sound effect : %s\n", Mix_GetError());
    exit(0);
  }

  return;
}
