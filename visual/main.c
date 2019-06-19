
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
	if (!(new->name = (char *)malloc(sizeof(char) * len)))
		sys_err("Error malloc.\n");
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
		//sleep(1);
		arr++;
	}
}

void	visual(t_node *node, t_vis *vis)
{
	char	*line;
	char	**arr;

	line = NULL;
	ft_putendl("B");
	while(get_next_line(0, &line))
	{
		ft_putendl(line);
		arr = ft_strsplit(line, ' ');
		input_room(node, vis, arr);
		print_arr(arr);
		delete_arr(arr);
		ft_strdel(&line);
	}
	ft_putendl("C");
	print_node(node);
	delete_node(node);
	//exit(0);
}

char	**crea_color_map(int heith, int width, const char *color)
{
	char	**map;
	int		i;
	int		j;

	map = (char **)malloc(sizeof(char *) * (heith + 3));
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
	vis->size_room = 20;
	vis->count_ant = 0;
	vis->map_room = NULL;
	vis->img_room = NULL;
}

/*
** Init background and menu.
*/

int		init_back(t_vis *vis)
{
	if(!(vis->img_back = mlx_xpm_file_to_image(vis->mlx_ptr,
			IMGPATH, &vis->heith, &vis->width)))
	{
		write(2, "Error image background.\n", 24);
		return (0);
	}
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
	vis->img_room = mlx_xpm_to_image(vis->mlx_ptr,vis->map_room, &a, &b);
	delete_arr(vis->map_room);
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

int		read_map(t_vis *vis)
{
	char	*line;

	line = NULL;
	while(get_next_line(0, &line))
	{
		if (!ft_strcmp("ERROR", line))
			sys_err("ERROR\n");
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
		exit(0);
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
				node->coor_x * 50, node->coor_y * 80);
		node = node->next;
	}
}

void	print_edges(t_vis *vis)
{
	sdf
}

int		print_steps(t_vis *vis)
{
	char **arr;

	if (vis->step == NULL)
		return (0);
	ft_putendl("new step");
	arr = ft_strsplit(vis->step->name, ' ');
	next_step(&vis->step);
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
	print_rooms(vis);
	print_edges(vis);
	//print_arr(vis->room);
	mlx_key_hook(vis->win_ptr, exit_key, (void*)0);
	mlx_loop_hook(vis->mlx_ptr, print_steps, vis);
	mlx_loop(vis->mlx_ptr);
	return (0);
}
