/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:06:17 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/02 13:57:29 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

void	delete_node(t_node *node)
{
	t_node *cur_node;

	cur_node = node;
	while (node != NULL)
	{
		cur_node = node;
		delete_all_list(&(cur_node->edg));
		free(cur_node);
		node = node->next;
	}
}

void	delete_node_ant(t_node *node, t_ant *ant)
{
	delete_node(node);
	delete_ways(ant);
	delete_all_list(&ant->que->first);
	free(ant->que);
	free(ant);
	ant = NULL;
}

void	create_print_list(t_nlst *pant, t_ant *ant, int i)
{
	t_nlst	**pant_it;
	t_nlst	*iter;
	int		j;
	int		b;

	b = 0;
	pant->next = NULL;
	pant_it = &pant;
	missing_row(ant, pant_it, i, &b);
	if (ant->ways->iter == NULL)
		ant->ways->iter = ant->ways;
	iter = ant->ways->iter->way;
	while (iter != NULL)
	{
		add_new_edges(pant_it, iter->name_edg);
		iter = iter->next;
		b++;
	}
	j = ant->cur_steps - b + 1;
	while (--j > 0)
		add_new_edges(pant_it, "\0");
	ant->ways->iter = ant->ways->iter->next;
}

/*
** Admission room of name start.
*/

void	admission_name_start_recount(t_ant *ant)
{
	t_ways	*ways;
	t_nlst	*nlst;

	ways = ant->ways;
	delete_dublicate(ant);
	re_count_steps(ant);
	while (ways != NULL)
	{
		nlst = ways->way;
		if (nlst == NULL)
			continue ;
		ways->way = ways->way->next;
		free(nlst);
		ways = ways->next;
	}
}

/*
** Print solution.
*/

void	solution(t_node *node, t_ant *ant)
{
	int				i;
	int				j;
	static t_nlst	*temp;
	t_nlst			*del;
	t_nlst			pant[ant->count_ant];

	i = -1;
	admission_name_start_recount(ant);
	while (++i < ant->count_ant)
		create_print_list(&pant[i], ant, i);
	j = -1;
	ft_putstr("\n");
	while (++j < ant->cur_steps)
	{
		i = -1;
		while (++i < ant->count_ant)
		{
			temp = &pant[i];
			del = pant[i].next;
			pant[i] = *pant[i].next;
			solution_print(temp->name_edg[0], i + 1, temp->name_edg, &del);
		}
		ft_putchar('\n');
	}
	ft_printf("ant->count_ant  %d\n", ant->count_ant);
	ft_printf("ant->cur_steps  %d\n", ant->cur_steps);
	finish(node, ant);
}
