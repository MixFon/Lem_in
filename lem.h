#include "libft/ft_printf.h"
#include "libft/libft.h"
#include "libft/get_next_line.h"

/*
** Size names nodes.
*/
# define NSIZE 10
/*
** List of names for edges and queue.
*/
typedef struct		s_nlst
{
	char			name_edg[NSIZE];
	struct s_nlst	*next;
}					t_nlst;

typedef struct		s_node
{
	char			name[NSIZE];
	int				coor_x;
	int				coor_y;
	short int		bl;
	struct s_node	*next;
	t_nlst			*edg;
}					t_node;
/*
** Structure queue.
** First is left element of list. End is right element of list.
*/
typedef struct		s_queue
{
	t_nlst			*first;
	t_nlst			*end;
	char			name_start[NSIZE];
	char			name_end[NSIZE];
}					t_queue;
