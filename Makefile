# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/01 12:18:45 by eskeleto          #+#    #+#              #
#    Updated: 2019/08/02 12:22:54 by widraugr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC = ./source/eskeleto/depth_first_search.c ./source/eskeleto/ft_check_int.c ./source/eskeleto/ft_error.c \
      ./source/eskeleto/ft_free_lem.c ./source/eskeleto/ft_free_mas_strings.c \
	  ./source/eskeleto/ft_isdigit.c ./source/eskeleto/ft_size_mas_strings.c \
	  ./source/eskeleto/ft_str_split_one_char.c ./source/eskeleto/ft_strisdigit.c \
	  ./source/eskeleto/neighbours.c ./source/eskeleto/read_lem.c ./source/eskeleto/read_link.c \
	  ./source/eskeleto/read_room.c ./source/eskeleto/read_start_and_end.c ./source/eskeleto/stack.c \
      ./source/eskeleto/vertex_init.c ./source/eskeleto/work.c \
      ./source/widraugr/add_new_edges.c ./source/widraugr/add_new_nlst.c ./source/widraugr/bfs.c \
      ./source/widraugr/create_short_way.c ./source/widraugr/cut_ways.c ./source/widraugr/init_ant.c \
      ./source/widraugr/insert_queue.c ./source/widraugr/main.c ./source/widraugr/part_way.c ./source/widraugr/print.c \
      ./source/widraugr/remove_edge.c ./source/widraugr/short_ways.c ./source/widraugr/solution.c \
      ./source/widraugr/sort_ways.c ./source/widraugr/working.c ./source/widraugr/finish.c

OBJ = depth_first_search.o ft_check_int.o ft_error.o \
      ft_free_lem.o ft_free_mas_strings.o \
      ft_isdigit.o ft_size_mas_strings.o \
      ft_str_split_one_char.o ft_strisdigit.o \
      neighbours.o read_lem.o read_link.o \
      read_room.o read_start_and_end.o stack.o \
      vertex_init.o work.o \
      add_new_edges.o add_new_nlst.o bfs.o \
      create_short_way.o cut_ways.o init_ant.o \
      insert_queue.o main.o part_way.o print.o \
      remove_edge.o short_ways.o solution.o \
      sort_ways.o working.o finish.o

FLAGS = -Wextra -Werror -Wall -g

HFILES = -I ./libft -I ./include

all: $(NAME)

$(NAME):
	make -C ./libft
	gcc $(FLAGS) $(HFILES) -c $(SRC)
	gcc $(FLAGS) $(OBJ) -L ./libft -lftprintf -o $(NAME)

clean:
	make clean -C ./libft
	/bin/rm -f $(OBJ)

fclean: clean
	make fclean -C ./libft
	/bin/rm -f $(NAME)
	
re: fclean all
	make re -C ./libft
