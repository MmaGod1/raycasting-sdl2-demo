CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
SRC = source/main.c source/render.c source/utils.c
OBJ = $(SRC:.c=.o)
INC = -I header/
SDL2 = `sdl2-config --cflags --libs`
LIBS = -lm

all: raycasting

raycasting: $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o raycasting $(SDL2) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ) raycasting

.PHONY: clean
