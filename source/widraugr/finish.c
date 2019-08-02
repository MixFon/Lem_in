/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 12:18:38 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/02 13:57:30 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

/*
** In file solution.c
*/

void	solution_print(char c, int num, char *name_edg, t_nlst **del)
{
	if (c != '\0')
		ft_printf("L%d-%s ", num, name_edg);
	free(*del);
}

/*
** In file solution.c
*/

void	finish(t_node *node, t_ant *ant)
{
	delete_node_ant(node, ant);
	exit(0);
}

/*
** In file remove_edge.c
*/

void	add_to_num_edges_help(t_nlst *pre, t_nlst ***edg, t_nlst **temp,
		char *name)
{
	if (pre == NULL)
	{
		*temp = creat_new_lst(name);
		**edg = *temp;
		return ;
	}
	else
	{
		*temp = creat_new_lst(name);
		pre->next = *temp;
	}
}

/*
** In file remove_edge.c
*/

void	init_val(int *i, t_nlst **pre, t_nlst **temp)
{
	*i = 0;
	*pre = NULL;
	*temp = NULL;
}

/*
** In file remove_edge.c
*/

int		delete_name_list_help(t_nlst **temp, int **num, int n)
{
	free(*temp);
	**num = n;
	return (0);
}
