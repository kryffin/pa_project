SRC=bouncy_img.c #source file
BIN=bouncy_img #exe file
INC=header.h #to check before each compile

$(BIN): $(SRC) $(INC)
	gcc -Wall -g  -std=c99 $(SRC) `sdl-config --cflags --libs` -o $(BIN) -lm -lSDL_ttf

clean:
	rm -f $(BIN)
