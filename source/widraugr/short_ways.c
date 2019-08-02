/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_ways.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:04:16 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/01 14:04:19 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

int		isempty_queue(t_queue *que)
{
	return (que->first == NULL ? 1 : 0);
}

/*
** Create new list for edges and(or) queue.
*/

t_nlst	*creat_new_lst(char *name)
{
	t_nlst *new;
	size_t len;

	len = ft_strlen(name);
	if (!(new = (t_nlst *)malloc(sizeof(t_nlst))))
		sys_err("Error malloc.\n");
	ft_strncpy(new->name_edg, name, len);
	new->name_edg[len] = '\0';
	new->next = NULL;
	return (new);
}

/*
** Cheack of a short path.
** Проверяет есть ли еще один котороткий путь.
*/

int		cheack_short_path(t_node *node, t_ant *ant)
{
	t_node	*cur_node;
	t_nlst	*iter;
	int		s_lvl;

	cur_node = search_node(node, ant->name_end);
	iter = cur_node->edg;
	s_lvl = cur_node->level;
	while (iter != NULL)
	{
		cur_node = search_node(node, iter->name_edg);
		if (cur_node->dfs_mark == 0)
			return (1);
		iter = iter->next;
	}
	return (0);
}

int		first_short_way(t_node *node, t_ant *ant)
{
	if (!(ant->ways = create_short_way(node, ant)))
	{
		ant->count_ways++;
		ant->pre_steps = 1;
		ant->bl = 0;
		return (1);
	}
	return (0);
}

/*
** Add new list of way.
** Пока есть короткие пути, создаем новый лист с именами пути.
** После создания коротких путей добавляем в конец имя конца пути.
** Особеность реализации.
*/

int		short_ways(t_node *node, t_ant *ant)
{
	t_ways *iter;

	while (cheack_short_path(node, ant))
	{
		if (ant->ways == NULL)
		{
			if (first_short_way(node, ant))
				return (1);
			ant->count_ways++;
			continue ;
		}
		if (!(iter = create_way(node, ant)))
			return (0);
		ant->count_ways++;
		iter->next = ant->ways->next;
		ant->ways->next = iter;
		iter->prev = ant->ways;
		if (iter->next != NULL)
			iter->next->prev = iter;
	}
	return (0);
}
