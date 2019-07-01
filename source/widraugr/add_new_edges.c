
#include "../../include/lem.h"

void	delete_dublicate(t_ant *ant)
{
	if (ant->ways->next == NULL)
		return ;
	if (ant->ways->len_way == 1 && ant->ways->next->len_way == 1)
	{
		delete_tail_ways(ant->ways->next);
		ant->ways->next = NULL;
		ant->count_ways = 1;
	}
}

/*
** Remove last elemet of list. And return name of last element.
*/

void	remove_last(t_queue *que, int count_ways)
{
	t_nlst	*iter;
	t_nlst	*temp;
	int		i;

	i = -1;
	while (++i < count_ways)
	{
		if (isempty_queue(que))
		{
			que->end = NULL;
			return ;
		}
		iter = que->first;
		temp = que->end;
		if (iter == temp)
			return ;
		while (iter->next != temp)
			iter = iter->next;
		que->end = iter;
		que->end->next = NULL;
		free(temp);
	}
}

void	re_count_steps(t_ant *ant)
{
	if (ant->ways->len_way == 1 && ant->cur_steps < ant->count_ant)
	{
		calc_all_ways(ant);
		ant->cur_steps = ant->count_ant / ant->count_ways + ant->max_count_way - 1;
	}
	if (ant->ways->len_way == 1 && ant->cur_steps > ant->count_ant)
	{
		ant->cur_steps = ant->count_ant;
		delete_tail_ways(ant->ways->next);
		ant->ways->next = NULL;
		ant->count_ways = 1;
	}
}

void	missing_row(t_ant *ant, t_nlst **pant_it, int i, int *b)
{
	int	miss;

	miss = i / ant->count_ways;
	while (miss > 0)
	{
		add_new_edges(pant_it, "\0");
		b++;
		miss--;
	}
}

/*
** Add new list name edgess.
*/

void	add_new_edges(t_nlst **nlst, char *name)
{
	t_nlst *first;
	t_nlst *new_esg;

	first = *nlst;
	if (!first)
	{
		*nlst= creat_new_lst(name);
		return ;
	}
	while (first->next != NULL)
		first = first->next;
	new_esg = creat_new_lst(name);
	first->next = new_esg;
}
