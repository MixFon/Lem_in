/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 10:18:25 by widraugr          #+#    #+#             */
/*   Updated: 2019/06/29 21:43:37 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "../lem.h"

/*
** If there is error. Shut down the program.
*/

void	sys_err(char *err)
{
	write(2, err, ft_strlen(err));
	exit(0);
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
		ft_printf("name = %s,    level  = %d weight = %d dfs {%d}\n",
			node->name, node->level, node->weight, node->dfs_mark);
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

	i = -1;
	while (++i < count_ways)
	{
		if (isempty_queue(que))
		{
			que->end = NULL;
			return ;
		}
		iter = que->first;
		temp = que->end;
		if (iter == temp)
			return ;
		while (iter->next != temp)
			iter = iter->next;
		que->end = iter;
		que->end->next = NULL;
		free(temp);
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
	while (iter != NULL)
	{
		cur_node = search_node(node, iter->name_edg);
		if (cur_node->dfs_mark == 0)
			return (1);
		iter = iter->next;
	}
	return (0);
}

int		first_short_way(t_node *node, t_ant *ant)
{
	if(!(ant->ways = create_short_way(node, ant)))
	{
		ft_putendl("H11111111");
		ant->count_ways++;
		ant->pre_steps = 1;
		ant->bl = 0;
		return (1) ;
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
			if (first_short_way(node, ant))
				return (1);
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
		//ft_printf("delete {%s}\n", iter->name_edg);
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
			ft_printf("   Insetr:{%s}\n", edg_lst->name_edg);
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
	ft_printf("   Insetr:{%s}\n", ant->name_start);
	while (!isempty_queue(ant->que))
	{
		name = remove_first(ant->que, 1);
		ft_printf("remove:[%s]\n", name);
		cur_node = search_node(node, name);
		if (!ft_strcmp(name, ant->name_end))
		{
			ant->lvl = cur_node->level;
			delete_all_list(&ant->que->first);
			ft_printf("Find!![%s]\n", name);
			free(name);
			//return ;
			continue ;
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

t_node	*help(t_node *node, t_ways *iter, t_ant *ant)
{
	t_node *cur_node;

	cur_node = search_node(node, iter->way->name_edg);
	cur_node->dfs_mark = 1;
	ant->s_lvl = cur_node->level;
	return (cur_node);
}

void	work_dfs(t_ways *iter, t_nlst **lst, t_node *cur_node)
{
	add_new_nlst(&iter->way, (*lst)->name_edg);
	iter->len_way++;
	cur_node->dfs_mark = 1;
}	

int		part(t_node *node, t_nlst *lst, t_ways *iter, t_ant *ant)
{
	char	*name;
	t_node	*cur_node;

	name = lst->name_edg;
	cur_node = search_node(node, name);
	ft_printf("edges {%s}\n", cur_node->name);
	if (!ft_strcmp(name, ant->name_start))
	{
		ft_putendl("1111");
		add_new_nlst(&iter->way, name);
		cur_node->dfs_mark = 1;
		return (1);
	}
	else if (cur_node->level == ant->s_lvl - 1 && cur_node->dfs_mark == 0 &&
			cur_node->level != 0)
	{
		ft_putendl("2222");
		work_dfs(iter, &lst, cur_node);
		return (2);
	}
	return (0);
}

/*
** Create list only short way.
*/

t_ways	*create_short_way(t_node *node, t_ant *ant)
{
	t_node	*cur_node;
	t_ways	*iter;
	int		bl;
	t_nlst	*lst;

	iter = create_new_way();
	iter->way = creat_new_lst(ant->name_end);
	while (iter->way != NULL)
	{
		cur_node = help(node, iter, ant);
		lst = cur_node->edg;
		ft_printf("cur_node {%s}\n", cur_node->name);
		while (lst != NULL)
		{
			bl = part(node, lst, iter, ant);
			if (bl == 1)
				return (iter);
			else	if (bl == 2)
				break ;
			lst = lst->next;
		}
		node_is_visited(lst, iter, cur_node);
	}
	free(iter);
	return (NULL);
}

int		part_way(t_node *node, t_nlst **lst, t_ways *iter, t_ant *ant)
{
	t_node *cur_node;

	cur_node = search_node(node, (*lst)->name_edg);
	if (!ft_strcmp((*lst)->name_edg, ant->name_start))
	{
		if (ant->a == 1)
		{
			*lst = (*lst)->next;
			return (3);
		}
		add_new_nlst(&iter->way, (*lst)->name_edg);
		cur_node->dfs_mark = 1;
		return (1);
	}
	else if (cur_node->level == ant->s_lvl - 1 && cur_node->dfs_mark == 0)
	{
		work_dfs(iter, lst, cur_node);
		return (2);
	}
	else if (cur_node->dfs_mark == 0)
	{
		work_dfs(iter, lst, cur_node);
		return (2);
	}
	return (0);
}

t_node	*search_cur_node(t_node *node, t_ant *ant, t_nlst **lst, t_ways *iter)
{
	t_node	*cur_node;
	
	cur_node = search_node(node, iter->way->name_edg);
	cur_node->dfs_mark = 1;
	ant->s_lvl = cur_node->level;
	*lst = cur_node->edg;
	ant->a++;
	return (cur_node);
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

	iter = create_new_way();
	iter->way = creat_new_lst(ant->name_end);
	ant->a = 0;
	while (iter->way != NULL)
	{
		cur_node = search_cur_node(node, ant, &lst, iter);
		while (lst)
		{
			ant->a = part_way(node, &lst, iter, ant);
			if (ant->a == 1)
				return (iter);
			else	if (ant->a == 2)
				break ;
			else	if (ant->a == 3)
				continue ;
			lst = lst->next;
		}
		node_is_visited(lst, iter, cur_node);
	}
	free(iter);
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
	new->ways = NULL;
	new->lvl = 0;
	new->count_ant = 0;
	new->pre_steps = 0;
	new->all_steps = 0;
	new->num_fn = 0;
	new->num_sn = 0;
	new->bl = 0;
	new->max_count_way = 0;
	new->s_lvl = 0;
	new->a = 0;
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

void	delete_dublicate(t_ant *ant)
{
	if (ant->ways->next == NULL)
		return ;
	if (ant->ways->len_way == 1 && ant->ways->next->len_way == 1)
	{
		delete_tail_ways(ant->ways->next);
		ant->ways->next = NULL;
		ant->count_ways = 1;
	}
}

void	re_count_steps(t_ant *ant)
{
	ft_printf("count_ways %d\n", ant->count_ways);
	if (ant->ways->len_way == 1 && ant->cur_steps < ant->count_ant)
	{
		calc_all_ways(ant);
		ant->cur_steps = ant->count_ant / ant->count_ways + ant->max_count_way - 1;
	}
	if (ant->ways->len_way == 1 && ant->cur_steps > ant->count_ant)
	{
		ant->cur_steps = ant->count_ant;
		delete_tail_ways(ant->ways->next);
		ant->ways->next = NULL;
		ant->count_ways = 1;
	}
}

/*
** Admission room of name start.
*/

void	admission_name_start_recount(t_ant *ant)
{
	t_ways	*ways;
	t_nlst	*nlst;

	ways = ant->ways;
	delete_dublicate(ant);
	re_count_steps(ant);	
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

void	missing_row(t_ant *ant, t_nlst **pant_it, int i, int *b)
{
	int	miss;

	miss = i / ant->count_ways;
	while (miss > 0)
	{
		add_new_edges(pant_it, "\0");
		b++;
		miss--;
	}
}

void	create_print_list(t_nlst *pant, t_ant *ant, int i)
{
	t_nlst	**pant_it;
	t_nlst	*iter;
	int		j;
	int		b;

	b = 0;
	pant->next = NULL;
	pant_it = &pant;
	missing_row(ant, pant_it, i, &b);
	if (ant->ways->iter == NULL)
		ant->ways->iter = ant->ways;
	iter = ant->ways->iter->way;
	while (iter != NULL)
	{
		add_new_edges(pant_it, iter->name_edg);
		iter = iter->next;
		b++;
	}
	j = ant->cur_steps - b + 1;
	while (--j > 0)
		add_new_edges(pant_it, "\0");
	ant->ways->iter = ant->ways->iter->next;
}

void	delete_node(t_node *node)
{
	t_node *cur_node;

	cur_node = node;
	while(node != NULL)
	{
		cur_node = node;
		delete_all_list(&(cur_node->edg));
		free(cur_node);
		node = node->next;
	}
}

void	delete_node_ant(t_node *node, t_ant *ant)
{
	delete_node(node);
	delete_ways(ant);
	delete_all_list(&ant->que->first);
	free(ant->que);
	free(ant);
	ant = NULL;
}

/*
** Print solution.
*/

void	solution(t_node *node, t_ant *ant)
{
	int				i;
	int				j;
	static t_nlst	*temp;
	t_nlst			*del;
	t_nlst			pant[ant->count_ant];

	i = -1;
	admission_name_start_recount(ant);
	while (++i < ant->count_ant)
		create_print_list(&pant[i], ant, i);
	j = 0;
	while (j < ant->cur_steps)
	{
		i = -1;
		while (++i < ant->count_ant)
		{
			temp = &pant[i];
			del = pant[i].next;
			pant[i] = *pant[i].next;
			if (temp->name_edg[0] != '\0')
				ft_printf("L%d-%s ", i + 1, temp->name_edg);
			free(del);
		}
		ft_putchar('\n');
		j++;
	}
	ft_printf("ant->count_ant  %d\n", ant->count_ant);
	ft_printf("ant->cur_steps  %d\n", ant->cur_steps);
	//delete_node_ant(node, ant);
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

int		delete_name_list(char *name, t_nlst **nlst, int *num)
{
	t_nlst	*iter;
	t_nlst	*pre;
	int		i;

	i = 1;
	pre = *nlst;
	iter = (*nlst)->next;
	ft_printf("!iteration |%s|\n", pre->name_edg);
	if (!ft_strcmp(name, (*nlst)->name_edg))
	{
		*nlst = (*nlst)->next;
		free(pre);	
		*num = 0;
		return (0);
	}
	while (iter != NULL)
	{
		ft_printf("iteration |%s|\n", iter->name_edg);
		if (!ft_strcmp(name, iter->name_edg))
		{
			pre->next = iter->next;	
			free(iter);
			*num = i;
			return (0);
		}
		i++;
		pre = pre->next;
		iter = iter->next;
	}
	return (1);
}

int		cheack_main_way(t_node *temp_node, t_nlst *way, int level)
{
	while (way != NULL)
	{
		if (ft_strcmp(temp_node->name, way->name_edg) == 0 && temp_node->level == level)
			return (1);
		way = way->next;
	}
	return (0);
}

void	unwanted_edg(t_node *node, t_ant *ant)
{
	t_node	*cur_node;
	t_nlst	*edg;
	t_node	*temp_node;

	if (ft_strcmp(ant->fir_wei, ant->name_start) == 0)
	{
		cur_node = search_node(node, ant->sec_wei);
		edg = cur_node->edg;
		while (edg != NULL)
		{
			temp_node = search_node(node, edg->name_edg);	
			if (cheack_main_way(temp_node, ant->ways->way, cur_node->level - 1))
				ft_strcpy(ant->fir_wei, temp_node->name);
			edg = edg->next;
		}
		ft_printf("asd fir_wie {%s}\n", ant->fir_wei);
	}
	else	if (ft_strcmp(ant->sec_wei, ant->name_start) == 0)
	{
		cur_node = search_node(node, ant->fir_wei);
		edg = cur_node->edg;
		while (edg != NULL)
		{
			temp_node = search_node(node, edg->name_edg);	
			if (cheack_main_way(temp_node, ant->ways->way, cur_node->level - 1))
				ft_strcpy(ant->sec_wei, temp_node->name);
			edg = edg->next;
		}
		ft_printf("asd sec_wie {%s}\n", ant->sec_wei);
	}

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
	unwanted_edg(node, ant);
}

/*
** Remove an edge from the list.
*/

void	remove_edge(t_node *node, t_ant *ant)
{
	t_node	*fir_node;
	t_node	*sec_node;

	ft_putendl("Delete ");
	if (ant->fir_wei[0] == '\0' || ant->sec_wei[0] == '\0')
		return ;
	ft_strcpy(ant->pre_firn, ant->fir_wei);
	ft_strcpy(ant->pre_secn, ant->sec_wei);
	ft_printf("Delete edges fir {%s}, sec {%s}\n", ant->fir_wei, ant->sec_wei);
	fir_node = search_node(node, ant->fir_wei);
	ft_printf("Lewel node fir  {%s}, = {%d}\n", fir_node->name, fir_node->level);
	sec_node = search_node(node, ant->sec_wei);
	ft_printf("Lewel node sec  {%s}, = {%d}\n", sec_node->name, sec_node->level);
	if (delete_name_list(fir_node->name, &sec_node->edg, &ant->num_fn))
	{
		ft_putendl("B111");
		ant->bl = 1;
		ant->pre_steps = 1;
	}
	if (delete_name_list(sec_node->name, &fir_node->edg, &ant->num_sn))
	{
		ft_putendl("B222");
		ant->bl = 1;
		ant->pre_steps = 1;
	}
	ft_printf("Number fir {%d}, sec {%d}\n", ant->num_fn, ant->num_sn);
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
	ft_putendl(__func__);
	while (ways)
	{
		ft_printf("\nPath %d:\nCout staps in way %d\n", ++i, ways->len_way);
		print_edges(ways->way);
		ways = ways->next;
	}
}

void	add_to_num_edges(t_nlst **edg, char *name, int num)
{
	t_nlst	*iter;
	t_nlst	*pre;
	t_nlst	*temp;
	int		i;

	i = 0;
	iter = *edg;
	pre = NULL;
	temp = NULL;
	ft_putendl("HELLLLLLLLLLLLLLLLLLL");
	ft_printf("num = {%d}\n", num);
	ft_printf("name {%s}\n", name);
	while (iter != NULL)
	{
		ft_putendl("11");
		if (i == num)
		{
			ft_putendl("22");
			ft_printf("1i == %d\n", i);
			temp = creat_new_lst(name);
			temp->next = iter;
			if (pre == NULL)
				*edg = temp;
			else
				pre->next = temp;
			print_edges(*edg);
			return ;
		}
		ft_printf("i == %d\n", i);
		i++;
		pre = iter;
		iter = iter->next;
	}
	ft_putendl("33");
	if (pre == NULL)
	{
		ft_putendl("44");
		ft_printf("2i == %d\n", i);
		temp = creat_new_lst(name);
		*edg = temp;
		print_edges(*edg);
		return ;
	}
	else
	{
		ft_putendl("55");
		temp = creat_new_lst(name);
		pre->next = temp;
		print_edges(*edg);
	}	
	ft_putendl("HEOOOOOOOOOOOOOOOOOOO");
}

/*
** Проверяет увеличение количества шагов.
*/

int		cheack_step(t_node *node, t_ant *ant)
{
	t_node *cur_node;

	ft_putendl("cheack STEP");
	if (ant->cur_steps == 0)
		return (1);
	ft_printf("cur_step [%d] pre_step [%d]\n", ant->cur_steps, ant->pre_steps);
	ft_printf("pre_firn [%s] pre_secn [%s]\n", ant->pre_firn, ant->pre_secn);
	ft_printf("bl =  [%d]\n", ant->bl);
	if (ant->cur_steps > ant->pre_steps && ant->pre_steps != 0)
	{	
		if (ant->bl == 0)
		{
			ft_printf("bl =  [%d]\n", ant->bl);
			//print_node(node);
			//
			cur_node = search_node(node, ant->pre_firn);
			add_to_num_edges(&cur_node->edg, ant->pre_secn, ant->num_sn);
			//add_new_edges(&cur_node->edg, ant->pre_secn);

			cur_node = search_node(node, ant->pre_secn);
			add_to_num_edges(&cur_node->edg, ant->pre_firn, ant->num_fn);
			//add_new_edges(&cur_node->edg, ant->pre_firn);
			//print_node(node);
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

void	swap_nlst_ptr(t_nlst **one, t_nlst **two)
{
	t_nlst	*temp;

	temp = *one;
	*one = *two;
	*two = temp;
}

void	swap_len_way(int *one, int *two)
{
	int	temp;

	temp = *one;
	*one = *two;
	*two = temp;
}

void	sort_ways(t_ant *ant)
{
	t_ways	*ways;
	t_ways	*pre;
	t_ways	*temp;
	int		bl;

	print_ways(ant);
	bl = 1;
	while (bl)
	{
		ways = ant->ways;
		bl = 0;
		while (ways->next != NULL)
		{
			pre = ways;
			ways = ways->next;
			if (ways == NULL)
				break ;
			if (pre->len_way > ways->len_way)
			{
				swap_nlst_ptr(&pre->way, &ways->way);
				swap_len_way(&pre->len_way, &ways->len_way);
				bl = 1;
			}
		}
	}
	print_ways(ant);
}

void	delete_tail_ways(t_ways *ways)
{
	t_ways	*pre;
	
	pre = ways;
	while (ways != NULL)
	{
		pre = ways;
		ways = ways->next;
		delete_all_list(&pre->way);
		free(pre);	
	}
}

int		len_ways(t_ways *ways)
{
	int i;

	i = 0;
	while (ways != NULL)
	{
		i++;
		ways = ways->next;
	}
	return (i);
}

int		finish_cut(t_ant *ant, t_ways *pre, int *now_step, int *pre_step)
{
	//static int i = 0;
	//i = len_ways(ant->ways);
	//ft_printf("i = %d, pre_step %d, now_step %d\n", ++i, *pre_step, *now_step);
	if (*now_step >= *pre_step && *pre_step != 0)
	{
		//ft_putendl("Hello4???????????");
		delete_tail_ways(pre->next);
		pre->next = NULL;
		ant->cur_steps = *pre_step + 1;
		ant->count_ways = ant->a - 1;
		//ft_putendl("Hello4???????????");
		return (1);
	}
	return (0);
}

void	save_date(t_ant *ant, int now_step)
{
	ant->a++;
	ant->cur_steps = now_step;
	ant->count_ways = ant->a - 1;
}

void	cut_ways(t_ant *ant)
{
	t_ways	*ways;
	t_ways	*pre;
	int		pre_step;
	int		now_step;
	int		sum;

	ant->a = 1;
	now_step = 0;
	sum = 0;
	ways = ant->ways;
	while (ways != NULL)
	{
		pre_step = now_step;
		sum += ways->len_way;
		if (((sum + ant->count_ant - ant->a) % ant->a) != 0)
			now_step = (sum + ant->count_ant - ant->a) / ant->a + 1;
		else
			now_step = (sum + ant->count_ant - ant->a) / ant->a;
		if (finish_cut(ant, pre, &now_step, &pre_step) == 1)
			return ;
		save_date(ant, now_step);
		pre = ways;
		ways = ways->next;
	}
	//delete_tail_ways(pre->next);
}

void	special_case(t_node *node, t_ant *ant)
{
	t_ways *ways;

	ways = ant->ways;
	if (ways->len_way > ant->count_ant)
	{
		delete_tail_ways(ant->ways->next);
		ant->ways->next = NULL;
		ant->count_ways = 1;
		ant->max_count_way = ft_lstlen(ant->ways->way) - 1;
		cut_ways(ant);
		print_ways(ant);
		solution(node, ant);
	}
}

void	working(t_node *node, t_ant *ant)
{
	while(cheack_step(node, ant))
	{
		weight_node(node);
		breadth_first_search(node, ant);
		ft_putendl("A333");
		if (short_ways(node, ant))
		{
			ft_putendl("A111");
			zeroing_bfs(node);
			delete_ways(ant);
			continue ;
		}
		if(calc_steps(ant))
		{
			ft_putendl("A222");
			zeroing_bfs(node);
			delete_ways(ant);
			continue;
		}
		//special_case(node, ant);
		define_fir_sec_wei(node, ant);
		print_node(node);
		remove_edge(node, ant);
		zeroing_bfs(node);
		delete_ways(ant);
	}
}

/*
** Print room's name and coor.
** Delete!!!!!!!!!!!!!!!!!!!!!!!!!11
*/

void	print_room_coor(t_room *rooms)
{
	ft_putstr(rooms->name_room);
	ft_putchar(' ');
	ft_putnbr(rooms->coord_x);
	ft_putchar(' ');
	ft_putnbr(rooms->coord_x);
	ft_putchar('\n');
}

/*
** Copy node .
*/

void	copy_node(t_node ***node, t_room *rooms)
{
	t_room	*rooms_it;
	
	rooms_it = rooms;
	while (rooms_it != NULL)
	{
		//print_room_coor(rooms_it);
		**node = add_node(**node, &rooms_it->name_room);
		rooms_it = rooms_it->next;
	}
	//print_node(*node);
}

/*
** Copy link.
*/

void	copy_link(t_node **node, t_link *links)
{
	t_link	*links_it;
	t_node	*cur_node;

	links_it = links;
	while (links_it != NULL)
	{
		cur_node = search_node(*node, links_it->room1);
		add_new_edges(&cur_node->edg, links_it->room2);
		cur_node = search_node(*node, links_it->room2);
		add_new_edges(&cur_node->edg, links_it->room1);
		links_it = links_it->next;
	}
}

/*
** Copy node and link to ant.
*/

void	copy_node_link(t_node **node, t_ant *ant, t_lem *lem)
{
	copy_node(&node, lem->rooms);	
	copy_link(node, lem->links); 
	ft_strcpy(ant->name_start, lem->start.name_room);
	ft_strcpy(ant->name_end, lem->end.name_room);
	ant->count_ant = lem->count_ants;
}

void	sum_max_ways(t_node *node, t_ant *ant)
{
	t_node	*cur_node;
	int		one;
	int		two;

	cur_node = search_node(node, ant->name_start);
	one = ft_lstlen(cur_node->edg);
	cur_node = search_node(node, ant->name_end);
	two = ft_lstlen(cur_node->edg);
	(one < two) ? (ant->sum_ways = one) : (ant->sum_ways = two);
	ft_printf("Sum ways %d\n", ant->sum_ways);
}

void	read_map(void)
{
	t_lem	lem;
	t_node	*node;
	t_ant	*ant;
	char	*file;

	node = NULL;
	ant = init_ant();
	file = ft_strnew(0);
	lem = ft_get_lem(&file);
	ft_check_graph(&lem);
	ft_putendl(file);
	free(file);
	//exit(0);
	copy_node_link(&node, ant, &lem);
	//print_node(node);
	ft_free_lem(&lem);
	sum_max_ways(node, ant);
	working(node, ant);
	//print_ways(ant);
	weight_node(node);
	breadth_first_search(node, ant);
	print_node(node);
	short_ways(node, ant);
	sort_ways(ant);
	cut_ways(ant);
	print_ways(ant);
	solution(node, ant);
}

int		main(void)
{
	read_map();
	return (0);
}
