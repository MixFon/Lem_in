/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 16:42:53 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/02 17:31:00 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_vis.h"

void	swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_draw_line_source(t_point *delta, t_point *sign, t_point point1,
		t_point point2)
{
	(*delta).x = ABS((point2.x - point1.x));
	(*delta).y = ABS((point2.y - point1.y));
	(*sign).x = (point1.x < point2.x) ? 1 : -1;
	(*sign).y = (point1.y < point2.y) ? 1 : -1;
}

void	ft_draw_line(void *mlx_ptr, void *win_ptr, t_point point1,
		t_point point2)
{
	t_point delta;
	t_point	sign;
	int		error;
	int		error2;

	ft_draw_line_source(&delta, &sign, point1, point2);
	error = delta.x - delta.y;
	mlx_pixel_put(mlx_ptr, win_ptr, point2.x, point2.y, 0xBF2956);
	while (point1.x != point2.x || point1.y != point2.y)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, point1.x, point1.y, 0xBF2956);
		error2 = error * 2;
		if (error2 > -delta.y)
		{
			error -= delta.y;
			point1.x += sign.x;
		}
		if (error2 < delta.x)
		{
			error += delta.x;
			point1.y += sign.y;
		}
	}
}

void	put_line(t_vis *vis, t_coor *start, t_coor *end)
{
	t_point	point1;
	t_point	point2;

	point1.x = start->x + CENTR;
	point1.y = start->y + CENTR;
	point2.x = end->x + CENTR;
	point2.y = end->y + CENTR;
	ft_draw_line(vis->mlx_ptr, vis->win_ptr, point1, point2);
}

char	*second_name(t_link *link)
{
	size_t	len;

	len = ft_strcl(link->name, '-');
	return (link->name + len + 1);
}
