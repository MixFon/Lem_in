/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 10:30:49 by widraugr          #+#    #+#             */
/*   Updated: 2019/05/16 15:29:22 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
/*
** Structure node.
** level    - the level at which the node is located in graf. (BFS)
** mark_bfs - a token that marks the visited node. (BFS) (val 0, 1)
** dfs_mark - a token that marks the visited node. (DFS) (val 0, 1, 2)
*/
typedef struct		s_node
{
	char			name[NSIZE];
	int				coor_x;
	int				coor_y;
	short int		mark_bfs;
	short int		dfs_mark;
	int				level;
	struct s_node	*next;
	t_nlst			*edg;
}					t_node;
/*
** Structure queue.
** First is left element of list. End is right element of list.
** sum summa ant in queue.
*/
typedef struct		s_queue
{
	t_nlst			*first;
	t_nlst			*end;
	int				sum;
}					t_queue;
/*
** Structure stack.
** First is left element of list.
*/
typedef struct		s_stack
{
	t_nlst			*first;
}					t_stack;

typedef struct		s_ant
{
	t_queue			*que;
	t_stack			*stack;
	t_nlst			*sol;;
	char			name_start[NSIZE];
	char			name_end[NSIZE];
	int				short_cut;
	int				count_ant;
}					t_ant;
