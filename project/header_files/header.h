#ifndef HEADER_H
#define HEADER_H

/* CONSTANTS */

//window
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32
#define SCREEN_FPS 30
#define FONT_SIZE 15
//img
#define BULLET_WIDTH 16
#define BULLET_HEIGHT 16
#define BULLET_SPEED 10
//paths
#define PATH_SPRITES "./res/spritesheet.png"
#define PATH_FONT "./res/font.ttf"
#define PATH_CURSOR "./res/cursor.png"
#define PATH_BLOCKS_SHEET "./res/blocks_spritesheet.png"
#define PATH_BACKGROUND "./res/background.bmp"
#define PATH_TXT_FILE "./res/arena.txt"
#define PATH_YOU_DIED "./res/you_died.png"
//delays
#define PLAYER_SHOOT_DELAY 100
#define ENEMY_SHOOT_DELAY 500

#define DELAY_STEP 150 //delay for the step updating

#define JUMP_HEIGHT -24
#define GRAVITY 4

#define NB_BLOCKS_WIDTH 40
#define NB_BLOCKS_HEIGHT 30

#define IMG_WIDTH 32
#define IMG_HEIGHT 64

#define CURSOR_WIDTH 15
#define CURSOR_HEIGHT 15

#define JUMP_DURATION 50

#endif
