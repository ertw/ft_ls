#include "ft_ls.h"
#define IS_TAIL !cursor->next
#define IS_HEAD cursor == head

/*
 * read in a directory or file from the read stack
 * if it's a file, print it
 * if it's a dir, print every file in it
 * 	if any file is a directory, add it to the read stack
*/
