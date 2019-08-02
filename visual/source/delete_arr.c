/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 16:34:25 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/02 17:08:26 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_vis.h"

char	*return_name_node(char *str)
{
	char *iter;

	iter = str;
	while (*iter != '\0' && *iter != '-')
		iter++;
	return (iter + 1);
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

void	print_visit(t_vis *vis, char *str_num, char *name_room)
{
	t_node *node;

	ft_printf("name_room = {%s}, str_num = {%s}\n", name_room, str_num);
	if (!(node = search_node(vis->node, name_room)))
	{
		ft_putendl("!!!not room!!!!");
		return ;
	}
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_visit,
			node->coor_x + 3, node->coor_y + 2);
	mlx_string_put(vis->mlx_ptr, vis->win_ptr,
			node->coor_x + 20, node->coor_y + 15, 0x000000, str_num);
}

void	print_arr(char **arr)
{
	while (*arr != NULL)
	{
		ft_printf("{%s}\n", *arr);
		arr++;
	}
}

void	delete_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_strdel(&arr[i]);
		i++;
	}
	free(arr);
}
