SRC = source_files/main.c source_files/controls.c source_files/player.c source_files/menu.c source_files/projectile.c source_files/var_init.c source_files/vector.c source_files/2dpoint.c source_files/level.c source_files/blocks.c #source file
BIN = mvt #exe file
INC = header_files/header.h header_files/controls.h header_files/player.h header_files/menu.h header_files/projectile.h header_files/var_init.h header_files/vector.h header_files/2dpoint.h header_files/level.h header_files/blocks.h #header file


$(BIN): $(SRC) $(INC)
	gcc -Wall -g -std=c99 $(SRC) -lSDL2 -o $(BIN) -lSDL2_ttf -lSDL2_gfx -lSDL2_image -lm

clean:
	rm -f $(BIN)
