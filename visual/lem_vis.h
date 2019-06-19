#ifndef LEM_VIS_H
# define LEM_VIS_H

# include "../libft/ft_printf.h"
# include "../libft/get_next_line.h"
# include "minilibx/mlx.h"

# define NSIZE	20
# define WIDTH	1280
# define HEITH	720

# define C_ROOM	"2056B6"

# define IMGPATH	"/Users/mixfon/MyFiles/ConsoleFiles/Lem_in2/visual/image/back3.xpm"
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

typedef struct		s_vis
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_back;
	void			*img_room;
	t_node			*node;
	t_link			*link;
	t_link			*step;
	int				heith;
	int				width;
	int				count_ant;
	char			**map_room;
	int				size_room;
}					t_vis;

#endif
