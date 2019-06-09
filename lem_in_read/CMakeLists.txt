cmake_minimum_required(VERSION 3.14)
project(lem_in C)

set(CMAKE_C_STANDARD 99)

include_directories("libft/")

add_executable(lem_in main.c lem_in.h
        get_next_line.c
        ft_error.c

        libft/ft_putnbr.c
        libft/ft_atoi.c
        libft/ft_strisdigit.c
        libft/ft_strsub.c
        libft/ft_strdup.c
        libft/ft_strdel.c
        libft/ft_strnew
        libft/ft_strjoin
        libft/ft_strchr.c
        libft/ft_putchar.c
        libft/ft_putendl.c
        libft/ft_strlen.c
        libft/ft_isdigit.c
        libft/ft_memset.c
        libft/ft_putstr.c
        libft/ft_check_int.c
        for_testing.c
        libft/ft_size_mas_strings.c
        libft/ft_strsplit.c
        libft/ft_strequ.c
        libft/ft_free_mas_strings.c

        ft_free_lem.c
        read_lem.c read_room.c read_link.c read_start_and_end.c
        libft/ft_str_split_one_char.c neighbours.c vertex_init.c stack.c depth_first_search.c)