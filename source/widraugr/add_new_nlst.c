/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_nlst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:43:35 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/01 13:43:37 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

void	calc_all_ways(t_ant *ant)
{
	t_ways *ways;

	ways = ant->ways;
	ant->all_steps = 0;
	while (ways)
	{
		if (ant->max_count_way < ways->len_way)
			ant->max_count_way = ways->len_way;
		ant->all_steps += ways->len_way;
		ways = ways->next;
	}
}

void	delete_tail_ways(t_ways *ways)
{
	t_ways	*pre;

	pre = ways;
	while (ways != NULL)
	{
		pre = ways;
		ways = ways->next;
		delete_all_list(&pre->way);
		free(pre);
	}
}

/*
** Delete one list in way.
*/

void	delete_list(t_nlst **way)
{
	t_nlst	*iter;

	iter = *way;
	if (!iter)
		return ;
	*way = (*way)->next;
	iter->next = NULL;
	free(iter);
}

void	work_dfs(t_ways *iter, t_nlst **lst, t_node *cur_node)
{
	add_new_nlst(&iter->way, (*lst)->name_edg);
	iter->len_way++;
	cur_node->dfs_mark = 1;
}

void	add_new_nlst(t_nlst **way, char *name)
{
	t_nlst	*iter;

	iter = creat_new_lst(name);
	iter->next = *way;
	*way = iter;
}
