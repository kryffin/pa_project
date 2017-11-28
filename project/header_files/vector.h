#ifndef VECTOR_H
#define VECTOR_H

/************/
/* INCLUDES */
/************/

#include <SDL2/SDL.h>
#include <math.h>

/**************/
/* STRUCTURES */
/**************/

typedef struct Vector {
  float x;
  float y;
} vector_t;

/*************/
/* FUNCTIONS */
/*************/

//returns the normalized vector
vector_t normalize (vector_t v);

//return a direction vector between a and b
vector_t vector_direction (SDL_Rect a, SDL_Rect b);

//returns the length of a vector
float vector_length (vector_t v);

/* SET */

//create a new vector
vector_t set_vector (float x, float y);

//set the x coordinate
void set_vector_x (vector_t *v, float x);

//set the y coordinate
void set_vector_y (vector_t *v, float y);

/* GET */

//get the x coordinate
float get_vector_x (vector_t v);

//get the y coordinate
float get_vector_y (vector_t v);

#endif
