/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:41:47 by eskeleto          #+#    #+#             */
/*   Updated: 2019/06/07 14:41:48 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_stack_is_empty(t_stack *head)
{
	if (head)
		return (0);
	return (1);
}

void	ft_push_stack(t_stack **head, char *name)
{
	t_stack	*tmp;

	tmp = (t_stack*)malloc(sizeof(t_stack));
	if (tmp == NULL)
		ft_error();
	else
	{
		tmp->next = *head;
		tmp->name = name;
		*head = tmp;
	}
}

void	ft_pop_stack(t_stack **head)
{
	t_stack *out;

	if ((*head) != NULL)
	{
		out = *head;
		*head = out->next;
		free(out);
	}
}
