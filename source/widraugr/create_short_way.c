
#include "../../include/lem.h"

void	node_is_visited(t_nlst *lst, t_ways *iter, t_node *cur_node)
{
	if (lst == NULL)
	{
		iter->len_way--;
		cur_node->dfs_mark = 1;
		delete_list(&iter->way);
	}
}

int		part(t_node *node, t_nlst *lst, t_ways *iter, t_ant *ant)
{
	char	*name;
	t_node	*cur_node;

	name = lst->name_edg;
	cur_node = search_node(node, name);
	//ft_printf("edges {%s}\n", cur_node->name);
	if (!ft_strcmp(name, ant->name_start))
	{
		add_new_nlst(&iter->way, name);
		cur_node->dfs_mark = 1;
		return (1);
	}
	else if (cur_node->level == ant->s_lvl - 1 && cur_node->dfs_mark == 0 &&
			cur_node->level != 0)
	{
		work_dfs(iter, &lst, cur_node);
		return (2);
	}
	return (0);
}

t_node	*help(t_node *node, t_ways *iter, t_ant *ant)
{
	t_node *cur_node;

	cur_node = search_node(node, iter->way->name_edg);
	cur_node->dfs_mark = 1;
	ant->s_lvl = cur_node->level;
	return (cur_node);
}

/*
** Create new way for short path.
** Create list short path.
*/

t_ways	*create_new_way(void)
{
	t_ways *way;

	if(!(way = (t_ways *)malloc(sizeof(t_ways))))
		sys_err("Error malloc\n");
	way->way = NULL;;
	way->len_way = 1;
	way->next = NULL;
	way->prev = NULL;
	way->iter = NULL;
	return (way);
}

/*
** Create list only short way.
*/

t_ways	*create_short_way(t_node *node, t_ant *ant)
{
	t_node	*cur_node;
	t_ways	*iter;
	int		bl;
	t_nlst	*lst;

	iter = create_new_way();
	iter->way = creat_new_lst(ant->name_end);
	while (iter->way != NULL)
	{
		cur_node = help(node, iter, ant);
		lst = cur_node->edg;
		while (lst != NULL)
		{
			bl = part(node, lst, iter, ant);
			if (bl == 1)
				return (iter);
			else	if (bl == 2)
				break ;
			lst = lst->next;
		}
		node_is_visited(lst, iter, cur_node);
	}
	free(iter);
	return (NULL);
}
