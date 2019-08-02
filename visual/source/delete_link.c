/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 16:47:30 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/02 17:09:00 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_vis.h"

/*
** Check link node.
*/

int		check_link_node(char *line)
{
	while (*line != '\0' && *line != 'L')
	{
		if (*line == '-')
			return (1);
		line++;
	}
	return (0);
}

void	print_link(t_link *link)
{
	while (link != NULL)
	{
		ft_printf("link [%s]\n", link->name);
		link = link->next;
	}
}

/*
** If pressed key esc close programm.
*/

int		exit_key(int key)
{
	if (key == 53)
		sys_err("Normal exit.\n");
	return (0);
}

void	print_error(t_vis *vis)
{
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_error, 0, 0);
	sleep(3);
	sys_err("Error file\n");
}

void	delete_link(t_link **link)
{
	t_link	*temp;

	temp = *link;
	while (*link != NULL)
	{
		*link = (*link)->next;
		free(temp->name);
		free(temp);
		temp = *link;
	}
	*link = NULL;
}
