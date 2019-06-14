/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_start_and_end.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:16:25 by eskeleto          #+#    #+#             */
/*   Updated: 2019/05/23 16:20:14 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_free_mas_and_lem(t_lem *lem, char ***mas)
{
	ft_free_lem(lem);
	ft_free_mas_strings(*mas);
	ft_error();
}

void	ft_read_start(char **str, t_lem *lem)
{
	char **mas;

	if (lem->start.name_room != NULL)
	{
		free(*str);
		ft_free_lem(lem);
		ft_error();
	}
	mas = ft_str_split_one_char(*str, ' ');
	free(*str);
	if (ft_size_mas_strings(mas) == 3 &&
			ft_strisdigit(mas[1]) && ft_strisdigit(mas[2]))
	{
		lem->start.name_room = ft_strdup(mas[0]);
		lem->start.coord_x = ft_atoi(mas[1]);
		lem->start.coord_y = ft_atoi(mas[2]);
		ft_push_room(&lem->rooms, ft_strdup(mas[0]),
				ft_atoi(mas[1]), ft_atoi(mas[2]));
		ft_check_names_of_rooms(lem, lem->start.name_room, mas);
		ft_check_coords_of_rooms(lem, ft_atoi(mas[1]), ft_atoi(mas[2]), mas);
	}
	else
		ft_free_mas_and_lem(lem, &mas);
	ft_free_mas_strings(mas);
}

void	ft_read_end(char **str, t_lem *lem)
{
	char **mas;

	if (lem->end.name_room != NULL)
	{
		free(*str);
		ft_free_lem(lem);
		ft_error();
	}
	mas = ft_str_split_one_char(*str, ' ');
	free(*str);
	if (ft_size_mas_strings(mas) == 3 &&
			ft_strisdigit(mas[1]) && ft_strisdigit(mas[2]))
	{
		lem->end.name_room = ft_strdup(mas[0]);
		lem->end.coord_x = ft_atoi(mas[1]);
		lem->end.coord_y = ft_atoi(mas[2]);
		ft_push_room(&lem->rooms, ft_strdup(mas[0]),
				ft_atoi(mas[1]), ft_atoi(mas[2]));
		ft_check_names_of_rooms(lem, lem->end.name_room, mas);
		ft_check_coords_of_rooms(lem, ft_atoi(mas[1]), ft_atoi(mas[2]), mas);
	}
	else
		ft_free_mas_and_lem(lem, &mas);
	ft_free_mas_strings(mas);
}

void	ft_start_or_end_not_comment(char **str, t_lem *lem, char **line)
{
	if (line[0][0] != '#')
	{
		if (ft_strequ(*str, "##start"))
		{
			free(*str);
			ft_read_start(line, lem);
			return ;
		}
		else if (ft_strequ(*str, "##end"))
		{
			free(*str);
			ft_read_end(line, lem);
			return ;
		}
	}
	else if (ft_strequ(*line, "##start") || ft_strequ(*line, "##end"))
	{
		free(*line);
		free(*str);
		ft_free_lem(lem);
		ft_error();
	}
}

void	ft_read_start_or_end(char **str, t_lem *lem, char **file)
{
	char *line;

	line = NULL;
	if (get_next_line(0, &line) > 0)
	{
		ft_to_file(file, line);
		if (ft_is_comment(line))
		{
			free(line);
			ft_read_start_or_end(str, lem, file);
		}
		else
		{
			ft_start_or_end_not_comment(str, lem, &line);
			return ;
		}
	}
	else if (line == NULL)
	{
		free(*str);
		ft_free_lem(lem);
		free(*file);
		ft_error();
	}
}
