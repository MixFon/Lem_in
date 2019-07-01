/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_first_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:19:58 by eskeleto          #+#    #+#             */
/*   Updated: 2019/06/07 14:21:25 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_vertex	*ft_find_vertex(t_vertex **vertex, char *name)
{
	t_vertex	*tmp;

	tmp = *vertex;
	while (tmp)
	{
		if (ft_strequ(name, tmp->name_vertex))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_vertex	*ft_top_stack(t_vertex **vertex, t_stack *head)
{
	if (!ft_stack_is_empty(head))
		return (ft_find_vertex(vertex, head->name));
	else
		return (NULL);
}

t_vertex	*ft_mark_vertex(t_vertex **vertex, char *name)
{
	t_vertex	*tmp;

	tmp = ft_find_vertex(vertex, name);
	tmp->mark_green = 1;
	return (tmp);
}

t_vertex	*ft_choose_neighbour(t_vertex **marked, t_vertex **vertex)
{
	t_neighbour	*tmp;
	t_vertex	*neighbour;

	if (*marked != NULL)
	{
		tmp = (*marked)->neighbour;
		while (tmp)
		{
			neighbour = ft_find_vertex(vertex, tmp->name_neighbour);
			if (neighbour->mark_green == 0)
			{
				return (neighbour);
			}
			tmp = tmp->next;
		}
	}
	return (NULL);
}

void		ft_depth_first_search(t_lem *lem, t_vertex **vertex)
{
	t_stack		*stack;
	t_vertex	*marked_vertex;
	t_vertex	*cur_vertex;

	stack = NULL;
	ft_push_stack(&stack, lem->start.name_room);
	marked_vertex = ft_mark_vertex(vertex, lem->start.name_room);
	cur_vertex = ft_choose_neighbour(&marked_vertex, vertex);
	while (!ft_stack_is_empty(stack))
	{
		while (cur_vertex != NULL)
		{
			ft_push_stack(&stack, cur_vertex->name_vertex);
			marked_vertex = ft_mark_vertex(vertex, cur_vertex->name_vertex);
			cur_vertex = ft_choose_neighbour(&marked_vertex, vertex);
		}
		ft_pop_stack(&stack);
		marked_vertex = ft_top_stack(vertex, stack);
		cur_vertex = ft_choose_neighbour(&marked_vertex, vertex);
	}
}
