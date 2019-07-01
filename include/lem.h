/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 10:30:49 by widraugr          #+#    #+#             */
/*   Updated: 2019/06/14 15:31:52 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_H
# define LEM_H

#include "../libft/ft_printf.h"
#include "../libft/libft.h"
#include "../libft/get_next_line.h"
//#include "lem_read/lem_in.h"

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
	struct s_ways	*prev;
	struct s_ways	*iter;
}					t_ways;

typedef struct		s_ant
{
	t_queue			*que;
	t_ways			*ways;
	char			name_start[NSIZE];
	char			name_end[NSIZE];
	char			nmax_weid[NSIZE];
	char			fir_wei[NSIZE];
	char			sec_wei[NSIZE];
	char			pre_firn[NSIZE];
	char			pre_secn[NSIZE];
	int				num_fn;
	int				num_sn;
	int				cur_steps;
	int				pre_steps;
	int				lvl;
	int				bl;
	int				count_ant;
	int				max_count_way;
	int				all_steps;
	int				count_ways;
	int				s_lvl;
	int				a;
}					t_ant;

typedef struct	s_pant
{
	char			name_room[NSIZE];

}					t_pant;

/*
** File working.c
*/
void	working(t_node *node, t_ant *ant);
int		cheack_step(t_node *node, t_ant *ant);
void	weight_node(t_node *node);
t_node	*search_node(t_node *node, char *name);
void	zeroing_bfs(t_node *node);
/*
** File bfs.c
*/
void	breadth_first_search(t_node *node, t_ant *ant);
void	insert(t_queue *queue, char *name);
char	*remove_first(t_queue *que, int count_ways);
void	delete_all_list(t_nlst **lst);
void	iter_to_edg_lst(t_node *node, t_ant *ant, t_node *cur_node);
/*
** File short_ways.c
*/
int		cheack_short_path(t_node *node, t_ant *ant);
int		first_short_way(t_node *node, t_ant *ant);
int		short_ways(t_node *node, t_ant *ant);
int		isempty_queue(t_queue *que);
t_nlst	*creat_new_lst(char *name);
/*
** File remove_edge.c
*/
int		delete_name_list(char *name, t_nlst **nlst, int *num);
int		calc_steps(t_ant *ant);
void	remove_edge(t_node *node, t_ant *ant);
void	define_fir_sec_wei(t_node *node, t_ant *ant);
void	add_to_num_edges(t_nlst **edg, char *name, int num);
/*
** File cut_ways.c
*/
int		finish_cut(t_ant *ant, t_ways *pre, int *now_step, int *pre_step);
void	save_date(t_ant *ant, int now_step);
void	delete_ways(t_ant *ant);
void	sys_err(char *err);
void	cut_ways(t_ant *ant);
/*
** File create_short_way.c
*/
void	node_is_visited(t_nlst *lst, t_ways *iter, t_node *cur_node);
int		part(t_node *node, t_nlst *lst, t_ways *iter, t_ant *ant);
t_node	*help(t_node *node, t_ways *iter, t_ant *ant);
t_ways	*create_new_way(void);
t_ways	*create_short_way(t_node *node, t_ant *ant);
/*
** File add_new_nlst.c
*/
void	add_new_nlst(t_nlst **way, char *name);
void	work_dfs(t_ways *iter, t_nlst **lst, t_node *cur_node);
void	delete_list(t_nlst **way);
void	delete_tail_ways(t_ways *ways);
void	calc_all_ways(t_ant *ant);
/*
** File sort_ways.c
*/
void	swap_nlst_ptr(t_nlst **one, t_nlst **two);
void	swap_len_way(int *one, int *two);
t_node	*search_cur_node(t_node *node, t_ant *ant, t_nlst **lst, t_ways *iter);
t_ways	*create_way(t_node *node, t_ant *ant);
void	sort_ways(t_ant *ant);
/*
** File part_way.c
*/
int		part_way(t_node *node, t_nlst **lst, t_ways *iter, t_ant *ant);
int		len_ways(t_ways *ways);
int		cheack_main_way(t_node *temp_node, t_nlst *way, int level);
int		check_name_short_way(char *name, t_ways *ways);
void	cheack_remove(t_ant *ant, t_queue *que, int i);
/*
** File solution.c
*/
void	solution(t_node *node, t_ant *ant);
void	delete_node_ant(t_node *node, t_ant *ant);
void	delete_node(t_node *node);
void	create_print_list(t_nlst *pant, t_ant *ant, int i);
void	admission_name_start_recount(t_ant *ant);
/*
** File add_new_edges.c
*/
void	add_new_edges(t_nlst **nlst, char *name);
void	missing_row(t_ant *ant, t_nlst **pant_it, int i, int *b);
void	delete_dublicate(t_ant *ant);
void	re_count_steps(t_ant *ant);
void	remove_last(t_queue *que, int count_ways);
/*
** File insert_queue.c
*/
int		ft_lstlen(t_nlst *nlst);
t_queue	*init_queue(void);
void	create_edges(t_node *node, char *line);
void	insert_front(t_queue *queue, char *name);
void	insert_queue(t_queue *que, t_ant *ant);
/*
** File init_ant.c
*/
void	infill_node(t_node *node, char *line);
t_node	*new_node(char *line);
void	copy_name(char *name, char *line);
t_node	*add_node(t_node *node, char **line);
t_ant	*init_ant(void);
/*
** File init_ant.c
*/
void	print_edges(t_nlst *edg);
void	print_node(t_node *node);
void	print_ways(t_ant *ant);


/*
void	depth_first_search(t_node *node, t_ant *ant);
t_ways	*create_way(t_node *node, t_ant *ant);
t_ways	*create_short_way(t_node *node, t_ant *ant);
void	cheack_short_way(t_ant *ant);
void	solution(t_node *node, t_ant *ant);
void	print_ways(t_ant *ant);
void	delete_ways(t_ant *ant);
void	print_ways(t_ant *ant);
void	calc_all_ways(t_ant *ant);
void	delete_tail_ways(t_ways *ways);
*/

#endif
