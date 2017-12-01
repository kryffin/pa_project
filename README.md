# -game title here-

Programmation Avancée project of L2-S3 2017/2018

## Getting Started

These instructions will get you to a playable executable file of our game.

### Prerequisites

You will need :

- SDL2
- SDL_ttf
- SDL_image
- SDL2_framerate

### Compiling

For Linux users (from the file containing the Makefile) :
'''
make -f Makefile
./mvt
'''

For Window users :
'''
to do
'''

## Memory leaks

There is no known memory leaks in our game, but using valgrind you can also verify:
'''
valgrind ./mvt
'''

## Built With

* [SDL2.0](https://www.libsdl.org/index.php)
* [SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/)
* [SDL_image](https://www.libsdl.org/projects/SDL_image/)
* [SDL2_framerate](http://www.ferzkopp.net/wordpress/2016/01/02/sdl_gfx-sdl2_gfx/) (contained in SDL_gfx)

## Authors

* **GOUTH Pierre** - [314wind](https://github.com/314wind)
* **KLEINHENTZ Nicolas** - [Kryffin](https://github.com/kryffin)

## The project Itself

This last section is designed to explain and show the various files of our game.

### Source Files - _.c_

* **2dpoint**
  - _Contains every fonctions for the intpoints and floatpoints structures._
  - Number of lines : **74**

* **blocks**
  - _Contains every fonctions for the block structure._
  - Number of lines : **67**

* **character**
  - _Contains every fonctions for the character structure, character list structure and various functions updating the characters._
  - Number of lines : **592**

* **controls**
  - _Contains every fonctions for the controls of the game (keyboard and mouse)._
  - Number of lines : **240**

* **game**
  - _Contains every fonctions for the game structure containing everything to run the game itself._
  - Number of lines : **210**

* **level**
  - _Contains every fonctions for the level structure._
  - Number of lines : **249**

* **main**
  - _Contains the main function (main loop running the game)._
  - Number of lines : **97**

* **menu**
  - _Contains every fonctions for the main menu at the game launch._
  - Number of lines : **293**

* **projectile**
  - _Contains every fonctions for the projectile structure and projectile list structure._
  - Number of lines : **135**

* **rendering**
  - _Contains every fonctions to render the game on the screen._
  - Number of lines : **428**

* **vector**
  - _Contains every fonctions for the vector structure._
  - Number of lines : **70**

### Header Files - _.h_

* **2dpoint**
  - _Contains every signatures for the intpoints and floatpoints structures._
  - Number of lines : **73**

* **blocks**
  - _Contains every signatures for the block structure._
  - Number of lines : **58**

* **character**
  - _Contains every signatures for the character structure, character list structure and various functions updating the characters._
  - Number of lines : **256**

* **controls**
  - _Contains every signatures for the controls of the game (keyboard and mouse)._
  - Number of lines : **61**

* **game**
  - _Contains every signatures for the game structure containing everything to run the game itself._
  - Number of lines : **84**

* **header**
  - _Contains the main includes and defines._
  - Number of lines : **40**

* **level**
  - _Contains every signatures for the level structure._
  - Number of lines : **93**

* **menu**
  - _Contains every signatures for the main menu at the game launch._
  - Number of lines : **66**

* **projectile**
  - _Contains every signatures for the projectile structure and projectile list structure._
  - Number of lines : **120**

* **rendering**
  - _Contains every signatures to render the game on the screen._
  - Number of lines : **44**

* **vector**
  - _Contains every signatures for the vector structure._
  - Number of lines : **55**

### Resource Files - _images and levels_

* **arena**
  - _.txt file : contains the arena level._

* **arenabackground**
  - _.jpg file : background to use in the arena._

* **background**
  - _.png file : contains the menu background._

* **background1**
  - _.jpg file : background to use in the first level._

* **background2**
  - _.png file : background to use in the second level._

* **background3**
  - _.jpg file : background to use in the third level._

* **blocks_spritesheet**
  - _.png file : sprite sheet of the blocks._

* **cursor**
  - _.png file : image of the cursor._

* **font**
  - _.ttf file : font used in the game (name of the font here)._

* **level1**
  - _.txt file : setup to use in the first level._

* **level2**
  - _.txt file : setup to use in the second level._

* **level3**
  - _.txt file : setup to use in the third level._

* **spritesheet**
  - _.png file : sprite sheet of the characters._

* **you_died**
  - _.png file : death screen used on death of the player._

## Metrics

Total lines of code :
  - Source files : 2,455
  - Header files : 950
  - Makefile : 13
  - **Total : 3,418**

Total images : 9

# The end
