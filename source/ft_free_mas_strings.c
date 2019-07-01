/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_mas_strings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:45:08 by eskeleto          #+#    #+#             */
/*   Updated: 2019/06/13 19:03:33 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_free_mas_strings(char **mas)
{
	int i;

	i = 0;
	while (mas[i] != NULL)
	{
		free(mas[i]);
		i++;
	}
	free(mas);
	return (i);
}
