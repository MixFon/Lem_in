/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_link.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:12:38 by eskeleto          #+#    #+#             */
/*   Updated: 2019/05/23 16:13:42 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_push_link(t_link **head, char *room1, char *room2)
{
	t_link	*tmp;

	tmp = (t_link*)malloc(sizeof(t_link));
	if (tmp == NULL)
		ft_error();
	else
	{
		tmp->next = *head;
		tmp->room1 = room1;
		tmp->room2 = room2;
		*head = tmp;
	}
}

int			ft_check_room_exist(t_lem lem, char *name)
{
	while (lem.rooms)
	{
		if (ft_strequ(lem.rooms->name_room, name))
			return (1);
		lem.rooms = lem.rooms->next;
	}
	return (0);
}

void	ft_check_links(t_lem *lem, char **mas, char *name1, char *name2)
{
	if (ft_strequ(name1, name2))
	{
		ft_free_lem(lem);
		ft_free_mas_strings(mas);
		ft_error();
	}
	if (!(ft_check_room_exist(*lem, name1) &&
		  ft_check_room_exist(*lem, name2)))
	{
		ft_free_lem(lem);
		ft_free_mas_strings(mas);
		ft_error();
	}
}

void	ft_read_link(char **str, t_lem *lem)
{
	char **mas;
	char *name1;
	char *name2;

	mas = ft_str_split_one_char(*str, '-');
	free(*str);
	if (ft_size_mas_strings(mas) == 2)
	{
		name1 = ft_strdup(mas[0]);
		name2 = ft_strdup(mas[1]);
		ft_push_link(&lem->links, name1, name2);
		ft_check_links(lem, mas, name1, name2);
	}
	else
	{
		ft_free_lem(lem);
		ft_free_mas_strings(mas);
		ft_error();
	}
	ft_free_mas_strings(mas);
}
