/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:00:02 by eskeleto          #+#    #+#             */
/*   Updated: 2019/06/13 19:45:31 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include <unistd.h>
//# include "../libft/libft.h"
# include "../libft/ft_printf.h"

//# define BUFF_SIZE 32

typedef struct			s_room
{
	char				*name_room;
	int					coord_x;
	int					coord_y;
	struct s_room		*next;
}						t_room;

typedef struct			s_link
{
	char				*room1;
	char				*room2;
	struct s_link		*next;
}						t_link;

typedef struct			s_lem
{
	int					count_ants;
	t_room				start;
	t_room				end;
	t_room				*rooms;
	t_link				*links;
}						t_lem;

typedef struct			s_neighbour
{
	char				*name_neighbour;
	struct s_neighbour	*next;
}						t_neighbour;

typedef struct			s_vertex
{
	char				*name_vertex;
	int					mark_green;
	t_neighbour			*neighbour;
	struct s_vertex		*next;
}						t_vertex;

typedef struct			s_stack
{
	char				*name;
	struct s_stack		*next;
}						t_stack;

int						get_next_line(const int fd, char **line);
void					ft_error(void);
void					ft_free_lem(t_lem *lem);
void					ft_read_farm(t_lem *lem);
void					ft_init_lem(t_lem *lem);
t_lem					ft_get_lem(void);
void					ft_get_counts_ants(t_lem *lem);
int						ft_is_comment(char *str);
void					ft_push_room(t_room **head, char *name, int x, int y);
void					ft_read_room(char **str, t_lem *lem);
void					ft_push_link(t_link **head, char *room1, char *room2);
void					ft_read_link(char **str, t_lem *lem);
void					ft_read_start(char **str, t_lem *lem);
void					ft_read_end(char **str, t_lem *lem);
void					ft_start_or_end_not_comment(char **str, t_lem *lem,
							char **line);
void					ft_read_start_or_end(char **str, t_lem *lem);
void					ft_check_names_of_rooms(t_lem *lem,
							char *name, char **mas);
void					ft_check_coords_of_rooms(t_lem *lem,
							int x, int y, char **mas);
void					ft_free_vertex(t_vertex **vertex);
void					ft_push_neighbour(t_neighbour **head, char *name);
void					ft_add_neighbour(t_vertex **vertex, t_link *link);
void					ft_push_vertex(t_vertex **head, char *name);
int						ft_check_room_exist(t_lem lem, char *name);
t_vertex				*ft_init_graph(t_lem *lem);
int						ft_stack_is_empty(t_stack *head);
void					ft_push_stack(t_stack **head, char *name);
void					ft_pop_stack(t_stack **head);
t_vertex				*ft_find_vertex(t_vertex **vertex, char *name);
t_vertex				*ft_top_stack(t_vertex **vertex, t_stack *head);
t_vertex				*ft_mark_vertex(t_vertex **vertex, char *name);
t_vertex				*ft_choose_neighbour(t_vertex **marked,
							t_vertex **vertex);
void					ft_depth_first_search(t_lem *lem, t_vertex **vertex);
void					ft_free_mas_and_lem(t_lem *lem, char ***mas);
//for_testing
void					ft_print_lem(t_lem lem);
void					ft_print_vertex(t_vertex *vertex);
void					ft_print_stack(t_stack *stack);
void					ft_check_graph(t_lem *lem);
void					ft_check_linking(t_lem *lem, t_vertex **vertex);
char					**ft_str_split_one_char(char const *s, char c);
int						ft_isdigit(int c);
int						ft_strisdigit(char *str);
int						ft_size_mas_strings(char **mas);
int						ft_free_mas_strings(char **mas);
int						ft_check_int(char const *str);
t_lem					ft_get_lem(void);
void					ft_free_lem(t_lem *lem);

#endif
