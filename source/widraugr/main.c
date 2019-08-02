/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 10:18:25 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/02 11:31:27 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "lem.h"

/*
** Copy node .
*/

void	copy_node(t_node ***node, t_room *rooms)
{
	t_room	*rooms_it;

	rooms_it = rooms;
	while (rooms_it != NULL)
	{
		**node = add_node(**node, &rooms_it->name_room);
		rooms_it = rooms_it->next;
	}
}

/*
** Copy link.
*/

void	copy_link(t_node **node, t_link *links)
{
	t_link	*links_it;
	t_node	*cur_node;

	links_it = links;
	while (links_it != NULL)
	{
		cur_node = search_node(*node, links_it->room1);
		add_new_edges(&cur_node->edg, links_it->room2);
		cur_node = search_node(*node, links_it->room2);
		add_new_edges(&cur_node->edg, links_it->room1);
		links_it = links_it->next;
	}
}

/*
** Copy node and link to ant
*/

void	copy_node_link(t_node **node, t_ant *ant, t_lem *lem)
{
	copy_node(&node, lem->rooms);
	copy_link(node, lem->links);
	ft_strcpy(ant->name_start, lem->start.name_room);
	ft_strcpy(ant->name_end, lem->end.name_room);
	ant->count_ant = lem->count_ants;
}

void	read_map(void)
{
	t_lem	lem;
	t_node	*node;
	t_ant	*ant;

	node = NULL;
	ant = init_ant();
	lem = ft_get_lem();
	ft_check_graph(&lem);
	copy_node_link(&node, ant, &lem);
	ft_free_lem(&lem);
	working(node, ant);
	weight_node(node);
	breadth_first_search(node, ant);
	short_ways(node, ant);
	sort_ways(ant);
	cut_ways(ant);
	solution(node, ant);
}

int		main(void)
{
	read_map();
	return (0);
}
