/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:04:38 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/02 17:37:47 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_vis.h"

/*
** Add new list name edgess.
*/

void	add_list_link(t_link **link, char *name)
{
	t_link	*first;
	t_link	*new_edg;

	first = *link;
	if (!first)
	{
		*link = creat_new_link(name);
		return ;
	}
	while (first->next != NULL)
		first = first->next;
	new_edg = creat_new_link(name);
	first->next = new_edg;
}

void	input_room(t_node *node, t_vis *vis, char **arr)
{
	char	*name;
	t_node	*cur_node;

	name = NULL;
	while (*arr != NULL)
	{
		name = return_name_node(*arr);
		cur_node = search_node(node, name);
		ft_printf("name {%s}, x =[%d] y = [%d]\n",
				cur_node->name, cur_node->coor_x, cur_node->coor_y);
		mlx_string_put(vis->mlx_ptr, vis->win_ptr,
				cur_node->coor_y * 10, cur_node->coor_x * 10, 0x2056B6, name);
		arr++;
	}
}

int		check_octotopr(t_vis *vis, char **line)
{
	if (ft_strcmp("##start", *line) == 0)
	{
		ft_strdel(line);
		get_next_line(0, line);
		ft_strncpy(vis->nstart, *line, ft_strcl(*line, ' '));
		ft_printf("start {%s}\n", vis->nstart);
	}
	else	if (ft_strcmp("##end", *line) == 0)
	{
		ft_strdel(line);
		get_next_line(0, line);
		ft_strncpy(vis->nend, *line, ft_strcl(*line, ' '));
		ft_printf("end {%s}\n", vis->nend);
	}
	return (0);
}

int		read_map(t_vis *vis)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line))
	{
		if (!vis->count_ant)
			vis->count_ant = ft_atoi(line);
		check_octotopr(vis, &line);
		if (!ft_strcmp("ERROR", line))
			print_error(vis);
		else	if (check_name_node(line))
		{
			ft_putendl(line);
			vis->node = add_node(vis->node, &line);
		}
		else	if (check_link_node(line))
			add_list_link(&vis->link, line);
		else	if (*line == 'L')
			add_list_link(&vis->step, line);
		ft_strdel(&line);
	}
	print_link(vis->link);
	print_link(vis->step);
	ft_strdel(&line);
	return (0);
}

int		main(void)
{
	t_vis	*vis;

	if (!(vis = create_vis()))
		exit(0);
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_back, 0, 0);
	read_map(vis);
	put_edges(vis);
	print_score(vis);
	print_rooms(vis);
	mlx_key_hook(vis->win_ptr, exit_key, (void*)0);
	mlx_loop_hook(vis->mlx_ptr, print_steps, vis);
	mlx_loop(vis->mlx_ptr);
	return (0);
}
