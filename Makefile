#!/usr/bin/make -f

LIBS = -L./libft -lft

SRC = src

NAME = ft_ls.out

#HEADERS = ft_ls.h

OBJECTS = $(SRC)/lst_met_make.o $(SRC)/arr_foreach.o $(SRC)/lst_del_dir.o $(SRC)/lst_del_met.o $(SRC)/lst_to_arr.o $(SRC)/sort_arr_lst.o $(SRC)/lst_node_process.o $(SRC)/ft_joinpath.o $(SRC)/lst_dir_make.o $(SRC)/ft_ls.o

CFLAGS = -Wall -Werror -Wextra -g -fno-omit-frame-pointer -fsanitize=address

all: information $(NAME)

$(NAME): $(OBJECTS)#$(HEADERS)
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
