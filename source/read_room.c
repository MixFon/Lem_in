/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:13:58 by eskeleto          #+#    #+#             */
/*   Updated: 2019/05/23 16:16:04 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_push_room(t_room **head, char *name, int x, int y)
{
	t_room	*tmp;

	tmp = (t_room*)malloc(sizeof(t_room));
	if (tmp == NULL)
		ft_error();
	else
	{
		tmp->next = *head;
		tmp->name_room = name;
		tmp->coord_x = x;
		tmp->coord_y = y;
		*head = tmp;
	}
}

void	ft_check_names_of_rooms(t_lem *lem, char *name, char **mas)
{
	t_room	*tmp;

	tmp = lem->rooms->next;
	while (tmp != NULL)
	{
		if (ft_strequ(tmp->name_room, name))
		{
			ft_free_mas_strings(mas);
			ft_free_lem(lem);
			ft_error();
		}
		tmp = tmp->next;
	}
}

void	ft_check_coords_of_rooms(t_lem *lem, int x, int y, char **mas)
{
	t_room	*tmp;

	tmp = lem->rooms->next;
	while (tmp != NULL)
	{
		if (tmp->coord_x == x && tmp->coord_y == y)
		{
			ft_free_mas_strings(mas);
			ft_free_lem(lem);
			ft_error();
		}
		tmp = tmp->next;
	}
}

void	ft_read_room(char **str, t_lem *lem)
{
	char **mas;
	char *name;

	mas = ft_str_split_one_char(*str, ' ');
	free(*str);
	if (ft_size_mas_strings(mas) == 3 &&
			ft_strisdigit(mas[1]) && ft_strisdigit(mas[2]))
	{
		name = ft_strdup(mas[0]);
		ft_push_room(&lem->rooms, name, ft_atoi(mas[1]), ft_atoi(mas[2]));
		ft_check_names_of_rooms(lem, name, mas);
		ft_check_coords_of_rooms(lem, ft_atoi(mas[1]), ft_atoi(mas[2]), mas);
	}
	else
	{
		ft_free_lem(lem);
		ft_free_mas_strings(mas);
		ft_error();
	}
	ft_free_mas_strings(mas);
}
