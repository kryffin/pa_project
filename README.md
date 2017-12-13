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

There is 64 bytes of leaked memory in our game, but using valgrind you can also verify:
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
  - Number of lines : **765**

* **controls**
  - _Contains every fonctions for the controls of the game (keyboard and mouse)._
  - Number of lines : **218**

* **game**
  - _Contains every fonctions for the game structure containing everything to run the game itself._
  - Number of lines : **243**

* **iframes**
  - _Contains every fonctions for the invincibility frames of the characters._
  - Number of lines : **67**

* **level**
  - _Contains every fonctions for the level structure._
  - Number of lines : **315**

* **main**
  - _Contains the main function (main loop running the game)._
  - Number of lines : **95**

* **menu**
  - _Contains every fonctions for the main menu at the game launch._
  - Number of lines : **299**

* **projectile**
  - _Contains every fonctions for the projectile structure and projectile list structure._
  - Number of lines : **152**

* **rendering**
  - _Contains every fonctions to render the game on the screen._
  - Number of lines : **553**

* **vector**
  - _Contains every fonctions for the vector structure._
  - Number of lines : **70**

### Header Files - _.h_

* **2dpoint**
  - _Contains every signatures for the intpoints and floatpoints structures._
  - Number of lines : **66**

* **blocks**
  - _Contains every signatures for the block structure._
  - Number of lines : **58**

* **character**
  - _Contains every signatures for the character structure, character list structure and various functions updating the characters._
  - Number of lines : **282**

* **controls**
  - _Contains every signatures for the controls of the game (keyboard and mouse)._
  - Number of lines : **54**

* **game**
  - _Contains every signatures for the game structure containing everything to run the game itself._
  - Number of lines : **96**

* **header**
  - _Contains the main includes and defines._
  - Number of lines : **33**

* **iframes**
  - _Contains every signatures for the invincibility frames._
  - Number of lines : **57**

* **level**
  - _Contains every signatures for the level structure._
  - Number of lines : **103**

* **menu**
  - _Contains every signatures for the main menu at the game launch._
  - Number of lines : **57**

* **projectile**
  - _Contains every signatures for the projectile structure and projectile list structure._
  - Number of lines : **125**

* **rendering**
  - _Contains every signatures to render the game on the screen._
  - Number of lines : **47**

* **vector**
  - _Contains every signatures for the vector structure._
  - Number of lines : **55**

### Resource Files - _images and levels_

* **arena**
  - _.jpg file : contains the arena background._

* **arena**
  - _.mp3 file : contains the arena music._

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
  - _.mp3 file : music of the first level._

* **level1**
  - _.txt file : setup to use in the first level._

* **level2**
  - _.mp3 file : music of the second level._

* **level2**
  - _.txt file : setup to use in the second level._

* **level3**
  - _.mp3 file : music of the third level._

* **level3**
  - _.txt file : setup to use in the third level._

* **menu**
  - _.mp3 file : music of the menu._

* **menubackground**
  - _.jpg file : background of the menu._

* **missile**
  - _.wav file : sound effect of the missile._

* **rifle**
  - _.wav file : sound effect of the rifle._

* **shotgun**
  - _.wav file : sound effect of the shotgun._

* **spritesheet**
  - _.png file : sprite sheet of the characters._

* **you_died**
  - _.png file : death screen used on death of the player._

## Metrics

Total lines of code :
  - Source files : 2,918
  - Header files : 1,033
  - Makefile : 13
  - **Total : 3,964**

# The end
