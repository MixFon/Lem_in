/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:07:57 by eskeleto          #+#    #+#             */
/*   Updated: 2019/06/13 19:52:12 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_check_linking(t_lem *lem, t_vertex **vertex)
{
	t_vertex	*tmp;

	tmp = *vertex;
	while (tmp != NULL)
	{
		if (tmp->mark_green == 0)
		{
			ft_free_lem(lem);
			ft_free_vertex(vertex);
			ft_error();
		}
		tmp = tmp->next;
	}
}

void	ft_check_graph(t_lem *lem)
{
	t_vertex	*vertex;

	if (lem->start.name_room == NULL || lem->end.name_room == NULL)
	{
		ft_free_lem(lem);
		ft_error();
	}
	vertex = ft_init_graph(lem);
	ft_depth_first_search(lem, &vertex);
	ft_check_linking(lem, &vertex);
	ft_free_vertex(&vertex);
}