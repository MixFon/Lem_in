
#include "../../include/lem.h"

void	cheack_remove(t_ant *ant, t_queue *que, int i)
{
	t_ways *ways;

	ways = ant->ways;
	while (ways != NULL)
	{
		if (i >= ant->cur_steps - ways->len_way)
			remove_last(que, 1);
		ways = ways->next;
	}
}

/*
** Check name in short list.
** Поиск имени в коротком пути, есть оно есть удаляем.
*/

int		check_name_short_way(char *name, t_ways *ways)
{
	t_ways	*iter;	
	t_nlst	*nlst;

	iter = ways;
	while (iter != NULL)
	{
		nlst = iter->way;			
		while (nlst != NULL)
		{
			if (!ft_strcmp(name, nlst->name_edg))
				return (1);
			nlst = nlst->next;
		}
		iter = iter->next;
	}
	return (0);
}	

int		cheack_main_way(t_node *temp_node, t_nlst *way, int level)
{
	while (way != NULL)
	{
		if (ft_strcmp(temp_node->name, way->name_edg)
				== 0 && temp_node->level == level)
			return (1);
		way = way->next;
	}
	return (0);
}

int		len_ways(t_ways *ways)
{
	int i;

	i = 0;
	while (ways != NULL)
	{
		i++;
		ways = ways->next;
	}
	return (i);
}

int		part_way(t_node *node, t_nlst **lst, t_ways *iter, t_ant *ant)
{
	t_node *cur_node;

	cur_node = search_node(node, (*lst)->name_edg);
	if (!ft_strcmp((*lst)->name_edg, ant->name_start))
	{
		if (ant->a == 1)
		{
			*lst = (*lst)->next;
			return (3);
		}
		add_new_nlst(&iter->way, (*lst)->name_edg);
		cur_node->dfs_mark = 1;
		return (1);
	}
	else if (cur_node->level == ant->s_lvl - 1 && cur_node->dfs_mark == 0)
	{
		work_dfs(iter, lst, cur_node);
		return (2);
	}
	else if (cur_node->dfs_mark == 0)
	{
		work_dfs(iter, lst, cur_node);
		return (2);
	}
	return (0);
}
