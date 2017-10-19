SRC=main.c controls.c player.c menu.c projectile.c var_init.c vector.c 2dpoint.c level.c blocks.c #source file
BIN=mvt #exe file


$(BIN): $(SRC)
	gcc -Wall -g -std=c99 $(SRC) -lSDL2 -o $(BIN) -lSDL2_ttf -lSDL2_gfx -lm

clean:
	rm -f $(BIN)
