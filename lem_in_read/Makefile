NAME = lem-in

LIB_FILE = libft.a

CFILES = main.c ft_error.c ft_free_lem.c read_start_and_end.c read_room.c read_link.c\
		get_next_line.c read_lem.c neighbours.c vertex_init.c stack.c\
		depth_first_search.c\
		for_testing.c

OFILES = main.o ft_error.o ft_free_lem.o read_start_and_end.o read_room.o read_link.o\
         get_next_line.o read_lem.o neighbours.o vertex_init.o stack.o\
         depth_first_search.o\
         for_testing.o

FLAGS = -Wextra -Werror -Wall -g

HFILES = -I ./libft

all: $(NAME)

$(NAME):
	make -C ./libft
	gcc $(FLAGS) $(HFILES) -c $(CFILES)
	gcc $(FLAGS) $(OFILES) -L./libft -lft -o $(NAME)

clean:
	make clean -C ./libft
	/bin/rm -f $(OFILES)

fclean: clean
	make fclean -C ./libft
	/bin/rm -f $(NAME)

re: fclean all
	make re -C ./libft

