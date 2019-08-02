/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_score.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 16:30:00 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/02 17:32:53 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_vis.h"

void	print_rooms(t_vis *vis)
{
	t_node	*node;

	node = vis->node;
	while (node != NULL)
	{
		mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_room,
				node->coor_x, node->coor_y);
		if (ft_strcmp(node->name, vis->nstart) == 0)
			mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_start,
				node->coor_x, node->coor_y);
		else	if (ft_strcmp(node->name, vis->nend) == 0)
			mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_end,
				node->coor_x, node->coor_y);
		mlx_string_put(vis->mlx_ptr, vis->win_ptr,
			node->coor_x - 0, node->coor_y - 20, 0x000000, node->name);
		node = node->next;
	}
}

void	rectengle_visit(t_vis *vis, char **arr)
{
	int		num;
	char	*str_num;
	char	*name_room;

	num = 0;
	while (*arr != NULL)
	{
		num = ft_atoi(*(arr) + 1);
		ft_printf("num = %d\n", num);
		str_num = ft_itoa(num);
		ft_printf("str_num = %s\n", str_num);
		name_room = return_name_node(*arr);
		print_visit(vis, str_num, name_room);
		ft_strdel(&str_num);
		arr++;
	}
}

void	next_step(t_link **step)
{
	t_link *temp;

	temp = *step;
	*step = (*step)->next;
	free(temp->name);
	free(temp);
}

int		print_steps(t_vis *vis)
{
	char **arr;

	if (vis->step == NULL)
		return (0);
	ft_putendl("new step");
	print_score(vis);
	sleep(2);
	print_rooms(vis);
	arr = ft_strsplit(vis->step->name, ' ');
	next_step(&vis->step);
	rectengle_visit(vis, arr);
	print_arr(arr);
	delete_arr(arr);
	return (0);
}

/*
** Print rectangle in down whith scores.
*/

void	print_score(t_vis *vis)
{
	static int	steps = 0;
	char		*str;

	str = ft_itoa(steps);
	steps++;
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr,
			vis->img_score, 1040, 660);
	mlx_string_put(vis->mlx_ptr, vis->win_ptr, 1070, 695, 0xBF2956,
		"Steps:");
	mlx_string_put(vis->mlx_ptr, vis->win_ptr, 1200, 695, 0xBF2956,
		str);
	free(str);
	str = ft_itoa(vis->count_ant);
	mlx_string_put(vis->mlx_ptr, vis->win_ptr, 1070, 670, 0xBF2956,
		"Count ants:");
	mlx_string_put(vis->mlx_ptr, vis->win_ptr, 1200, 670, 0xBF2956,
		str);
	free(str);
}
