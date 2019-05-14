#include "lem.h"

/*
** If there is error. Shut down the program.
*/

void	sys_err(char *err)
{
	write(2, err, ft_strlen(err));
	exit(0);
}

/*
** Check name node.
** Check symbol octothorpe.
** For search comments, start or end.
*/

int		check_name_octothorpe(char *line)
{
	int space;

	space = 0;
	if (!ft_strncmp("##", line, 2))
		return (1);
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
** Check link node.
*/

int		check_link_node(char *line)
{
	while (*line != '\0')
	{
		if (*line == '-')
			return (1);
		line++;
	}
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

/*
** Create new node.
*/

t_node	*new_node(char *line)
{
	t_node *new;

	if (!(new = (t_node *)malloc(sizeof(t_node))))
		sys_err("Error malloc");
	new->coor_x = 0;
	new->coor_y = 0;
	new->bl = 0;
	new->level = -1;
	new->next = NULL;
	new->edg = NULL;
	infill_node(new, line);
	return (new);
}

/*
** Serch node by name.
*/

t_node *search_node(t_node *node, char *name)
{
	while (node)
	{
		if (ft_strcmp(node->name, name) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

/*
** Print edges.
*/

void	print_edges(t_nlst *edg)
{
	while (edg)
	{
		ft_printf("Edges name = %s\n", edg->name_edg);
		edg = edg->next;
	}
}

/*
** Print list. For test.
*/

void	print_list(t_node *node)
{
	while (node)
	{
		ft_printf("name = %s, x = %d, y = %d\n",
			node->name, node->coor_x, node->coor_y);
		print_edges(node->edg);
		node = node->next;
	}
}

/*
** Create new list for edges and(or) queue.
*/

t_nlst	*creat_new_lst(char *name)
{
	t_nlst *new;
	size_t len;

	len = ft_strlen(name);
	if (!(new = (t_nlst *)malloc(sizeof(t_nlst))))
		sys_err("Error malloc.\n");
	ft_strncpy(new->name_edg, name, len);
	new->name_edg[len] = '\0';
	new->next = NULL;
	return (new);
}

/*
** Add new list name edgess.
*/

void	add_new_edges(t_nlst **nlst, char *name)
{
	t_nlst *first;
	t_nlst *new_esg;

	first = *nlst;
	if (!first)
	{
		*nlst= creat_new_lst(name);
		return ;
	}
	while (first->next != NULL)
		first = first->next;
	new_esg = creat_new_lst(name);
	first->next = new_esg;
}

/*
** Init queue.
*/

t_queue	*init_queue()
{
	t_queue *queue;

	if (!(queue = (t_queue *)malloc(sizeof(t_queue))))
		sys_err("Error malloc\n");
	queue->first = NULL;
	queue->end = NULL;
	return (queue);
}

/*
** Insert new list into queue.
*/

void	insert(t_queue *queue, char *name)
{
	t_nlst  *new;
	t_nlst  *iter;

	new = NULL;
	iter = queue->end;
	if (queue->first == NULL && queue->first == NULL)
	{
		queue->first = creat_new_lst(name);
		queue->end = queue->first;
	}
	else
	{
		new = creat_new_lst(name);
		iter->next = new;
		queue->end = new;
	}
}

int		isempty_queue(t_queue *que)
{
	if (que->first == NULL)
		return (1);
	else
		return (0);
}

/*
** Remove first elemet of list. And return first elem.
*/

char	*remove_first(t_queue *que)
{
	t_nlst	*iter;
	char	*name;

	if (isempty_queue(que))
	{
		que->end = NULL;
		return (NULL);
	}
	iter = que->first;
	que->first = que->first->next;
	iter->next = NULL;
	name = ft_strdup(iter->name_edg);
	free(iter);
	return (name);
}

/*
** Create edges.
*/

void	create_edges(t_node *node, char *line)
{
	size_t	len;
	char	*fir_name;
	t_node	*temp;

	len = ft_strcl(line, '-');
	fir_name = ft_strnew(len + 1);
	fir_name = ft_strncpy(fir_name, line, len);
	temp = search_node(node, fir_name);
	add_new_edges(&temp->edg, (line + len + 1));
	temp = search_node(node, line + len + 1);
	add_new_edges(&temp->edg, fir_name);
	//ft_printf("fir_name = %s\n", fir->name);
	//ft_printf("sec_name = %s\n", sec->name);
	ft_strdel(&fir_name);
}


/*
** Copy name. For queue start and queue end.
*/

void	copy_name(char *name, char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0' && line[i] != ' ')
	{
		name[i] = line[i];
		i++;
	}
	name[i] = '\0';
}

/*
** Add new node in to list.
** Ceack liks. Line???
*/

t_node	*add_node(t_node *node, t_queue *que, char **line)
{
	t_node	*n_node;
	t_node	*first;

	first = node;
	if (!ft_strncmp("##start", *line, 7))
	{
		ft_strdel(line);
		get_next_line(0, line);
		ft_putendl(*line);
		copy_name(que->name_start, *line);
		ft_printf("Start name = %s\n", que->name_start);
	}
	else	if (!ft_strncmp("##end", *line, 5))
	{
		ft_strdel(line);
		get_next_line(0, line);
		ft_putendl(*line);
		copy_name(que->name_end, *line);
		ft_printf("End name = %s\n", que->name_end);
	}
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
** Breadth-first search.
*/

void	breadth_irst_search(t_node *node, t_queue *que)
{
	t_node	*cur_node;
	t_nlst	*edg_lst;
	char	*name;
	int		i;

	insert(que, que->name_start);
	i = 0;
	while (!isempty_queue(que))
	{
		name = remove_first(que);
		cur_node = search_node(node, name);
		i = ++cur_node->level;
		ft_printf("Remove %s Level %d\n", name, cur_node->level);
		edg_lst = cur_node->edg;
		if (!ft_strcmp(name, que->name_end))
		{
			ft_printf("Finish %s\n", name);
			return ;
		}
		cur_node->bl = 1;
		while (edg_lst != NULL)
		{
			cur_node = search_node(node, edg_lst->name_edg);
			cur_node->level = i;
			if (cur_node->bl == 0)
			{
				insert(que, edg_lst->name_edg);
				ft_printf("Insert %s\n", edg_lst->name_edg);
			}
			edg_lst = edg_lst->next;
		}
		free(name);
	}
}

/*
** Read map.
*/

void	read_map(void)
{
	char	*line;
	t_node	*node;
	t_queue	*que;
	//int		fd;

	line = NULL;
	node = NULL;
	//fd = open("map1", O_RDONLY);
	que = init_queue();
	while(get_next_line(0, &line))
	{
		ft_printf("%s\n", line);
		if (check_name_octothorpe(line))
			node = add_node(node, que, &line);
		else	if (check_link_node(line))
			create_edges(node, line);
		ft_strdel(&line);
	}
	//print_list(node);
	breadth_irst_search(node, que);
}

int		main(void)
{
	t_queue *que;
	char	*lst;

	que = NULL;
	que = init_queue();
	insert(que, "1");
	insert(que, "2");
	insert(que, "3");
	insert(que, "4");
	insert(que, "5");
	print_edges(que->first);
	ft_printf("fitst = %s, end = %s\n", que->first, que->end);
	lst = remove_first(que);
	free(lst);
	lst = remove_first(que);
	free(lst);
	lst = remove_first(que);
	free(lst);
	lst = remove_first(que);
	free(lst);
	print_edges(que->first);
	ft_printf("fitst = %s, end = %s\n", que->first, que->end);
	insert(que, "6");
	insert(que, "7");
	print_edges(que->first);
	ft_printf("fitst = %s, end = %s\n", que->first, que->end);
	lst = remove_first(que);
	free(lst);
	print_edges(que->first);
	ft_printf("fitst = %s, end = %s\n", que->first, que->end);
	read_map();
	return (0);
}
