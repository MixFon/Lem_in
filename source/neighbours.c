/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neighbours.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:32:58 by eskeleto          #+#    #+#             */
/*   Updated: 2019/06/07 14:33:02 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_push_neighbour(t_neighbour **head, char *name)
{
	t_neighbour	*tmp;

	tmp = (t_neighbour*)malloc(sizeof(t_neighbour));
	if (tmp == NULL)
		ft_error();
	else
	{
		tmp->next = *head;
		tmp->name_neighbour = name;
		*head = tmp;
	}
}

void		ft_add_neighbour(t_vertex **vertex, t_link *link)
{
	t_vertex *tmp;

	tmp = *vertex;
	while (*vertex != NULL)
	{
		if (ft_strequ((*vertex)->name_vertex, link->room1))
			ft_push_neighbour(&(*vertex)->neighbour, link->room2);
		if (ft_strequ((*vertex)->name_vertex, link->room2))
			ft_push_neighbour(&(*vertex)->neighbour, link->room1);
		*vertex = (*vertex)->next;
	}
	*vertex = tmp;
}
