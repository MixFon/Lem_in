#include "lem_in.h"

void ft_print_lem(t_lem lem)
{
	ft_putstr("count_ants: ");
	ft_putnbr(lem.count_ants);
	ft_putstr("\n");

	ft_putstr("start:   ");
	ft_putstr("\n       start.name_room: ");
	ft_putstr(lem.start.name_room);
	ft_putstr("\n       start.coord_x: ");
	ft_putnbr(lem.start.coord_x);
	ft_putstr("\n       start.coord_y: ");
	ft_putnbr(lem.start.coord_y);
	ft_putstr("\n");

	ft_putstr("end:   ");
	ft_putstr("\n       end.name_room: ");
	ft_putstr(lem.end.name_room);
	ft_putstr("\n       end.coord_x: ");
	ft_putnbr(lem.end.coord_x);
	ft_putstr("\n       end.coord_y: ");
	ft_putnbr(lem.end.coord_y);
	ft_putstr("\n");

	ft_putstr("roooms:   ");
	while (lem.rooms != NULL)
	{
		ft_putstr("\n       rooms.name_room: ");
		ft_putstr(lem.rooms->name_room);
		ft_putstr("\n       rooms.coord_x: ");
		ft_putnbr(lem.rooms->coord_x);
		ft_putstr("\n       rooms.coord_y: ");
		ft_putnbr(lem.rooms->coord_y);
		ft_putstr("\n");
		lem.rooms = lem.rooms->next;
	}

	ft_putstr("links:   ");
	while (lem.links != NULL)
	{
		ft_putstr("\n       link.room1: ");
		ft_putstr(lem.links->room1);
		ft_putstr("\n       link.room2: ");
		ft_putstr(lem.links->room2);
		ft_putstr("\n");
		lem.links = lem.links->next;
	}

	ft_putstr("\n");
}

void ft_print_vertex(t_vertex *vertex)
{
	//t_vertex *tmp;
	t_neighbour *tmp_n;

	//tmp = vertex;
	ft_putstr("vertex:   ");
	while (vertex != NULL)
	{
		ft_putstr("\n       vertex.name_vertex: ");
		ft_putstr(vertex->name_vertex);
		ft_putstr("\n       vertex.mark_green: ");
		ft_putnbr(vertex->mark_green);
		ft_putstr("\n       vertex.neighbour: ");
		tmp_n = vertex->neighbour;
		while (vertex->neighbour != NULL)
		{
			ft_putstr(vertex->neighbour->name_neighbour);
			vertex->neighbour = vertex->neighbour->next;
			ft_putstr("\n       ");

		}
		vertex->neighbour = tmp_n;
		//ft_putstr("\n       rooms.coord_y: ");
		//ft_putnbr(lem.rooms->coord_y);
		ft_putstr("\n");
		vertex = vertex->next;
	}
	//vertex = tmp;
	ft_free_vertex(&vertex);
}

void ft_print_stack(t_stack *stack)
{
	ft_putstr("stack   ");
	while (stack != NULL)
	{
		ft_putstr("; ");
		ft_putstr(stack->name);
		stack = stack->next;
	}
}

int		ft_count_rooms(t_lem *lem)
{
	int count;

	count = 0;
	while (lem->rooms != NULL)
	{
		count++;
		lem->rooms = lem->rooms->next;
	}
	return (count);
}