/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_new_link.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 16:39:01 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/02 17:31:14 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_vis.h"

t_coor	*remove_coor(t_vis *vis, char *temp)
{
	t_coor	*coor;
	t_node	*node;

	if (!(coor = (t_coor *)malloc(sizeof(t_coor))))
		sys_err("Error malloc\n");
	coor->x = 0;
	coor->y = 0;
	node = search_node(vis->node, temp);
	coor->x = node->coor_x;
	coor->y = node->coor_y;
	return (coor);
}

char	*first_name(t_link *link)
{
	char	*name;
	size_t	len;

	len = ft_strcl(link->name, '-');
	name = ft_strnew(len);
	ft_strncpy(name, link->name, len);
	return (name);
}

void	put_edges(t_vis *vis)
{
	char	*temp;
	t_link	*link;
	t_coor	*start;
	t_coor	*end;

	while (vis->link != NULL)
	{
		temp = first_name(vis->link);
		start = remove_coor(vis, temp);
		ft_strdel(&temp);
		temp = second_name(vis->link);
		end = remove_coor(vis, temp);
		put_line(vis, start, end);
		free(start);
		free(end);
		link = vis->link;
		vis->link = vis->link->next;
		free(link->name);
		free(link);
	}
}

/*
** If there is error. Shut down the program.
*/

void	sys_err(char *err)
{
	write(2, err, ft_strlen(err));
	exit(0);
}

/*
** Create new list for links and steps.
*/

t_link	*creat_new_link(char *name)
{
	t_link *newl;
	size_t len;

	len = ft_strlen(name);
	if (!(newl = (t_link *)malloc(sizeof(t_link))))
		sys_err("Error malloc.\n");
	newl->name = ft_strnew(len);
	ft_strncpy(newl->name, name, len);
	newl->name[len] = '\0';
	newl->next = NULL;
	return (newl);
}
