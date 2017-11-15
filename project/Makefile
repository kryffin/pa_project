SRC = source_files/2dpoint.c source_files/vector.c source_files/menu.c source_files/player.c source_files/projectile.c source_files/controls.c source_files/blocks.c source_files/level.c source_files/var_init.c source_files/main.c #source file
BIN = mvt #exe file
INC = header_files/header.h header_files/2dpoint.h header_files/vector.h header_files/menu.h header_files/player.h header_files/projectile.h header_files/controls.h header_files/blocks.h header_files/level.h header_files/var_init.h #header file

CC = gcc
FLAGS = -Wall -g -std=c99
LIBS = -lSDL2_ttf -lSDL2_gfx -lSDL2_image -lm

$(BIN): $(SRC) $(INC)
	$(CC) $(FLAGS) $(SRC) $(INC) -lSDL2 -o $(BIN) $(LIBS)

clean:
	rm -f $(BIN)
