/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:58:36 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/01 13:58:38 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

/*
** Print edges.
*/

void	print_edges(t_nlst *edg)
{
	while (edg)
	{
		ft_printf("Edges name = %s\n", edg->name_edg);
		edg = edg->next;
	}
}

/*
** Print list.
** For test.
*/

void	print_node(t_node *node)
{
	while (node)
	{
		ft_printf("name = %s,    level  = %d weight = %d dfs {%d}\n",
			node->name, node->level, node->weight, node->dfs_mark);
		print_edges(node->edg);
		node = node->next;
	}
}

void	print_ways(t_ant *ant)
{
	t_ways	*ways;
	int		i;

	i = 0;
	ways = ant->ways;
	while (ways)
	{
		ft_printf("\nPath %d:\nCout staps in way %d\n", ++i, ways->len_way);
		print_edges(ways->way);
		ways = ways->next;
	}
}
