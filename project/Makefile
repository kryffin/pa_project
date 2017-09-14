SRC=main.c controls.c player.c #source file
BIN=mvt #exe file
INC=header.h #to check before each compile

$(BIN): $(SRC) $(INC)
	gcc -Wall -g -std=c99 $(SRC) -lSDL2 -o $(BIN) -lSDL2_ttf

clean:
	rm -f $(BIN)
