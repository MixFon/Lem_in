/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inint_back.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 16:51:53 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/02 17:17:28 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_vis.h"

t_node	*add_node(t_node *node, char **line)
{
	t_node	*n_node;
	t_node	*first;

	first = node;
	if (!node)
	{
		node = new_node(*line);
		return (node);
	}
	n_node = new_node(*line);
	n_node->next = node;
	return (n_node);
}

char	**crea_color_map(int heith, int width, const char *color)
{
	char	**map;
	int		i;
	int		j;
	char	*wid;
	char	*hei;

	wid = ft_itoa(width);
	hei = ft_itoa(heith);
	if (!(map = (char **)malloc(sizeof(char *) * (heith + 3))))
		sys_err("Error malloc\n");
	map[0] = ft_multi_strdup(4, wid, " ", hei, " 1 1 ");
	map[1] = ft_multi_strdup(2, "b c #", color);
	i = 1;
	while (++i < heith + 2)
	{
		j = -1;
		map[i] = ft_strnew(width + 1);
		while (++j < width)
			map[i][j] = 'b';
	}
	free(wid);
	free(hei);
	map[i] = NULL;
	return (map);
}

/*
** Create new structure and initialise.
*/

t_vis	*create_vis(void)
{
	t_vis	*vis;
	int		a;
	int		b;

	if (!(vis = (t_vis*)malloc(sizeof(t_vis))))
		return (NULL);
	init_val(vis);
	vis->mlx_ptr = mlx_init();
	vis->win_ptr = mlx_new_window(vis->mlx_ptr, WIDTH, HEITH, "Lem-in");
	vis->map_room = crea_color_map(vis->size_room, vis->size_room, C_ROOM);
	vis->map_start = crea_color_map(vis->size_room, vis->size_room, C_START);
	vis->map_end = crea_color_map(vis->size_room, vis->size_room, C_END);
	vis->map_score = crea_color_map(60, 200, C_SCORE);
	vis->map_visit = crea_color_map(vis->size_room - 5,
			vis->size_room - 5, C_VISIT);
	vis->img_room = mlx_xpm_to_image(vis->mlx_ptr, vis->map_room, &a, &b);
	vis->img_start = mlx_xpm_to_image(vis->mlx_ptr, vis->map_start, &a, &b);
	vis->img_end = mlx_xpm_to_image(vis->mlx_ptr, vis->map_end, &a, &b);
	vis->img_score = mlx_xpm_to_image(vis->mlx_ptr, vis->map_score, &a, &b);
	vis->img_visit = mlx_xpm_to_image(vis->mlx_ptr, vis->map_visit, &a, &b);
	delete_all_arr(vis);
	init_back(vis);
	return (vis);
}

/*
** Init value struct.
*/

void	init_val(t_vis *vis)
{
	vis->mlx_ptr = NULL;
	vis->win_ptr = NULL;
	vis->img_back = NULL;
	vis->node = NULL;
	vis->link = NULL;
	vis->step = NULL;
	vis->heith = 0;
	vis->width = 0;
	vis->size_room = SIZE_ROOM;
	vis->count_ant = 0;
	vis->map_room = NULL;
	vis->map_score = NULL;
	vis->img_room = NULL;
	vis->img_score = NULL;
	vis->img_start = NULL;
	vis->img_end = NULL;
}

/*
** Init background and menu.
*/

int		init_back(t_vis *vis)
{
	if (!(vis->img_back = mlx_xpm_file_to_image(vis->mlx_ptr,
			IMGPATH, &vis->heith, &vis->width)))
		sys_err("Error image background.\n");
	if (!(vis->img_error = mlx_xpm_file_to_image(vis->mlx_ptr,
			IMGERR, &vis->heith, &vis->width)))
		sys_err("Error image ERROR.\n");
	return (1);
}
