/*

iframes.c : contains every functions to manage the invincibility frames after getting hit

*/

#include "../header_files/iframes.h"

/* SET */

//initialize an iframe struct
i_frames_t init_i_frames () {
  i_frames_t f;
  set_i_frames_delay(&f, 0);
  set_i_frames_invincible(&f, false);

  set_i_frames_display_delay(&f, 0);
  set_i_frames_display(&f, true);

  return f;
}

//set the delay
void set_i_frames_delay (i_frames_t *f, int delay) {
  f->delay = delay;
  return;
}

//set the invincible state
void set_i_frames_invincible (i_frames_t *f, bool invincible) {
  f->invincible = invincible;
  return;
}

//set the display delay
void set_i_frames_display_delay (i_frames_t *f, int displayDelay) {
  f->displayDelay = displayDelay;
  return;
}

//set the display state
void set_i_frames_display (i_frames_t *f, bool display) {
  f->display = display;
  return;
}

/* GET */

//get the delay
int get_i_frames_delay (i_frames_t f) {
  return f.delay;
}

//get the invincible state
bool get_i_frames_invincible (i_frames_t f) {
  return f.invincible;
}

//set the display delay
int get_i_frames_display_delay (i_frames_t f) {
  return f.displayDelay;
}

//get the display state
bool get_i_frames_display (i_frames_t f) {
  return f.display;
}
