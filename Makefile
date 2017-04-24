#!/usr/bin/make -f

LIBS = -L./libft -lft

NAME = recurse.out

HEADERS = ft_ls.h

OBJECTS = recurse.o

CFLAGS = -Wall -Werror -Wextra -g -fno-omit-frame-pointer -fsanitize=address

all: information $(NAME)

$(NAME): $(OBJECTS) $(HEADERS)
	make -C ./libft/
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $@
clean:
	rm -f $(OBJECTS)
fclean: clean
	rm -f $(NAME) $(OBJECTS)
re: fclean all

information:
	@printf "Building...\n"
.PHONY:information re fclean clean all
