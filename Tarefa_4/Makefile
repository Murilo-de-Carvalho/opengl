exec = main
CC = gcc
CFLAGS = -std=c99 -Wextra -g -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -lGL -lGLU -lglut -lm -lX11 #-fsanitize=address
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

$(exec): $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) -o $(exec)
	@rm *.o

%.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

run: $(exec)
	@./$(exec)

clean:
	@rm $(exec)