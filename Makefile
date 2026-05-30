C = gcc
CFLAGS = -Wall -Wextra -g

SRC = main.c cart.c mmu.c cpu.c
OBJ = $(SRC:.c=.o)

gb: $(OBJ)
		$(CC) -o gb $(OBJ) $(CFLAGS)

clean:
		rm -f $(OBJ) gb
