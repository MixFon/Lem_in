# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: widraugr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/02 17:45:23 by widraugr          #+#    #+#              #
#    Updated: 2019/08/02 17:54:43 by widraugr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC = creat_new_link.c \
		delete_all_arr.c \
		delete_arr.c \
		delete_link.c \
		inint_back.c \
		main.c \
		new_node.c \
		print_score.c \
		second_name.c

SRC_PATH = source/

RC_COMPL = $(addprefix $(SRC_PATH), $(SRC))

OBJ = $(SRC:%.c=%.o)

FLAGS = -Wextra -Werror -Wall

HFILES = -I ../libft -I ./include

all: $(NAME)

$(NAME):
	make -C ./libft
	gcc $(FLAGS) $(HFILES) -c $(SRC)
	gcc $(FLAGS) $(OBJ) -L ../libft -lftprintf -o $(NAME)

clean:
	make clean -C ./libft
	/bin/rm -f $(OBJ)

fclean: clean
	make fclean -C ./libft
	/bin/rm -f $(NAME)
	
re: fclean all
	make re -C ./libft
