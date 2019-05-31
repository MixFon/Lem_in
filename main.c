/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 10:18:25 by widraugr          #+#    #+#             */
/*   Updated: 2019/05/31 18:09:15 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	new->mark_bfs = 0;
	new->dfs_mark = 0;
	new->level = 0;
	new->weight = 0;
	new->next = NULL;
	new->edg = NULL;
	infill_node(new, line);
	return (new);
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
** Print list. 
** For test.
*/

void	print_node(t_node *node)
{
	while (node)
	{
		ft_printf("name = %s, x = %d, y = %d level  = %d weight = %d\n",
			node->name, node->coor_x, node->coor_y, node->level, node->weight);
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
	new->sum_ant = 0;
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

t_queue	*init_queue(void)
{
	t_queue *queue;

	if (!(queue = (t_queue *)malloc(sizeof(t_queue))))
		sys_err("Error malloc\n");
	queue->first = NULL;
	queue->end = NULL;
	queue->sum = 0;
	return (queue);
}

/*
** Insert new list into front queue.
*/

void	insert_front(t_queue *queue, char *name)
{
	t_nlst  *new;
	t_nlst  *iter;

	new = NULL;
	iter = queue->first;
	if (queue->first == NULL && queue->first == NULL)
	{
		queue->first = creat_new_lst(name);
		queue->end = queue->first;
	}
	else
	{
		new = creat_new_lst(name);
		new->next = iter;
		queue->first = new;
	}
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
	return (que->first == NULL ? 1 : 0);
}

/*
** Remove last elemet of list. And return name of last element.
*/

void	remove_last(t_queue *que, int count_ways)
{
	t_nlst	*iter;
	t_nlst	*temp;
	int		i;

	i = 0;
	while (i < count_ways)
	{
		if (isempty_queue(que))
		{
			ft_putendl("Queue empty");
			que->end = NULL;
			return ;
		}
		iter = que->first;
		temp = que->end;
		if (iter == temp)
		{
			//free(temp);
			temp = NULL;
			return ;
		}
		while (iter->next != temp)
			iter = iter->next;
		que->end = iter;
		que->end->next = NULL;
		free(temp);
		i++;
	}

}


/*
** Remove first elemet of list. And return name of first element.
*/

char	*remove_first(t_queue *que, int count_ways)
{
	t_nlst	*iter;
	char	*name;
	int		i;

	i = 0;
	while (i < count_ways)
	{
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
		i++;
	}
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

t_node	*add_node(t_node *node, t_ant *ant, char **line)
{
	t_node	*n_node;
	t_node	*first;

	first = node;
	if (!ft_strncmp("##start", *line, 7))
	{
		ft_strdel(line);
		get_next_line(0, line);
		ft_putendl(*line);
		copy_name(ant->name_start, *line);
		ft_printf("Start name = %s\n", ant->name_start);
	}
	else	if (!ft_strncmp("##end", *line, 5))
	{
		ft_strdel(line);
		get_next_line(0, line);
		ft_putendl(*line);
		copy_name(ant->name_end, *line);
		ft_printf("End name = %s\n", ant->name_end);
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
** Cheack of a short path.
*/

int		cheack_short_path(t_node *node, t_ant *ant)
{
	t_node	*cur_node;
	t_nlst	*iter;
	int		s_lvl;

	cur_node = search_node(node, ant->name_end);
	iter = cur_node->edg;
	s_lvl = cur_node->level;
	while (iter)
	{
		cur_node = search_node(node, iter->name_edg);
		if (cur_node->level == s_lvl - 1 && cur_node->dfs_mark == 0)
			return (1);
		iter = iter->next;
	}
	return (0);
}

/*
** Add new list of way.
*/

void	short_ways(t_node *node, t_ant *ant)
{
	t_ways *iter;

	while (cheack_short_path(node, ant))
	{
		if (ant->ways == NULL)
		{
			ant->ways = create_short_way(node, ant);
			ant->count_ways++;
			continue ;
		}
		iter = create_short_way(node, ant);
		ant->count_ways++;
		iter->next = ant->ways->next;
		ant->ways->next = iter;
	}
}
/*
** Breadth-first search.
*/

void	breadth_first_search(t_node *node, t_ant *ant)
{
	t_node	*cur_node;
	t_nlst	*edg_lst;
	char	*name;
	int		i;
	int		max_weid;
	int		weight;

	i = 0;
	weight = 0;
	max_weid = 0;
	insert(ant->que, ant->name_start);
	while (!isempty_queue(ant->que))
	{
		name = remove_first(ant->que, 1);
		cur_node = search_node(node, name);
		ft_printf("Remove %s Level %d\n", name, cur_node->level);
		if (!ft_strcmp(name, ant->name_end))
		{
			ft_printf("Finish %s\n", name);
			ant->lvl = cur_node->level;
			return ;
		}
		edg_lst = cur_node->edg;
		i = cur_node->level;
		weight = cur_node->weight;
		cur_node->mark_bfs = 1;
		while (edg_lst != NULL)
		{
			cur_node = search_node(node, edg_lst->name_edg);
			cur_node->weight += weight;
			if (cur_node->weight > max_weid)
			{
				max_weid = cur_node->weight;
				ft_strcpy(ant->nmax_weid, cur_node->name);
			}
			if (cur_node->mark_bfs == 0)
			{
				insert(ant->que, edg_lst->name_edg);
				cur_node->mark_bfs = 1;
				//cur_node->level++;
				cur_node->level = i + 1;
				ft_printf("Insert %s\n", edg_lst->name_edg);
			}
			edg_lst = edg_lst->next;
		}
		free(name);
	}
}

void	add_new_nlst(t_nlst **sol, char *name)
{
	t_nlst	*iter;

	iter = creat_new_lst(name);
	iter->next = *sol;
	*sol = iter;
}

/*
** Depth-first search.
** Create list short path.
*/

t_ways	*create_new_way(void)
{
	t_ways *way;

	if(!(way = (t_ways *)malloc(sizeof(t_ways))))
		sys_err("Error malloc\n");
	way->way = NULL;;
	way->len_way = 1;
	way->next = NULL;
	return (way);
}

/*
** Depth-first search.
** Create list short path.
*/

t_ways	*create_short_way(t_node *node, t_ant *ant)
{
	t_node	*cur_node;
	t_nlst	*lst;
	t_ways	*iter;
	char	*name;
	int		s_lvl;

	iter = create_new_way();
	iter->way = creat_new_lst(ant->name_end);
	ft_printf("Name start stack '%s'\n", ant->name_end);
	while (iter->way != NULL)
	{
		name = iter->way->name_edg;
		cur_node = search_node(node, name);
		cur_node->dfs_mark = 1;
		s_lvl = cur_node->level;
		ft_printf("%s level %d\n",name, s_lvl);
		lst = cur_node->edg;
		while (lst)
		{
			name = lst->name_edg;
			cur_node = search_node(node, name);
			ft_printf("cha %s level %d\n", name, cur_node->level);
			if (!ft_strcmp(name, ant->name_start))
			{
				ft_printf("Find! %s\n", name);
				ft_printf("Path\n");
				ft_printf("len_way %d\n", iter->len_way);
				add_new_nlst(&iter->way, name);
				print_edges(iter->way);
				cur_node->dfs_mark = 1;
			//	ant->ways = iter;
				return (iter) ;
			}
			else if (cur_node->level == s_lvl - 1 && cur_node->dfs_mark == 0)
			{
				add_new_nlst(&iter->way, name);
				iter->len_way++;
				ft_printf("Push to list way %s\n", name);
				break ;
			}
			lst = lst->next;
		}
		//print_stack(ant->stack->first);
	}
	return (NULL);
}

/*
** Init struct ant.
*/

t_ant	*init_ant(void)
{
	t_ant	*new;

	if(!(new = (t_ant*)malloc(sizeof(t_ant))))
		sys_err("Error malloc\n");
	new->que = init_queue();
	//new->stack = init_stack();
	//new->short_way = NULL;
	new->ways = NULL;
	new->lvl = 0;
	new->count_ant = 0;
	new->count_ways = 0;
	return (new);
}

/*
** Print ant in room.
*/

void	print_ant_room(t_nlst *nlst, int ant_path, int count_ways)
{
	t_nlst	*iter;
	int		ant;
	static int	bl = 0;
	static int	i = 0;

	ant = 1;
	iter = nlst;
	while (iter)
	{
		iter->sum_ant = ant + i;
		if (ant == ant_path)
			bl = 1;
		ant++;
		if (iter == iter->next)
			break ;
		iter = iter->next;
	}
	if (bl == 1)
		i += count_ways;
	iter = nlst;
	while (iter != NULL)
	{
		ft_printf("L%d-%s ", iter->sum_ant, iter->name_edg);
		if (iter == iter->next)
		{
			ft_putchar('\n');
			return ;
		}
		iter = iter->next;
	}
	ft_putchar('\n');
}

int		ft_lstlen(t_nlst *nlst)
{
	int		i;
	t_nlst	*iter;

	i = 0;
	iter = nlst;
	while (iter)
	{
		i++;
		iter = iter->next;
	}
	return (i);
}

/*
** Admission room of name start.
*/

void	admission_name_start(t_ant *ant)
{
	t_ways	*ways;
	t_nlst	*nlst;

	ways = ant->ways;
	while (ways != NULL)
	{
		nlst = ways->way;
		if (nlst == NULL)
			continue ;
		ways->way = ways->way->next;
		free(nlst);
		ways = ways->next;
	}
}

/*
** Insert queue.
*/

void	insert_queue(t_queue *que, t_ant *ant)
{
	t_ways	*ways;
	t_nlst	*nlst;
	
	ways = ant->ways;
	while (ways != NULL)
	{
		nlst = ways->way;
		if (nlst == NULL)
		{
			ways = ways->next;
			continue ;
		}
		insert_front(que, nlst->name_edg);
		ways->way = ways->way->next;
		free(nlst);
		ways = ways->next;
	}
}

/*
** Print solution.
*/

void	solution(t_ant *ant)
{
	t_queue	*que;
	//t_nlst	*nlst;
	int		cur_ant;
	int		i;
	int		lst_len;

	cur_ant = 1;
	i = 0;
	admission_name_start(ant);
	ft_printf("count_ant %d\n", ant->count_ant);
	ft_printf("count_ways %d\n", ant->count_ways);
	que = init_queue();
	lst_len = ant->ways->len_way;
	ft_printf("Len lst  %d\n", lst_len);
	insert_queue(que, ant);
	while (i < ant->ways->len_way + (ant->count_ant / ant->count_ways) - 1)
	{
		//ft_putendl("Hello");
		print_ant_room(que->first, ant->count_ways * lst_len, ant->count_ways);
		if (cur_ant < lst_len && cur_ant < ant->count_ant / ant->count_ways)
		{
			insert_queue(que, ant);
			//insert_front(que, nlst->name_edg);
			cur_ant++;
		}
		else if (cur_ant <= lst_len && lst_len > ant->count_ant / ant->count_ways)
		{
			//ft_putendl("Hello2");
			remove_first(que, ant->count_ways);
			//remove_last(que, ant->count_ways);
			insert_queue(que, ant);
			remove_last(que, ant->count_ways);
			//break ;
			//insert_front(que, nlst->name_edg);
		}
		if(i >= lst_len - 1 && i >= ant->count_ant / ant->count_ways - 1 &&
				lst_len <= ant->count_ant)
		{
			//ft_putendl("Hello3");
			remove_last(que, ant->count_ways);
		}
		else	if (i >= lst_len - 1 && lst_len > ant->count_ant)
		{
			//ft_putendl("Hello4");
			remove_first(que, ant->count_ways);
		}
		//break ;
		i++;
	}
}

/*
** Cheack short way.
*/
/*
void	cheack_short_way(t_ant *ant)
{
	int	len;

	len = ft_lstlen(ant->ways->way);
	if (ant->count_ant <= len)
		solution(ant);
}
*/

/*
** Defines the weight of the node.
*/

void	weight_node(t_node *node)
{
	t_node	*iter;

	iter = node;
	while (iter != NULL)
	{
		iter->weight = ft_lstlen(iter->edg);
		iter = iter->next;
	}
}

/*
** Check name in short list.
*/

int		check_name_short_way(char *name, t_ways *ways)
{
	t_ways	*iter;	
	t_nlst	*nlst;

	iter = ways;
	while (iter != NULL)
	{
		nlst = iter->way;			
		while (nlst != NULL)
		{
			if (!ft_strcmp(name, nlst->name_edg))
				return (1);
			nlst = nlst->next;
		}
		iter = iter->next;
	}
	return (0);
}	

/*
** Remove an edge from the list..
*/

void	delete_name_list(char *name, t_nlst *nlst)
{
	t_nlst	*iter;
	t_nlst	*pre;

	pre = nlst;
	iter = nlst->next;
	if (!ft_strcmp(name, nlst->name_edg))
	{
		nlst = nlst->next;
		ft_printf("Delete1 %s\n", pre->name_edg);
		free(pre);	
		return ;
	}
	while (iter != NULL)
	{
		if (!ft_strcmp(name, iter->name_edg))
		{
			pre->next  = iter->next;	
			ft_printf("Delete2 %s\n", iter->name_edg);
			free(iter);
			return ;
		}
		pre = pre->next;
		iter = iter->next;
	}
}

/*
** Remove an edge from the list..
*/

void	remove_edge(t_node *node, t_ant *ant)
{
	t_node	*max_node;
	t_node	*par_node;
	t_nlst	*nlst;

	max_node = search_node(node, ant->nmax_weid);
	nlst = max_node->edg;
	while (nlst != NULL)
	{
		par_node = search_node(node, nlst->name_edg);
		if (par_node->level == max_node->level - 1 &&
				check_name_short_way(nlst->name_edg, ant->ways))
		{
			delete_name_list(max_node->name, par_node->edg);
			delete_name_list(par_node->name, max_node->edg);
		}
		nlst = nlst->next;
	}
}

/*
** Insert bfs to zero.
*/

void	zeroing_bfs(t_node *node)
{
	t_node *cur_node;

	cur_node = node;
	while (cur_node != NULL)
	{
		cur_node->mark_bfs = 0;
		cur_node->dfs_mark = 0;
		cur_node->level = 0;
		cur_node->weight = 0;
		cur_node = cur_node->next;
	}
}

/*
** Read map.
*/

void	read_map(void)
{
	char	*line;
	t_node	*node;
	t_ant	*ant;
	//int		fd;

	line = NULL;
	node = NULL;
	//fd = open("map1", O_RDONLY);
	ant = init_ant();
	while(get_next_line(0, &line))
	{
		ft_printf("%s\n", line);
		if (ant->count_ant == 0)
			ant->count_ant = ft_atoi(line);
		if (check_name_octothorpe(line))
			node = add_node(node, ant, &line);
		else	if (check_link_node(line))
			create_edges(node, line);
		ft_strdel(&line);
	}
	//print_list(node);
	weight_node(node);
	breadth_first_search(node, ant);
	short_ways(node, ant);
	//ft_printf("!!!!!!!!!!!!!!!!!!!!!!Name max weidht %s\n", ant->nmax_weid);
	print_node(node);
	/*
	remove_edge(node, ant);	
	zeroing_bfs(node);
	weight_node(node);
	breadth_first_search(node, ant);
	short_ways(node, ant);
	print_node(node);
	*/
	solution(ant);
}

int		main(void)
{
	/*
	t_queue *que;

	que = init_queue();
	insert(que, "1");
	insert(que, "2");
	insert(que, "3");
	insert(que, "4");
	print_edges(que->first);
	remove_last(que);
	ft_putchar('\n');
	print_edges(que->first);
	*/
	read_map();
	return (0);
}
// ------------------------------------------------------------------------------
/*

void	print_stack(t_nlst *lst)
{
	//ft_printf("Stack:\n");
	while (lst)
	{
		ft_printf("%s ", lst->name_edg);
		lst = lst->next;
	}
	ft_printf("\n");
}


void	pop(t_stack *stack, t_node *node)
{
	t_nlst	*temp;
	t_node	*cur_node;

	temp = stack->first;
	stack->first = stack->first->next;
	temp->next = NULL;
	cur_node = search_node(node, temp->name_edg);
	cur_node->dfs_mark = 2;
	//name = ft_strdup(temp->name_edg);
	free(temp);
}

void	push(t_stack *stack, char *name)
{
	t_nlst *new_lst;
	t_nlst *temp;

	temp = stack->first;
	//stack->count++;
	if (stack->first == NULL)
		stack->first = creat_new_lst(name);
	else
	{
		new_lst = creat_new_lst(name);
		new_lst->next = temp;
		stack->first = new_lst;	
	}
}

int		isempty_stack(t_stack *stack)
{
	if (stack->first == NULL)
		return (1);
	else
		return (0);
}
*/
/*
** Init stack.
*/
/*
t_stack	*init_stack(void)
{
	t_stack *new;

	if (!(new = (t_stack*)malloc(sizeof(t_stack))))
		sys_err("Error malloc\n");
	new->first = NULL;
	return (new);
} 
*/
/*
** Copy solution list name.
*/
/*
void	copy_sol_list(t_ant *ant, t_nlst *first)
{
	t_nlst *temp;
	t_nlst *iter;

	iter = creat_new_lst(first->name_edg);
	first = first->next;
	while (first)
	{
		temp = creat_new_lst(first->name_edg);
		temp->next = iter;
		iter = temp;
		first = first->next;
	}
	ant->short_way = iter;
	ft_printf("Copy list!!!!\n");
	print_edges(ant->short_way);
}
*/
/*
void	depth_first_search(t_node *node, t_ant *ant)
{
	t_node	*cur_node;
	t_queue	*path;
	t_nlst	*lst;
	char	*name;
	int		s_lvl;

	push(ant->stack, ant->name_end);
	path = init_queue();
	insert(path, ant->name_end);
	ft_printf("Name start stack '%s'\n", ant->name_end);
	while (!isempty_stack(ant->stack))
	{
		name = ant->stack->first->name_edg;
		//ft_printf("Name first stack %s\n", name);
		cur_node = search_node(node, name);
		cur_node->dfs_mark = 1;
		s_lvl = cur_node->level;
		ft_printf("%s level %d\n",name, s_lvl);
		lst = cur_node->edg;
		while (lst)
		{
			name = lst->name_edg;
			cur_node = search_node(node, name);
			ft_printf("cha %s level %d\n", name, cur_node->level);
			if (!ft_strcmp(name, ant->name_start))
			{
				ft_printf("Find! %s\n", name);
				ft_printf("Path\n");
				insert(path, name);
				//copy_sol_list(ant, path->first);
				//print_edges(path->first);
				cur_node->dfs_mark = 1;
				remove_last(path);
				//return ;
			}
			else if (cur_node->level == s_lvl - 1 && cur_node->dfs_mark == 0)
			{
				push(ant->stack, name);
				insert(path, name);
				ant->stack->lvl++;
				//print_edges(path->first);
				ft_printf("Push to stack %s\n", name);
				break ;
			}
			lst = lst->next;
		}
		if (lst == NULL)
		{
			ft_printf("Remove %s\n", path->end->name_edg);
			remove_last(path);
			ant->stack->lvl--;
			pop(ant->stack, node);
		}
		print_stack(ant->stack->first);
	}
}
*/
