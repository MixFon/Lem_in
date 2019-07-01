
#include "../../include/lem.h"

void	add_to_num_edges(t_nlst **edg, char *name, int num)
{
	t_nlst	*iter;
	t_nlst	*pre;
	t_nlst	*temp;
	int		i;

	i = 0;
	iter = *edg;
	pre = NULL;
	temp = NULL;
	while (iter != NULL)
	{
		if (i == num)
		{
			temp = creat_new_lst(name);
			temp->next = iter;
			if (pre == NULL)
				*edg = temp;
			else
				pre->next = temp;
			//print_edges(*edg);
			return ;
		}
		i++;
		pre = iter;
		iter = iter->next;
	}
	if (pre == NULL)
	{
		temp = creat_new_lst(name);
		*edg = temp;
		//print_edges(*edg);
		return ;
	}
	else
	{
		temp = creat_new_lst(name);
		pre->next = temp;
		//print_edges(*edg);
	}	
}
/*
** Определение первого и второго по весу узлов.
** Во второе сравнение не заходит. Возможно проверка не нужна.
*/

void	define_fir_sec_wei(t_node *node, t_ant *ant)
{
	t_nlst	*way;
	t_node	*cur_node;
	int		fir;
	int		sec;

	fir = 0;
	sec = 0;
	way = ant->ways->way;
	while (way != NULL)
	{
		cur_node = search_node(node, way->name_edg);
		if (cur_node->weight > fir && ft_strcmp(way->name_edg, ant->name_end))
		{
			sec = fir;
			fir = cur_node->weight;
			ft_strcpy(ant->sec_wei, ant->fir_wei);
			ft_strcpy(ant->fir_wei, cur_node->name);
		}
		else if (cur_node->weight > sec && ft_strcmp(way->name_edg, ant->name_end))
		{
			sec = cur_node->weight;
			ft_strcpy(ant->sec_wei, cur_node->name);
		}
		way = way->next;
	}
}

/*
** Recalc_stepsad map.
*/

int		calc_steps(t_ant *ant)
{
	calc_all_ways(ant);
	ant->pre_steps = ant->cur_steps;
	if (((ant->all_steps + ant->count_ant - ant->count_ways)
				% ant->count_ways) != 0)
		ant->cur_steps = (ant->all_steps + (ant->count_ant -
					ant->count_ways)) / ant->count_ways + 1;
	else
		ant->cur_steps = (ant->all_steps + (ant->count_ant -
					ant->count_ways)) / ant->count_ways;
	if (ant->cur_steps > ant->pre_steps && ant->pre_steps != 0)
		return (1);
	else
		return (0);
}

/*
** Remove an edge from the list..
** Удоляет один лист  из списка соседей.
*/

int		delete_name_list(char *name, t_nlst **nlst, int *num)
{
	t_nlst	*iter;
	t_nlst	*pre;
	int		i;

	i = 1;
	pre = *nlst;
	iter = (*nlst)->next;
	if (!ft_strcmp(name, (*nlst)->name_edg))
	{
		*nlst = (*nlst)->next;
		free(pre);	
		*num = 0;
		return (0);
	}
	while (iter != NULL)
	{
		if (!ft_strcmp(name, iter->name_edg))
		{
			pre->next = iter->next;	
			free(iter);
			*num = i;
			return (0);
		}
		i++;
		pre = pre->next;
		iter = iter->next;
	}
	return (1);
}

/*
** Remove an edge from the list.
*/

void	remove_edge(t_node *node, t_ant *ant)
{
	t_node	*fir_node;
	t_node	*sec_node;

	if (ant->fir_wei[0] == '\0' || ant->sec_wei[0] == '\0')
		return ;
	ft_strcpy(ant->pre_firn, ant->fir_wei);
	ft_strcpy(ant->pre_secn, ant->sec_wei);
	fir_node = search_node(node, ant->fir_wei);
	sec_node = search_node(node, ant->sec_wei);
	if (delete_name_list(fir_node->name, &sec_node->edg, &ant->num_fn))
	{
		ant->bl = 1;
		ant->pre_steps = 1;
	}
	if (delete_name_list(sec_node->name, &fir_node->edg, &ant->num_sn))
	{
		ant->bl = 1;
		ant->pre_steps = 1;
	}
}
