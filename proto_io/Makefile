SRC=proto.c #level.c #block.c #source file
BIN=proto #exe file


$(BIN): $(SRC)
	gcc -Wall -g -std=c99 $(SRC) -lSDL2 -o $(BIN)

clean:
	rm -f $(BIN)
