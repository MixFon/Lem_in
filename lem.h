/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 10:30:49 by widraugr          #+#    #+#             */
/*   Updated: 2019/05/31 18:10:29 by widraugr         ###   ########.fr       */
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
** sum_ant - count ant in room in this moment. 
*/
typedef struct		s_nlst
{
	char			name_edg[NSIZE];
	struct s_nlst	*next;
	int				sum_ant;
}					t_nlst;
/*
** Structure node.
** level    - the level at which the node is located in graf. (BFS)
** mark_bfs - a token that marks the visited node. (BFS) (val 0, 1)
** dfs_mark - a token that marks the visited node. (DFS) (val 0, 1)
*/
typedef struct		s_node
{
	char			name[NSIZE];
	int				coor_x;
	int				coor_y;
	short int		mark_bfs;
	short int		dfs_mark;
	int				level;
	int				weight;
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
** List ways.
*/
typedef struct		s_ways
{
	t_nlst			*way;
	int				len_way;
	struct s_ways	*next;
}					t_ways;

typedef struct		s_ant
{
	t_queue			*que;
	t_ways			*ways;
	char			name_start[NSIZE];
	char			name_end[NSIZE];
	char			nmax_weid[NSIZE];
	int				lvl;
	int				count_ant;
	int				count_ways;
}					t_ant;

void	depth_first_search(t_node *node, t_ant *ant);
t_ways	*create_short_way(t_node *node, t_ant *ant);
void	cheack_short_way(t_ant *ant);
void	solution(t_ant *ant);
/*
** Structure stack.
** First is left element of list.
*/
/*
typedef struct		s_stack
{
	t_nlst			*first;
}					t_stack;
*/
