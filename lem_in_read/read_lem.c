/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:09:21 by eskeleto          #+#    #+#             */
/*   Updated: 2019/06/12 13:43:16 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_is_comment(char *str)
{
	if (ft_strequ(str, "##start") || ft_strequ(str, "##end"))
		return (0);
	else if (str[0] == '#')
		return (1);
	return (0);
}

void	ft_get_counts_ants(t_lem *lem)
{
	char	*line;
	int		count_ants;

	line = NULL;
	if (get_next_line(0, &line) > 0)
	{
		if (ft_is_comment(line))
		{
			free(line);
			ft_get_counts_ants(lem);
			return ;
		}
		else if (ft_strisdigit(line))
		{
			count_ants = ft_atoi(line);
			if (ft_check_int(line) && (count_ants > 0))
			{
				lem->count_ants = count_ants;
				free(line);
				return ;
			}
		}
		free(line);
	}
	ft_error();
}

void	ft_read_farm(t_lem *lem)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
		{
			ft_read_start_or_end(&line, lem);
		}
		else if (line[0] == '#')
		{
			free(line);
		}
		else if (ft_strchr(line, '-') && !ft_strchr(line, ' '))
		{
			ft_read_link(&line, lem);
		}
		else
		{
			ft_read_room(&line, lem);
		}
		line = NULL;
	}
}

void	ft_init_lem(t_lem *lem)
{
	lem->count_ants = 0;
	lem->rooms = NULL;
	lem->start.name_room = NULL;
	lem->start.coord_x = 0;
	lem->start.coord_y = 0;
	lem->start.next = NULL;
	lem->end.name_room = NULL;
	lem->end.coord_x = 0;
	lem->end.coord_y = 0;
	lem->end.next = NULL;
	lem->links = NULL;
}

t_lem	ft_get_lem(void)
{
	t_lem	lem;

	ft_init_lem(&lem);
	ft_get_counts_ants(&lem);
	ft_read_farm(&lem);
	return (lem);
}
