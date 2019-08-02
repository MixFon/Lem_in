/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_ways.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:50:11 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/02 11:31:49 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

void	delete_ways(t_ant *ant)
{
	t_ways	*ways;
	t_ways	*pre_ways;

	ways = ant->ways;
	ant->lvl = 0;
	ant->count_ways = 0;
	while (ways != NULL)
	{
		delete_all_list(&ways->way);
		pre_ways = ways;
		ways = ways->next;
		free(pre_ways);
	}
	ant->ways = NULL;
}

/*
** If there is error. Shut down the program.
*/

void	sys_err(char *err)
{
	write(2, err, ft_strlen(err));
	exit(0);
}

int		finish_cut(t_ant *ant, t_ways *pre, int *now_step, int *pre_step)
{
	if (*now_step >= *pre_step && *pre_step != 0)
	{
		delete_tail_ways(pre->next);
		pre->next = NULL;
		ant->cur_steps = *pre_step + 1;
		ant->count_ways = ant->a - 1;
		return (1);
	}
	return (0);
}

void	save_date(t_ant *ant, int now_step)
{
	ant->a++;
	ant->cur_steps = now_step;
	ant->count_ways = ant->a - 1;
}

void	cut_ways(t_ant *ant)
{
	t_ways	*ways;
	t_ways	*pre;
	int		pre_step;
	int		now_step;
	int		sum;

	ant->a = 1;
	now_step = 0;
	sum = 0;
	ways = ant->ways;
	while (ways != NULL)
	{
		pre_step = now_step;
		sum += ways->len_way;
		if (((sum + ant->count_ant - ant->a) % ant->a) != 0)
			now_step = (sum + ant->count_ant - ant->a) / ant->a + 1;
		else
			now_step = (sum + ant->count_ant - ant->a) / ant->a;
		if (finish_cut(ant, pre, &now_step, &pre_step) == 1)
			return ;
		save_date(ant, now_step);
		pre = ways;
		ways = ways->next;
	}
}
