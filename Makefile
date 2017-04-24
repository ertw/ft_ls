#!/usr/bin/make -f

LIBRARY = ./libft/libft.a

NAME = recurse.out

HEADERS = recurse.h

OBJECTS = recurse.o

ifeq ($(mode),release)
	CFLAGS = -Wall -Werror -Wextra -g
else
	mode = debug
	CFLAGS = -Wall -Werror -Wextra -g -fno-omit-frame-pointer -fsanitize=address
endif

.PHONY:all
all: information $(NAME)

$(NAME): $(OBJECTS)
	make -C ./libft/ mode=$(mode)
	$(CC) $(CFLAGS) $(OBJECTS) -L. ./libft/libft.a -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	rm -f $(OBJECTS)
.PHONY:fclean
fclean: clean
	rm -f $(NAME) $(OBJECTS)
.PHONY:re
re: fclean all

.PHONY:information
information:
	@printf "Build mode "$(mode)" selected\n"
