/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:07:37 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/01 14:07:39 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

void	swap_nlst_ptr(t_nlst **one, t_nlst **two)
{
	t_nlst	*temp;

	temp = *one;
	*one = *two;
	*two = temp;
}

void	swap_len_way(int *one, int *two)
{
	int	temp;

	temp = *one;
	*one = *two;
	*two = temp;
}

t_node	*search_cur_node(t_node *node, t_ant *ant, t_nlst **lst, t_ways *iter)
{
	t_node	*cur_node;

	cur_node = search_node(node, iter->way->name_edg);
	cur_node->dfs_mark = 1;
	ant->s_lvl = cur_node->level;
	*lst = cur_node->edg;
	ant->a++;
	return (cur_node);
}

/*
** Depth-first search.
** Create list short path.
*/

t_ways	*create_way(t_node *node, t_ant *ant)
{
	t_node	*cur_node;
	t_nlst	*lst;
	t_ways	*iter;

	iter = create_new_way();
	iter->way = creat_new_lst(ant->name_end);
	ant->a = 0;
	while (iter->way != NULL)
	{
		cur_node = search_cur_node(node, ant, &lst, iter);
		while (lst)
		{
			ant->a = part_way(node, &lst, iter, ant);
			if (ant->a == 1)
				return (iter);
			else	if (ant->a == 2)
				break ;
			else	if (ant->a == 3)
				continue ;
			lst = lst->next;
		}
		node_is_visited(lst, iter, cur_node);
	}
	free(iter);
	return (NULL);
}

void	sort_ways(t_ant *ant)
{
	t_ways	*ways;
	t_ways	*pre;
	int		bl;

	bl = 1;
	while (bl)
	{
		ways = ant->ways;
		bl = 0;
		while (ways->next != NULL)
		{
			pre = ways;
			ways = ways->next;
			if (ways == NULL)
				break ;
			if (pre->len_way > ways->len_way)
			{
				swap_nlst_ptr(&pre->way, &ways->way);
				swap_len_way(&pre->len_way, &ways->len_way);
				bl = 1;
			}
		}
	}
}
