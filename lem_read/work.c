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

char 	*ft_strjoin_with_n(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	int		len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\n';
	str[i + 1] = '\0';
	return (str);
}

void	ft_to_file(char **file, char *line)
{
	char *tmp;

	tmp = ft_strdup(*file);
	free(*file);
	*file = ft_strjoin_with_n(tmp, line);
	free(tmp);
}