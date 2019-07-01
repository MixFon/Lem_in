
#include "../../include/lem.h"


/*
** Insert bfs to zero.
*/

void	zeroing_bfs(t_node *node)
{
	t_node *cur_node;

	cur_node = node;
	while (cur_node != NULL)
	{
		cur_node->mark_bfs = 0;
		cur_node->dfs_mark = 0;
		cur_node->level = 0;
		cur_node->weight = 0;
		cur_node = cur_node->next;
	}
}

/*
** Serch for a node by name.
*/

t_node	*search_node(t_node *node, char *name)
{
	while (node)
	{
		if (ft_strcmp(node->name, name) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

/*
** Defines the weight of the node.
** Поправить, сделать при создании узла.
*/

void	weight_node(t_node *node)
{
	t_node	*iter;

	iter = node;
	while (iter != NULL)
	{
		iter->weight = 1;
		iter = iter->next;
	}
}

/*
** Проверяет увеличение количества шагов.
*/

int		cheack_step(t_node *node, t_ant *ant)
{
	t_node *cur_node;

	if (ant->cur_steps == 0)
		return (1);
	if (ant->cur_steps > ant->pre_steps && ant->pre_steps != 0)
	{	
		if (ant->bl == 0)
		{
			cur_node = search_node(node, ant->pre_firn);
			add_to_num_edges(&cur_node->edg, ant->pre_secn, ant->num_sn);
			cur_node = search_node(node, ant->pre_secn);
			add_to_num_edges(&cur_node->edg, ant->pre_firn, ant->num_fn);
		}
		return (0);
	}
	else
		return (1);
	return (1);
}

void	working(t_node *node, t_ant *ant)
{
	while(cheack_step(node, ant))
	{
		weight_node(node);
		breadth_first_search(node, ant);
		if (short_ways(node, ant))
		{
			zeroing_bfs(node);
			delete_ways(ant);
			continue ;
		}
		if(calc_steps(ant))
		{
			zeroing_bfs(node);
			delete_ways(ant);
			continue;
		}
		define_fir_sec_wei(node, ant);
		//print_node(node);
		remove_edge(node, ant);
		zeroing_bfs(node);
		delete_ways(ant);
	}
}
