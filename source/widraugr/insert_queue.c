/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:52:46 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/01 13:54:04 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

int		ft_lstlen(t_nlst *nlst)
{
	int		i;
	t_nlst	*iter;

	i = 0;
	iter = nlst;
	while (iter)
	{
		i++;
		iter = iter->next;
	}
	return (i);
}

/*
** Init queue.
*/

t_queue	*init_queue(void)
{
	t_queue *queue;

	if (!(queue = (t_queue *)malloc(sizeof(t_queue))))
		sys_err("Error malloc\n");
	queue->first = NULL;
	queue->end = NULL;
	queue->sum = 0;
	return (queue);
}

/*
** Create edges.
*/

void	create_edges(t_node *node, char *line)
{
	size_t	len;
	char	*fir_name;
	t_node	*cur_node;

	len = ft_strcl(line, '-');
	fir_name = ft_strnew(len + 1);
	fir_name = ft_strncpy(fir_name, line, len);
	cur_node = search_node(node, fir_name);
	add_new_edges(&cur_node->edg, (line + len + 1));
	cur_node = search_node(node, line + len + 1);
	add_new_edges(&cur_node->edg, fir_name);
	ft_strdel(&fir_name);
}

/*
** Insert new list into front queue.
*/

void	insert_front(t_queue *queue, char *name)
{
	t_nlst	*newl;
	t_nlst	*iter;

	newl = NULL;
	iter = queue->first;
	if (queue->first == NULL && queue->first == NULL)
	{
		queue->first = creat_new_lst(name);
		queue->end = queue->first;
	}
	else
	{
		newl = creat_new_lst(name);
		newl->next = iter;
		queue->first = newl;
	}
}

/*
** Insert queue.
*/

void	insert_queue(t_queue *que, t_ant *ant)
{
	t_ways	*ways;
	t_nlst	*nlst;

	ways = ant->ways;
	while (ways->next)
		ways = ways->next;
	while (ways != NULL)
	{
		nlst = ways->way;
		if (nlst == NULL)
		{
			ways = ways->prev;
			continue ;
		}
		insert_front(que, nlst->name_edg);
		ways->way = ways->way->next;
		free(nlst);
		ways = ways->prev;
	}
}
