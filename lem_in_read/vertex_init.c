/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:42:05 by eskeleto          #+#    #+#             */
/*   Updated: 2019/06/07 14:42:31 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_push_vertex(t_vertex **head, char *name)
{
	t_vertex	*tmp;

	tmp = (t_vertex*)malloc(sizeof(t_vertex));
	if (tmp == NULL)
		ft_error();
	else
	{
		tmp->next = *head;
		tmp->name_vertex = name;
		tmp->mark_green = 0;
		tmp->neighbour = NULL;
		*head = tmp;
	}
}

int			ft_check_vertex_exist(t_lem lem, char *name)
{
	while (lem.rooms)
	{
		if (ft_strequ(lem.rooms->name_room, name))
			return (1);
		lem.rooms = lem.rooms->next;
	}
	return (0);
}

t_vertex	*ft_init_graph(t_lem *lem)
{
	t_vertex	*vertex;
	t_lem		tmp_lem;

	vertex = NULL;
	tmp_lem = *lem;
	while (lem->rooms != NULL)
	{
		ft_push_vertex(&vertex, lem->rooms->name_room);
		lem->rooms = lem->rooms->next;
	}
	while (lem->links != NULL)
	{
		ft_add_neighbour(&vertex, lem->links, &tmp_lem);
		lem->links = lem->links->next;
	}
	*lem = tmp_lem;
	return (vertex);
}
