/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_vis.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 17:34:41 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/02 17:45:32 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_VIS_H
# define LEM_VIS_H

# include "../../libft/ft_printf.h"
# include "../../libft/get_next_line.h"
# include "../minilibx_macos/mlx.h"

# define NSIZE	20
# define WIDTH	1280
# define HEITH	720

# define ABS(N) ((N<0)?(-N):(N))

# define C_ROOM	"2056B6"
# define C_VISIT "BF2956"
# define C_SCORE "540f0c"
# define C_START "00008B"
# define C_END	"00008B"

# define SIZE_ROOM	50
# define CENTR	SIZE_ROOM / 2

# define IMGPATH "./image/back3.xpm"
# define IMGERR	"./image/error.xpm"

typedef struct		s_link
{
	char			*name;
	struct s_link	*next;
}					t_link;

typedef struct		s_node
{
	char			name[NSIZE];
	int				coor_x;
	int				coor_y;
	struct s_node	*next;
}					t_node;

typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct		s_coor
{
	int				x;
	int				y;
}					t_coor;

typedef struct		s_vis
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_back;
	void			*img_room;
	void			*img_score;
	void			*img_start;
	void			*img_end;
	void			*img_visit;
	void			*img_error;
	t_node			*node;
	t_link			*link;
	t_link			*step;
	int				heith;
	int				width;
	char			nstart[NSIZE];
	char			nend[NSIZE];
	int				count_ant;
	char			**map_room;
	char			**map_score;
	char			**map_visit;
	char			**map_start;
	char			**map_end;
	int				size_room;
}					t_vis;
/*
** File pint_score.c
*/
void				rectengle_visit(t_vis *vis, char **arr);
void				next_step(t_link **step);
void				print_rooms(t_vis *vis);
int					print_steps(t_vis *vis);
void				print_score(t_vis *vis);
/*
** File delete_arr.c
*/
char				*return_name_node(char *str);
t_node				*search_node(t_node *node, char *name);
void				print_arr(char **arr);
void				delete_arr(char **arr);
void				print_visit(t_vis *vis, char *str_num, char *name_room);
/*
** File creat_new_link.c
*/
t_coor				*remove_coor(t_vis *vis, char *temp);
char				*first_name(t_link *link);
void				put_edges(t_vis *vis);
void				sys_err(char *err);
t_link				*creat_new_link(char *name);
/*
** File second_name.c
*/
void				swap(int *a, int *b);
void				ft_draw_line_source(t_point *delta, t_point *sign,
		t_point point1, t_point point2);
void				ft_draw_line(void *mlx_ptr, void *win_ptr,
		t_point point1, t_point point2);
void				put_line(t_vis *vis, t_coor *start, t_coor *end);
char				*second_name(t_link *link);
/*
** File delete_link.c
*/
int					check_link_node(char *line);
void				print_link(t_link *link);
int					exit_key(int key);
void				print_error(t_vis *vis);
void				delete_link(t_link **link);
/*
** File init_back.c
*/
t_node				*add_node(t_node *node, char **line);
char				**crea_color_map(int heith, int width, const char *color);
t_vis				*create_vis(void);
void				init_val(t_vis *vis);
int					init_back(t_vis *vis);
/*
** File new_node.c
*/
void				print_node(t_node *node);
void				delete_node(t_node *node);
int					check_name_node(char *line);
void				infill_node(t_node *node, char *line);
t_node				*new_node(char *line);
/*
** File pint_score.c
*/
void				add_list_link(t_link **link, char *name);
void				input_room(t_node *node, t_vis *vis, char **arr);
int					check_octotopr(t_vis *vis, char **line);
int					read_map(t_vis *vis);
int					main(void);
/*
** File pint_score.c
*/
void				delete_all_arr(t_vis *vis);

#endif
