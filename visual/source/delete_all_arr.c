/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_all_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 17:15:57 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/02 17:17:43 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_vis.h"

void	delete_all_arr(t_vis *vis)
{
	delete_arr(vis->map_room);
	delete_arr(vis->map_visit);
	delete_arr(vis->map_start);
	delete_arr(vis->map_end);
}
