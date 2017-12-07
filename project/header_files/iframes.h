#ifndef IFRAMES_H
#define IFRAMES_H

/************/
/* INCLUDES */
/************/

#include <stdbool.h>

/**************/
/* STRUCTURES */
/**************/

typedef struct Invincibility_Frames {
  int delay; //delay the duration of invicibility
  bool invincible; //states if it is invincible or not

  int displayDelay; //delay between each displaying of the sprite
  bool display; //states if the object needs to be displayed or not
}i_frames_t;

/*************/
/* FUNCTIONS */
/*************/

/* SET */

//initialize an iframe struct
i_frames_t init_i_frames ();

//set the delay
void set_i_frames_delay (i_frames_t *f, int delay);

//set the invincible state
void set_i_frames_invincible (i_frames_t *f, bool invincible);

//set the display delay
void set_i_frames_display_delay (i_frames_t *f, int displayDelay);

//set the display state
void set_i_frames_display (i_frames_t *f, bool display);

/* GET */

//get the delay
int get_i_frames_delay (i_frames_t f);

//get the invincible state
bool get_i_frames_invincible (i_frames_t f);

//set the display delay
int get_i_frames_display_delay (i_frames_t f);

//get the display state
bool get_i_frames_display (i_frames_t f);

#endif
