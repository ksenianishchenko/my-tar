NAME = mytar

HEADER = header.h

FLAGS = -I.

SRC = my-tar.c extract.c list.c my-tar.c options.c tar.c

OBJ = $(SRC:.c=.o)

%.o: %.c $(HEADER)
	gcc -c -o $@ $< $(FLAGS)

$(NAME): $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o *~ $(NAME)
