/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 10:18:25 by widraugr          #+#    #+#             */
/*   Updated: 2019/06/29 21:43:37 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lem_in.h"
#include "../../include/lem.h"

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
	//print_node(node);
	short_ways(node, ant);
	sort_ways(ant);
	cut_ways(ant);
	//print_ways(ant);
	solution(node, ant);
}

int		main(void)
{
	read_map();
	return (0);
}

/*
void	special_case(t_node *node, t_ant *ant)
{
	t_ways *ways;

	ways = ant->ways;
	if (ways->len_way > ant->count_ant)
	{
		delete_tail_ways(ant->ways->next);
		ant->ways->next = NULL;
		ant->count_ways = 1;
		ant->max_count_way = ft_lstlen(ant->ways->way) - 1;
		cut_ways(ant);
		//print_ways(ant);
		solution(node, ant);
	}
}
*/

/*
void	unwanted_edg(t_node *node, t_ant *ant)
{
	t_node	*cur_node;
	t_nlst	*edg;
	t_node	*temp_node;

	if (ft_strcmp(ant->fir_wei, ant->name_start) == 0)
	{
		cur_node = search_node(node, ant->sec_wei);
		edg = cur_node->edg;
		while (edg != NULL)
		{
			temp_node = search_node(node, edg->name_edg);	
			if (cheack_main_way(temp_node, ant->ways->way, cur_node->level - 1))
				ft_strcpy(ant->fir_wei, temp_node->name);
			edg = edg->next;
		}
		ft_printf("asd fir_wie {%s}\n", ant->fir_wei);
	}
	else	if (ft_strcmp(ant->sec_wei, ant->name_start) == 0)
	{
		cur_node = search_node(node, ant->fir_wei);
		edg = cur_node->edg;
		while (edg != NULL)
		{
			temp_node = search_node(node, edg->name_edg);	
			if (cheack_main_way(temp_node, ant->ways->way, cur_node->level - 1))
				ft_strcpy(ant->sec_wei, temp_node->name);
			edg = edg->next;
		}
		ft_printf("asd sec_wie {%s}\n", ant->sec_wei);
	}

}
*/
