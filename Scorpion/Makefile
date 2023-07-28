NAME = scorpion
CC = cc
CFLAGS = -Wall -Wextra -Werror


FILES = scorpion.c \
		mem.c \
		jpeg_parse.c \
		exif.c \

OBJ = $(FILES:.c=.o)

all: $(NAME)
	

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo '~ Scorpion is ready to sting!'

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

ex:	$(NAME)
	@./scorpion images/test.jpg
	

re: fclean all
