#ifndef TDPOINT_H
#define TDPOINT_H

/************/
/* INCLUDES */
/************/

#include <stdbool.h>

/**************/
/* STRUCTURES */
/**************/

typedef struct IntegerPoint {
  int x;
  int y;
} intpoint_t;

typedef struct FloatPoint_t {
  float x;
  float y;
} floatpoint_t;

/*************/
/* FUNCTIONS */
/*************/

/* SET */

//returns a new with float coordinates
floatpoint_t set_floatpoint (float x, float y);

//change the x coordinate of a floatpoint
void set_floatpoint_x (floatpoint_t *p, float x);

//change the y coordinate of a floatpoint
void set_floatpoint_y (floatpoint_t *p, float y);

//----------------

//returns a new with integer coordinates
intpoint_t set_intpoint (int x, int y);

//change the x coordinate of an intpoint
void set_intpoint_x (intpoint_t *p, int x);

//change the y coordinate of an intpoint
void set_intpoint_y (intpoint_t *p, int y);

/* GET */

//returns the x coordinate of a floatpoint
float get_floatpoint_x (floatpoint_t p);

//returns the y coordinate of a floatpoint
float get_floatpoint_y (floatpoint_t p);

//----------------

//returns the x coordinate of an intpoint
int get_intpoint_x (intpoint_t p);

//returns the y coordinate of an intpoint
int get_intpoint_y (intpoint_t p);

#endif
