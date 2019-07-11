/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:04:38 by widraugr          #+#    #+#             */
/*   Updated: 2019/06/26 14:18:09 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_vis.h"

/*
** If there is error. Shut down the program.
*/

void	sys_err(char *err)
{
	write(2, err, ft_strlen(err));
	exit(0);
}

/*
** Print list. 
** For test.
*/

void	print_node(t_node *node)
{
	while (node)
	{
		ft_printf("name = %s,  node->coor_x  = %d node->coor_y = %d\n",
			node->name, node->coor_x, node->coor_y);
		node = node->next;
	}
}

void	delete_node(t_node *node)
{
	t_node *cur_node;

	cur_node = node;
	while(node != NULL)
	{
		cur_node = node;
		free(cur_node);
		node = node->next;
	}
}

int		check_name_node(char *line)
{
	int space;

	space = 0;
	if (*line == 'L')
		return (0);
	while (*line != '\0')
	{
		if (*line == ' ')
		   space++;	
		line++;
	}
	if (space == 2)
		return (1);
	return (0);
}

/*
** Infill node coordinats and name.
*/

void	infill_node(t_node *node, char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0' && line[i] != ' ')
	{
		node->name[i] = line[i];
		node->name[i + 1] = '\0';
		i++;
	}
	node->coor_x = ft_atoi(line + i);
	i++;
	while (line[i] != '\0' && line[i] != ' ')
		i++;
	node->coor_y = ft_atoi(line + i);
}

t_node	*new_node(char *line)
{
	t_node *new;

	if (!(new = (t_node *)malloc(sizeof(t_node))))
		sys_err("Error malloc\n");
	new->coor_x = 0;
	new->coor_y = 0;
	new->next = NULL;
	infill_node(new, line);
	return (new);
}

t_node	*add_node(t_node *node, char **line)
{
	t_node	*n_node;
	t_node	*first;

	first = node;
	if (!node)
	{
		node = new_node(*line);
		return (node);
	}
	n_node = new_node(*line);
	n_node->next = node;
	return (n_node);
}

/*
** Serch for a node by name.
*/

t_node	*search_node(t_node *node, char *name)
{
	while (node)
	{
		if (ft_strcmp(node->name, name) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	print_arr(char **arr)
{
	while (*arr != NULL)
	{
		ft_printf("{%s}\n", *arr);
		arr++;
	}
}

void	delete_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_strdel(&arr[i]);
		i++;
	}
	free(arr);
}

char	*return_name_node(char *str)
{
	char *iter;

	iter = str;
	while (*iter != '\0' && *iter != '-')
		iter++;
	return (iter + 1);
}

/*
** Create new list for links and steps.
*/

t_link	*creat_new_link(char *name)
{
	t_link *new;
	size_t len;

	len = ft_strlen(name);
	if (!(new = (t_link *)malloc(sizeof(t_link))))
		sys_err("Error malloc.\n");
	new->name = ft_strnew(len);
	ft_strncpy(new->name, name, len);
	new->name[len] = '\0';
	new->next = NULL;
	return (new);
}

/*
** Add new list name edgess.
*/

void	add_list_link(t_link **link, char *name)
{
	t_link	*first;
	t_link	*new_edg;

	first = *link;
	if (!first)
	{
		*link= creat_new_link(name);
		return ;
	}
	while (first->next != NULL)
		first = first->next;
	new_edg = creat_new_link(name);
	first->next = new_edg;
	//*link = new_edg;
}

void	input_room(t_node *node, t_vis *vis, char **arr)
{
	char	*name;
	t_node	*cur_node;

	name = NULL;	
	while (*arr != NULL)
	{
		name = return_name_node(*arr);
		cur_node = search_node(node, name);
		ft_printf("name {%s}, x =[%d] y = [%d]\n",
				cur_node->name, cur_node->coor_x, cur_node->coor_y);
		mlx_string_put(vis->mlx_ptr, vis->win_ptr,
				cur_node->coor_y * 10, cur_node->coor_x * 10, 0x2056B6, name);
		arr++;
	}
}

char	**crea_color_map(int heith, int width, const char *color)
{
	char	**map;
	int		i;
	int		j;

	if (!(map = (char **)malloc(sizeof(char *) * (heith + 3))))
		sys_err("Error malloc\n");
	map[0] = ft_multi_strdup(4, ft_itoa(width), " ", ft_itoa(heith), " 1 1 "); 
	map[1] = ft_multi_strdup(2, "b c #", color);
	i = 1;
	while (++i < heith + 2)
	{
		j = -1;
		map[i] = ft_strnew(width + 1);
		while (++j < width)
			map[i][j] = 'b';
	}
	map[i] = NULL;
	return (map);
}

/*
** Init value struct.
*/

void	init_val(t_vis *vis)
{
	vis->mlx_ptr = NULL;
	vis->win_ptr = NULL;
	vis->img_back = NULL;
	vis->node = NULL;
	vis->link = NULL;
	vis->step = NULL;
	vis->heith = 0;
	vis->width = 0;
	vis->size_room = SIZE_ROOM;
	vis->count_ant = 0;
	vis->map_room = NULL;
	vis->map_score = NULL;
	vis->img_room = NULL;
	vis->img_score = NULL;
	vis->img_start = NULL;
	vis->img_end = NULL;
}

/*
** Init background and menu.
*/

int		init_back(t_vis *vis)
{
	if(!(vis->img_back = mlx_xpm_file_to_image(vis->mlx_ptr,
			IMGPATH, &vis->heith, &vis->width)))
		sys_err("Error image background.\n");
	if(!(vis->img_error = mlx_xpm_file_to_image(vis->mlx_ptr,
			IMGERR, &vis->heith, &vis->width)))
		sys_err("Error image ERROR.\n");
	return (1);
}

/*
** Create new structure and initialise.
*/

t_vis	*create_vis(void)
{
	t_vis	*vis;
	int		a;
	int		b;

	if(!(vis = (t_vis*)malloc(sizeof(t_vis))))
		return (NULL);
	init_val(vis);
	vis->mlx_ptr = mlx_init();
	vis->win_ptr = mlx_new_window(vis->mlx_ptr, WIDTH, HEITH, "Lem-in");
	vis->map_room = crea_color_map(vis->size_room, vis->size_room, C_ROOM);
	vis->map_start = crea_color_map(vis->size_room, vis->size_room, C_START);
	vis->map_end = crea_color_map(vis->size_room, vis->size_room, C_END);
	vis->map_score = crea_color_map(60, 200, C_SCORE);
	vis->map_visit = crea_color_map(vis->size_room - 5,vis->size_room - 5, C_VISIT);
	vis->img_room = mlx_xpm_to_image(vis->mlx_ptr, vis->map_room, &a, &b);
	vis->img_start = mlx_xpm_to_image(vis->mlx_ptr, vis->map_start, &a, &b);
	vis->img_end = mlx_xpm_to_image(vis->mlx_ptr, vis->map_end, &a, &b);
	vis->img_score = mlx_xpm_to_image(vis->mlx_ptr, vis->map_score, &a, &b);
	vis->img_visit = mlx_xpm_to_image(vis->mlx_ptr, vis->map_visit, &a, &b);
	delete_arr(vis->map_room);
	delete_arr(vis->map_visit);
	delete_arr(vis->map_start);
	delete_arr(vis->map_end);
	init_back(vis);
	return (vis);
}

/*
** Check link node.
*/

int		check_link_node(char *line)
{
	while (*line != '\0' && *line != 'L')
	{
		if (*line == '-')
			return (1);
		line++;
	}
	return (0);
}

void	print_link(t_link *link)
{
	while (link != NULL)
	{
		ft_printf("link [%s]\n", link->name);
		link = link->next;
	}
}

void	delete_link(t_link **link)
{
	t_link	*temp;

	temp = *link;
	while (*link != NULL)
	{
		*link = (*link)->next;
		free(temp->name);
		free(temp);
		temp = *link;
	}
	*link = NULL;
}

int		check_octotopr(t_vis *vis, char **line)
{
	if (ft_strcmp("##start", *line) == 0)
	{
		ft_strdel(line);
		get_next_line(0, line);
		ft_strncpy(vis->nstart, *line, ft_strcl(*line, ' '));
		ft_printf("start {%s}\n", vis->nstart);
	}
	else	if (ft_strcmp("##end", *line) == 0)
	{
		ft_strdel(line);
		get_next_line(0, line);
		ft_strncpy(vis->nend, *line, ft_strcl(*line, ' '));
		ft_printf("end {%s}\n", vis->nend);
	}
		return (1);
	return (0);
}

void	print_error(t_vis *vis)
{
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_error, 0, 0);
	sleep(3);
	sys_err("Error file\n");
}

int		read_map(t_vis *vis)
{
	char	*line;

	line = NULL;
	while(get_next_line(0, &line))
	{
		if (!vis->count_ant)
			vis->count_ant = ft_atoi(line);
		check_octotopr(vis, &line);
		if (!ft_strcmp("ERROR", line))
			print_error(vis);
		else	if (check_name_node(line))
		{
			ft_putendl(line);
			vis->node = add_node(vis->node, &line);
		}
		else	if (check_link_node(line))
			add_list_link(&vis->link, line);
		else	if (*line == 'L')
			add_list_link(&vis->step, line);
		ft_strdel(&line);
	}
	print_link(vis->link);	
	print_link(vis->step);	
	//delete_link(&vis->link);
	//delete_link(&vis->step);
	ft_strdel(&line);
	//delete_node(vis->node);
	//exit(0);
	return (0);
}

/*
** If pressed key esc close programm.
*/

int		exit_key(int key)
{
	if (key == 65307)
		sys_err("Normal exit.\n");
	return (0);
}

void	next_step(t_link **step)
{
	t_link *temp;

	temp = *step;
	*step = (*step)->next;
	free(temp->name);
	free(temp);
	
}

void	print_rooms(t_vis *vis)
{
	t_node	*node;

	node = vis->node;
	while (node != NULL)
	{
		mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_room,
				node->coor_x, node->coor_y);
		if (ft_strcmp(node->name, vis->nstart) == 0)
		mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_start,
				node->coor_x, node->coor_y);
		else	if (ft_strcmp(node->name, vis->nend) == 0)
		mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_end,
				node->coor_x, node->coor_y);
	mlx_string_put(vis->mlx_ptr, vis->win_ptr,
			node->coor_x, node->coor_y, 0x000000, node->name);
		node = node->next;
	}
}

void	swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_draw_line(void *mlx_ptr, void *win_ptr, t_point point1, t_point point2)
{
	t_point delta;
	t_point	sign;
	int		error;
	int		error2;

	delta.x = ABS((point2.x - point1.x));
	delta.y = ABS((point2.y - point1.y));
	sign.x = (point1.x < point2.x) ? 1 : -1;
	sign.y = (point1.y < point2.y) ? 1 : -1;
	error = delta.x - delta.y;
	mlx_pixel_put(mlx_ptr, win_ptr, point2.x, point2.y, 0xBF2956);
	while(point1.x != point2.x || point1.y != point2.y)
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

void	put_line(t_vis *vis, int x0, int y0, int x1, int y1)
{
	t_point	point1;
	t_point	point2;

	point1.x = x0;
	point1.y = y0;
	point2.x = x1;
	point2.y = y1;
	ft_draw_line(vis->mlx_ptr, vis->win_ptr, point1, point2);
}

char	*first_name(t_link *link)
{
	char	*name;
	size_t	len;

	len = ft_strcl(link->name, '-');
	name = ft_strnew(len);
	ft_strncpy(name, link->name, len); 
	return (name);
}

char	*second_name(t_link *link)
{
	char	*name;
	size_t	len;

	len = ft_strcl(link->name, '-');
	return (link->name + len + 1);
}

t_coor	*remove_coor(t_vis *vis, char *temp)
{
	t_coor	*coor;
	t_node	*node;

	if(!(coor = (t_coor *)malloc(sizeof(t_coor))))
		sys_err("Error malloc\n");
	coor->x = 0;
	coor->y = 0;
	node = search_node(vis->node, temp);
	coor->x = node->coor_x;
	coor->y = node->coor_y;
	return (coor);
}

void	put_edges(t_vis *vis)
{
	char	*temp;
	t_link	*link;
	t_coor	*start;
	t_coor	*end;
	
	while (vis->link != NULL)
	{
		temp = first_name(vis->link);
		start = remove_coor(vis, temp);
		ft_strdel(&temp);
		temp = second_name(vis->link);	
		end = remove_coor(vis, temp);
		put_line(vis, start->x + CENTR, start->y + CENTR,
				end->x + CENTR, end->y + CENTR);
		free(start);
		free(end);
		link = vis->link;
		vis->link = vis->link->next;
		free(link);
	}
}

void	print_visit(t_vis *vis, char *str_num, char *name_room)
{
	t_node *node;

	ft_printf("name_room = {%s}, str_num = {%s}\n", name_room, str_num);
	if (!(node = search_node(vis->node, name_room)))
	{
		ft_putendl("!!!not room!!!!");
		return ;
	}
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_visit,
			node->coor_x + 3, node->coor_y + 2);
	mlx_string_put(vis->mlx_ptr, vis->win_ptr,
			node->coor_x + 10, node->coor_y + 20, 0x000000, str_num);
}

void	rectengle_visit(t_vis *vis, char **arr)
{
	int		num;
	char	*str_num;
	char	*name_room;

	num = 0;
	while (*arr != NULL)
	{
		num = ft_atoi(*(arr) + 1);
		ft_printf("num = %d\n", num);
		str_num = ft_itoa(num);
		ft_printf("str_num = %s\n", str_num);
		name_room = return_name_node(*arr);
		print_visit(vis, str_num, name_room);	
		ft_strdel(&str_num);
		arr++;
	}
}

/*
** Print rectangle in down whith scores.
*/

void	print_score(t_vis *vis)
{
	static int	steps = 0;
	char		*str;

	str = ft_itoa(steps);
	steps++;
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_score, 1040, 660);
	mlx_string_put(vis->mlx_ptr, vis->win_ptr, 1100, 710, 0xBF2956,
		"Steps:");
	mlx_string_put(vis->mlx_ptr, vis->win_ptr, 1180, 710, 0xBF2956,
		str);
	str = ft_itoa(vis->count_ant);
	mlx_string_put(vis->mlx_ptr, vis->win_ptr, 1100, 685, 0xBF2956,
		"Count ants:");
	mlx_string_put(vis->mlx_ptr, vis->win_ptr, 1180, 685, 0xBF2956,
		str);
	free(str);
}

int		print_steps(t_vis *vis)
{
	char **arr;

	if (vis->step == NULL)
		return (0);
	ft_putendl("new step");
	print_score(vis);
	sleep(1);
	print_rooms(vis);
	arr = ft_strsplit(vis->step->name, ' ');
	next_step(&vis->step);
	rectengle_visit(vis, arr);
	print_arr(arr);
	delete_arr(arr);
	return (0);
}

int		main(void)
{
	t_vis	*vis;
	
	if(!(vis = create_vis()))
		exit(0);
	read_map(vis);
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_back, 0, 0);
	put_edges(vis);
	print_score(vis);
	print_rooms(vis);
	//print_arr(vis->room);
	mlx_key_hook(vis->win_ptr, exit_key, (void*)0);
	mlx_loop_hook(vis->mlx_ptr, print_steps, vis);
	mlx_loop(vis->mlx_ptr);
	return (0);
}
