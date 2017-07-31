//
// Created by lush on 7/30/17.
//

#include "lem-in.h"

t_room	*create_room(char *name, int x, int y)
{
	t_room *room;

	room = (t_room*)malloc(sizeof(t_room));
	room->name = name;
	room->x = x;
	room->y = y;
	room->list = NULL;
	return (room);
}

t_room	*find_by_name(t_elem *list, char *name)
{
	while(list)
	{
		if (ft_strcmp(list->room->name, name) == 0)
			return (list->room);
		list = list->next;
	}
	return (NULL);
}

t_room	*find_by_id(t_elem *list, t_room *room)
{
	while(list)
	{
		if (list->room == room)
			return (list->room);
		list = list->next;
	}
	return (NULL);
}

void	add_connection(t_room *a, t_room *b)
{
	t_elem *elem;

	elem = create_element();
	elem->room = b;
	if (a->list != NULL)
		elem->next = a->list;
	a->list = elem;
}

void	connect(t_room *a, t_room *b)
{
	if (find_by_id(a->list, b) || find_by_id(b->list, a))
		error("Error! duplicate connection");
	add_connection(a, b);
	add_connection(b, a);
}