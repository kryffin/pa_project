SRC=main.c #source file
BIN=ant #exe file
INC=header.h #to check before each compile

$(BIN): $(SRC) $(INC)
	gcc -Wall -g -std=c99 $(SRC) `sdl-config --cflags --libs` -o $(BIN) -lSDL_ttf

clean:
	rm -f $(BIN)
