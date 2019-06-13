/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_lem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 15:58:55 by eskeleto          #+#    #+#             */
/*   Updated: 2019/06/13 19:03:37 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_free_lem(t_lem *lem)
{
	t_room *tmp_room;
	t_link *tmp_link;

	if (lem->start.name_room != NULL)
		free(lem->start.name_room);
	if (lem->end.name_room != NULL)
		free(lem->end.name_room);
	while (lem->rooms)
	{
		tmp_room = lem->rooms->next;
		if (lem->rooms->name_room != NULL)
			free(lem->rooms->name_room);
		free(lem->rooms);
		lem->rooms = tmp_room;
	}
	while (lem->links)
	{
		tmp_link = lem->links->next;
		if (lem->links->room1 != NULL)
			free(lem->links->room1);
		if (lem->links->room2 != NULL)
			free(lem->links->room2);
		free(lem->links);
		lem->links = tmp_link;
	}
}

void	ft_free_vertex(t_vertex **vertex)
{
	t_neighbour	*tmp_neighbour;
	t_vertex	*tmp_vertex;

	while (*vertex)
	{
		tmp_vertex = (*vertex)->next;
		while ((*vertex)->neighbour)
		{
			tmp_neighbour = (*vertex)->neighbour->next;
			free((*vertex)->neighbour);
			(*vertex)->neighbour = tmp_neighbour;
		}
		free(*vertex);
		*vertex = tmp_vertex;
	}
}
