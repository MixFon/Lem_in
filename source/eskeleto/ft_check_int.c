/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:44:30 by eskeleto          #+#    #+#             */
/*   Updated: 2019/08/01 13:36:50 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_check_int(char const *str)
{
	long long int	num;
	int				i;
	int				sign;

	i = 0;
	sign = 1;
	num = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0' && i < 12)
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if ((sign == 1 && num > 2147483647)
		|| (sign == -1 && num > 2147483648))
		return (0);
	return (1);
}
