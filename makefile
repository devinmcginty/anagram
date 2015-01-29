CC = gcc
FILES = main.c wordhash.c
HEADERS = wordhash.h
OUTFILE = anagram.out
SCRABBLE_FLAG = -f
RM = rm -f

build: $(FILES) $(HEADERS)
	$(CC) $(FILES) -o $(OUTFILE)

anagram:
	./$(OUTFILE) $(WORD)

scrabble:
	./$(OUTFILE) $(SCRABBLE_FLAG) $(WORD)

clean:
	$(RM) *.o *.out $(OUTFILE)

rebuild: clean build
