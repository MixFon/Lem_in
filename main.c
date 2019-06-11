/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 10:18:25 by widraugr          #+#    #+#             */
/*   Updated: 2019/06/11 15:40:15 by widraugr         ###   ########.fr       */
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
		ft_printf("name = %s,    level  = %d weight = %d\n",
			node->name, node->level, node->weight);
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
	t_node	*cur_node;

	len = ft_strcl(line, '-');
	fir_name = ft_strnew(len + 1);
	fir_name = ft_strncpy(fir_name, line, len);
	cur_node = search_node(node, fir_name);
	add_new_edges(&cur_node->edg, (line + len + 1));
	cur_node = search_node(node, line + len + 1);
	add_new_edges(&cur_node->edg, fir_name);
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
** Проверяет есть ли еще один котороткий путь. 
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
		if (cur_node->dfs_mark == 0)
			return (1);
		iter = iter->next;
	}
	return (0);
}

/*
** Add new list of way.
** Пока есть короткие пути, создаем новый лист с именами пути. 
** После создания коротких путей добавляем в конец имя конца пути.
** Особеность реализации.
*/

int		short_ways(t_node *node, t_ant *ant)
{
	t_ways *iter;

	while (cheack_short_path(node, ant))
	{
		if (ant->ways == NULL)
		{
			if(!(ant->ways = create_short_way(node, ant)))
			{
				ant->count_ways++;
				ant->pre_steps = 1;
				ant->bl = 0;
				return (1) ;
			}
			ant->count_ways++;
			continue ;
		}
		if(!(iter = create_way(node, ant)))
			return (0) ;
		ant->count_ways++;
		iter->next = ant->ways->next;
		ant->ways->next = iter;
		iter->prev = ant->ways;
		if (iter->next != NULL)
			iter->next->prev = iter;
	}
	return (0);
}

/*
** Удаляет весь лист.
*/

void	delete_all_list(t_nlst **lst)
{
	t_nlst	*iter;
	t_nlst	*pre;

	iter = *lst;
	pre = iter;
	while (iter != NULL)
	{
		iter = iter->next;
		free(pre);
		pre = iter;
	}
	*lst = NULL;
}

/*
** Breadth-first search.
*/

void	iter_to_edg_lst(t_node *node, t_ant *ant, t_node *cur_node)
{
	int		i;
	int		weight;
	t_nlst	*edg_lst;

	edg_lst = cur_node->edg;
	i = cur_node->level;
	weight = cur_node->weight;
	cur_node->mark_bfs = 1;
	while (edg_lst != NULL)
	{
		cur_node = search_node(node, edg_lst->name_edg);
		cur_node->weight += weight;
		if (cur_node->mark_bfs == 0)
		{
			insert(ant->que, edg_lst->name_edg);
			cur_node->mark_bfs = 1;
			cur_node->level = i + 1;
		}
		edg_lst = edg_lst->next;
	}
}

/*
** Breadth-first search.
*/

void	breadth_first_search(t_node *node, t_ant *ant)
{
	t_node	*cur_node;
	char	*name;

	insert(ant->que, ant->name_start);
	while (!isempty_queue(ant->que))
	{
		name = remove_first(ant->que, 1);
		cur_node = search_node(node, name);
		if (!ft_strcmp(name, ant->name_end))
		{
			ant->lvl = cur_node->level;
			delete_all_list(&ant->que->first);
			return ;
		}
		iter_to_edg_lst(node, ant, cur_node);
		free(name);
	}
}

void	add_new_nlst(t_nlst **way, char *name)
{
	t_nlst	*iter;

	iter = creat_new_lst(name);
	iter->next = *way;
	*way = iter;
}

/*
** Create new way for short path.
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
	way->prev = NULL;
	way->iter = NULL;
	return (way);
}

/*
** Delete one list in way.
*/

void	delete_list(t_nlst **way)
{
	t_nlst	*iter;

	iter = *way;
	if (!iter)
		return ;
	*way = (*way)->next;
	iter->next = NULL;
	free(iter);
}
/*
int		iter_to_lst(t_node *node, t_ant *ant, t_node *cur_node, t_ways *iter)
{
	return (0);
}
*/

void	node_is_visited(t_nlst *lst, t_ways *iter, t_node *cur_node)
{
	if (lst == NULL)
	{
		iter->len_way--;
		cur_node->dfs_mark = 1;
		delete_list(&iter->way);
	}
}

int		part(t_node *node, t_nlst *lst, t_ways *iter, t_ant *ant)
{
	char	*name;
	t_node	*cur_node;

	name = lst->name_edg;
	cur_node = search_node(node, name);
	if (!ft_strcmp(name, ant->name_start))
	{
		add_new_nlst(&iter->way, name);
		cur_node->dfs_mark = 1;
		return (1);
	}
	else if (cur_node->level == ant->s_lvl - 1 && cur_node->dfs_mark == 0)
	{
		add_new_nlst(&iter->way, name);
		iter->len_way++;
		cur_node->dfs_mark = 1;
		return (2);
	}
	return (0);
}
/////////////////////////////////////////////////////////////////////////////////////////////
/*
** Create list only short way.
*/

t_ways	*create_short_way(t_node *node, t_ant *ant)
{
	t_node	*cur_node;
	t_ways	*iter;
	char	*name;
	int		bl;
	t_nlst	*lst;

	iter = create_new_way();
	iter->way = creat_new_lst(ant->name_end);
	while (iter->way != NULL)
	{
		name = iter->way->name_edg;
		cur_node = search_node(node, name);
		cur_node->dfs_mark = 1;
		ant->s_lvl = cur_node->level;
		lst = cur_node->edg;
		while (lst != NULL)
		{
			bl = part(node, lst, iter, ant);
			if (bl == 1)
				return (iter);
			else	if (bl == 2)
				break;
			lst = lst->next;
		}
		node_is_visited(lst, iter, cur_node);
	}
	return (NULL);
}

/*
** Depth-first search.
** Create list short path.
*/

t_ways	*create_way(t_node *node, t_ant *ant)
{
	t_node	*cur_node;
	t_nlst	*lst;
	t_ways	*iter;
	char	*name;
	int		s_lvl;
	int a = 0;

	iter = create_new_way();
	iter->way = creat_new_lst(ant->name_end);
	while (iter->way != NULL)
	{
		name = iter->way->name_edg;
		cur_node = search_node(node, name);
		cur_node->dfs_mark = 1;
		s_lvl = cur_node->level;
		lst = cur_node->edg;
		a++;
		while (lst)
		{
			name = lst->name_edg;
			cur_node = search_node(node, name);
			if (!ft_strcmp(name, ant->name_start))
			{
				if (a == 1)
				{
					lst = lst->next;
					continue ;
				}
				add_new_nlst(&iter->way, name);
				cur_node->dfs_mark = 1;
				return (iter);
			}
			else if (cur_node->level == s_lvl - 1 && cur_node->dfs_mark == 0)
			{
				add_new_nlst(&iter->way, name);
				iter->len_way++;
				cur_node->dfs_mark = 1;
				break ;
			}
			else if (cur_node->dfs_mark == 0)
			{
				add_new_nlst(&iter->way, name);
				iter->len_way++;
				cur_node->dfs_mark = 1;
				break ;
			}
			lst = lst->next;
		}
		if (lst == NULL)
		{
			iter->len_way--;
			cur_node->dfs_mark = 1;
			delete_list(&iter->way);
		}
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
	new->pre_steps = 0;
	new->all_steps = 0;
	new->bl = 0;
	new->max_count_way = 0;
	new->s_lvl = 0;
	new->count_ways = 0;
	return (new);
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
	while (ways->next)
		ways = ways->next;
	while (ways != NULL)
	{
		nlst = ways->way;
		if (nlst == NULL)
		{
			ways = ways->prev;
			continue ;
		}
		insert_front(que, nlst->name_edg);
		ways->way = ways->way->next;
		free(nlst);
		ways = ways->prev;
	}
}
void	cheack_remove(t_ant *ant, t_queue *que, int i)
{
	t_ways *ways;

	ways = ant->ways;
	while (ways != NULL)
	{
		if (i >= ant->cur_steps - ways->len_way)
			remove_last(que, 1);
		ways = ways->next;
	}
}

void	create_print_list(t_nlst *pant, t_ant *ant, int i)
{
	t_nlst	**pant_it;
	t_nlst	*iter;
	int		miss;
	int		j;
	int		b;

	b = 0;
	pant->next = NULL;
	pant_it = &pant;
	miss = i / ant->count_ways;
	while (miss > 0)
	{
	//	ft_putendl("Hello");
		add_new_edges(pant_it, "\0");
		b++;
		miss--;
	}
	if (ant->ways->iter == NULL)
		ant->ways->iter = ant->ways;
	iter = ant->ways->iter->way;
	while (iter != NULL)
	{
		add_new_edges(pant_it, iter->name_edg);
		iter = iter->next;
		b++;
	}
	j = ant->cur_steps - b + 2;
	while (--j > 0)
		add_new_edges(pant_it, "\0");
	//print_edges(pant->next);
	ant->ways->iter = ant->ways->iter->next;

}

/*
** Print solution.
*/

void	solution(t_ant *ant)
{
	int				i;
	int				j;
	static t_nlst	*temp;
	t_nlst			pant[ant->count_ant];

	i = -1;
	admission_name_start(ant);
	while (++i < ant->count_ant)
		create_print_list(&pant[i], ant, i);
	j = 0;
	ft_printf("ant->count_ant  %d\n", ant->cur_steps);
	while (j <  ant->cur_steps + 1)
	{
		i = -1;
		while (++i < ant->count_ant)
		{
			temp = &pant[i];
			pant[i] = *pant[i].next;
			if (temp->name_edg[0] != '\0')
			{
				ft_printf("L%d-", i + 1);
				ft_putstr(temp->name_edg);
				ft_putchar(' ');
			}
		}
		ft_putchar('\n');
		j++;
	}
	exit(0);
}
/*
** Defines the weight of the node.
** Поправить, сделать при создании узла.
*/

void	weight_node(t_node *node)
{
	t_node	*iter;

	iter = node;
	while (iter != NULL)
	{
		iter->weight = 1;
		iter = iter->next;
	}
}

/*
** Check name in short list.
** Поиск имени в коротком пути, есть оно есть удаляем.
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
** Удоляет один лист  из списка соседей.
*/

int	delete_name_list(char *name, t_nlst **nlst)
{
	t_nlst	*iter;
	t_nlst	*pre;

	pre = *nlst;
	iter = (*nlst)->next;
	if (!ft_strcmp(name, (*nlst)->name_edg))
	{
		*nlst = (*nlst)->next;
		free(pre);	
		return (0);
	}
	while (iter != NULL)
	{
		if (!ft_strcmp(name, iter->name_edg))
		{
			pre->next = iter->next;	
			free(iter);
			return (0);
		}
		pre = pre->next;
		iter = iter->next;
	}
	return (1);
}

/*
** Определение первого и второго по весу узлов.
** Во второе сравнение не заходит. Возможно проверка не нужна.
*/

void	define_fir_sec_wei(t_node *node, t_ant *ant)
{
	t_nlst	*way;
	t_node	*cur_node;
	int		fir;
	int		sec;

	fir = 0;
	sec = 0;
	way = ant->ways->way;
	while (way != NULL)
	{
		cur_node = search_node(node, way->name_edg);
		if (cur_node->weight > fir && ft_strcmp(way->name_edg, ant->name_end))
		{
			sec = fir;
			fir = cur_node->weight;
			ft_strcpy(ant->sec_wei, ant->fir_wei);
			ft_strcpy(ant->fir_wei, cur_node->name);
		}
		else if (cur_node->weight > sec && ft_strcmp(way->name_edg, ant->name_end))
		{
			sec = cur_node->weight;
			ft_strcpy(ant->sec_wei, cur_node->name);
		}
		way = way->next;
	}
}

/*
** Remove an edge from the list.
*/
void	remove_edge(t_node *node, t_ant *ant)
{
	t_node	*fir_node;
	t_node	*sec_node;

	if (ant->fir_wei[0] == '\0' || ant->sec_wei[0] == '\0')
		return ;
	ft_strcpy(ant->pre_firn, ant->fir_wei);
	ft_strcpy(ant->pre_secn, ant->sec_wei);
	fir_node = search_node(node, ant->fir_wei);
	sec_node = search_node(node, ant->sec_wei);
	if (delete_name_list(fir_node->name, &sec_node->edg))
	{
		ant->bl = 1;
		ant->pre_steps = 1;
	}
	if (delete_name_list(sec_node->name, &fir_node->edg))
	{
		ant->bl = 1;
		ant->pre_steps = 1;
	}
}

/*
** Delete and free ways.
*/

void	delete_ways(t_ant *ant)
{
	t_ways	*ways;
	t_ways	*pre_ways;

	ways = ant->ways;
	ant->lvl = 0;
	ant->count_ways = 0;
	while (ways != NULL)
	{
		delete_all_list(&ways->way);
		pre_ways = ways;
		ways = ways->next;
		free(pre_ways);
	}
	ant->ways = NULL;
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
** Проверяет наличие подходящего пути.
*/

int		choice_way(t_ant *ant)
{
	int		sum_room;
	t_ways	*ways;
	
	sum_room = 0;
	ways = ant->ways;
	while (ways != NULL)
	{
		sum_room += ways->len_way;
		ways = ways->next;
	}
	if (ant->count_ant <= sum_room)
		return (1);
	return (0);
}

void	print_ways(t_ant *ant)
{
	t_ways	*ways;
	int		i;
	
	i = 0;
	ways = ant->ways;
	while (ways)
	{
		ft_printf("\nPath %d:\n", ++i);
		print_edges(ways->way);
		ways = ways->next;
	}
}

/*
** Print count steps.
*/

void	print_steps(t_ant *ant)
{
	t_ways *ways;

	ways = ant->ways;
	while (ways)
	{
		if (ant->max_count_way < ways->len_way)
			ant->max_count_way = ways->len_way;
		ways = ways->next;
	}
	ft_printf("count_ant %d\n", ant->count_ant);
	ft_printf("count_ways %d\n", ant->count_ways);
	ft_printf("max_count_way %d\n", ant->max_count_way);
ft_printf("Steps %d\n", ant->count_ant / ant->count_ways + ant->max_count_way - 1);
}

/*
** Проверяет увеличение количества шагов.
*/

int		cheack_step(t_node *node, t_ant *ant)
{
	t_node *cur_node;

	if (ant->cur_steps == 0)
		return (1);
	if (ant->cur_steps > ant->pre_steps && ant->pre_steps != 0)
	{	
		if (ant->bl == 0)
		{
			cur_node = search_node(node, ant->pre_firn);
			add_new_edges(&cur_node->edg, ant->pre_secn);
			cur_node = search_node(node, ant->pre_secn);
			add_new_edges(&cur_node->edg, ant->pre_firn);
		}
		return (0);
	}
	else
		return (1);
	return (1);
}

void	calc_all_ways(t_ant *ant)
{
	t_ways *ways;

	ways = ant->ways;
	ant->all_steps = 0;
	while (ways)
	{
		if (ant->max_count_way < ways->len_way)
			ant->max_count_way = ways->len_way;
		ant->all_steps += ways->len_way;
		ways = ways->next;
	}
}

/*
** Recolc_stepsad map.
*/

int		calc_steps(t_ant *ant)
{
	calc_all_ways(ant);
	ant->pre_steps = ant->cur_steps;
	if (((ant->all_steps + ant->count_ant - ant->count_ways) % ant->count_ways) != 0)
		ant->cur_steps = (ant->all_steps + (ant->count_ant - ant->count_ways)) / ant->count_ways + 1;
	else
		ant->cur_steps = (ant->all_steps + (ant->count_ant - ant->count_ways)) / ant->count_ways;
	if (ant->cur_steps > ant->pre_steps && ant->pre_steps != 0)
		return (1);
	else
		return (0);
}

void	sort_ways(t_ant *ant)
{
	t_ways	*ways;
	t_ways	*pre;
	t_ways	*temp;
	int		i;

	i = ant->count_ways + 1;
	while (--i > 0)
	{
		ways = ant->ways;
		while (ways->next != NULL)
		{
			pre = ways;
			ways = ways->next;
			if (pre->len_way > ways->len_way)
			{
				temp = pre->prev;
				temp->next = ways;
				ways->prev = temp;
				pre->next = ways->next;
				ways->next = pre;
				pre->prev = ways;
				continue ;
			}
		}
	}
}

void	cut_ways(t_ant *ant)
{
	t_ways	*ways;
	t_ways	*pre;
	int		i;
	int		pre_step;
	int		now_step;
	int		sum;

	i = 1;
	pre_step = 0;
	now_step = 0;
	sum = 0;
	ways = ant->ways;
	pre = ways;
	while (ways != NULL)
	{
		pre_step = now_step;
		sum += ways->len_way;
		if (((sum + ant->count_ant - i) % i) != 0)
			now_step = (sum + ant->count_ant - i) / i + 1;
		else
			now_step = (sum + ant->count_ant - i) / i;
		if (now_step > pre_step && pre_step != 0)
		{
			pre->next = NULL;
			ant->cur_steps = pre_step;
			ant->count_ways = i - 1;
			break;
		}
		i++;
		ant->cur_steps = now_step;
		ant->count_ways = i - 1;
		pre = ways;
		ways = ways->next;
	}
}


void	special_case(t_ant *ant)
{
	t_ways *ways;

	ways = ant->ways;
	if (ways->len_way >= ant->count_ant)
	{
		ant->ways->next = NULL;
		ant->count_ways = 1;
		ant->max_count_way = ft_lstlen(ant->ways->way) - 1;
		cut_ways(ant);
		print_ways(ant);
		solution(ant);
	}
}

void	working(t_node *node, t_ant *ant)
{
	while (cheack_step(node, ant))
	{
		weight_node(node);
		breadth_first_search(node, ant);
		//print_node(node);
		if(short_ways(node, ant))
		{
			zeroing_bfs(node);
			delete_ways(ant);
			continue ;
		}
		//print_ways(ant);
		if(calc_steps(ant))
		{
			zeroing_bfs(node);
			delete_ways(ant);
			continue;
		}
		special_case(ant);
		define_fir_sec_wei(node, ant);
		remove_edge(node, ant);
		zeroing_bfs(node);
		delete_ways(ant);
	}
}

void	read_map(void)
{
	char	*line;
	t_node	*node;
	t_ant	*ant;

	line = NULL;
	node = NULL;
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
	working(node, ant);
	weight_node(node);
	breadth_first_search(node, ant);
	//print_node(node);
	short_ways(node, ant);
	sort_ways(ant);
	cut_ways(ant);
	//print_steps(ant);
	//calc_all_ways(ant);
	print_ways(ant);
	solution(ant);
}

int		main(void)
{
	read_map();
	return (0);
}
