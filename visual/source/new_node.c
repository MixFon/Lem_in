/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 16:56:11 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/02 17:34:04 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_vis.h"

/*
** Print list.
** For test.
*/

void	print_node(t_node *node)
{
	while (node)
	{
		ft_printf("name = %s,  node->coor_x  = %d node->coor_y = %d\n",
			node->name, node->coor_x, node->coor_y);
		node = node->next;
	}
}

void	delete_node(t_node *node)
{
	t_node *cur_node;

	cur_node = node;
	while (node != NULL)
	{
		cur_node = node;
		free(cur_node);
		node = node->next;
	}
}

int		check_name_node(char *line)
{
	int space;

	space = 0;
	if (*line == 'L')
		return (0);
	while (*line != '\0')
	{
		if (*line == ' ')
			space++;
		line++;
	}
	if (space == 2)
		return (1);
	return (0);
}

/*
** Infill node coordinats and name.
*/

void	infill_node(t_node *node, char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0' && line[i] != ' ')
	{
		node->name[i] = line[i];
		node->name[i + 1] = '\0';
		i++;
	}
	node->coor_x = ft_atoi(line + i);
	i++;
	while (line[i] != '\0' && line[i] != ' ')
		i++;
	node->coor_y = ft_atoi(line + i);
}

t_node	*new_node(char *line)
{
	t_node *new;

	if (!(new = (t_node *)malloc(sizeof(t_node))))
		sys_err("Error malloc\n");
	new->coor_x = 0;
	new->coor_y = 0;
	new->next = NULL;
	infill_node(new, line);
	return (new);
}
