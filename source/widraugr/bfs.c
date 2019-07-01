
#include "../../include/lem.h"

/*
** Удаляет весь лист.
*/

void	delete_all_list(t_nlst **lst)
{
	t_nlst	*iter;
	t_nlst	*pre;

	iter = *lst;
	pre = iter;
	while (iter != NULL)
	{
		iter = iter->next;
		free(pre);
		pre = iter;
	}
	*lst = NULL;
}

/*
** Remove first elemet of list. And return name of first element.
*/

char	*remove_first(t_queue *que, int count_ways)
{
	t_nlst	*iter;
	char	*name;
	int		i;

	i = 0;
	while (i < count_ways)
	{
		if (isempty_queue(que))
		{
			que->end = NULL;
			return (NULL);
		}
		iter = que->first;
		que->first = que->first->next;
		iter->next = NULL;
		name = ft_strdup(iter->name_edg);
		free(iter);
		i++;
	}
	return (name);
}

/*
** Insert new list into queue.
*/

void	insert(t_queue *queue, char *name)
{
	t_nlst  *new;
	t_nlst  *iter;

	new = NULL;
	iter = queue->end;
	if (queue->first == NULL && queue->first == NULL)
	{
		queue->first = creat_new_lst(name);
		queue->end = queue->first;
	}
	else
	{
		new = creat_new_lst(name);
		iter->next = new;
		queue->end = new;
	}
}

/*
** Breadth-first search.
*/

void	iter_to_edg_lst(t_node *node, t_ant *ant, t_node *cur_node)
{
	int		i;
	int		weight;
	t_nlst	*edg_lst;

	edg_lst = cur_node->edg;
	i = cur_node->level;
	weight = cur_node->weight;
	cur_node->mark_bfs = 1;
	while (edg_lst != NULL)
	{
		cur_node = search_node(node, edg_lst->name_edg);
		cur_node->weight += weight;
		if (cur_node->mark_bfs == 0)
		{
			insert(ant->que, edg_lst->name_edg);
			//ft_printf("   Insetr:{%s}\n", edg_lst->name_edg);
			cur_node->mark_bfs = 1;
			cur_node->level = i + 1;
		}
		edg_lst = edg_lst->next;
	}
}

/*
** Breadth-first search.
*/

void	breadth_first_search(t_node *node, t_ant *ant)
{
	t_node	*cur_node;
	char	*name;

	insert(ant->que, ant->name_start);
	//ft_printf("   Insetr:{%s}\n", ant->name_start);
	while (!isempty_queue(ant->que))
	{
		name = remove_first(ant->que, 1);
		//ft_printf("remove:[%s]\n", name);
		cur_node = search_node(node, name);
		if (!ft_strcmp(name, ant->name_end))
		{
			ant->lvl = cur_node->level;
			delete_all_list(&ant->que->first);
			//ft_printf("Find!![%s]\n", name);
			free(name);
			//return ;
			continue ;
		}
		iter_to_edg_lst(node, ant, cur_node);
		free(name);
	}
}
