#cc -g -fsanitize=address dirlist.c -L. ./libft/libft.a ; ./a.out
#cc -g dirlist.c -L. ./libft/libft.a ; ./a.out
cc -g -fsanitize=address recurse.c -L. ./libft/libft.a ; ./a.out
#cc -g recurse.c -L. ./libft/libft.a ; ./a.out
