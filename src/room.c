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
	room->links = NULL;
	room->next = NULL;
	room->prev = NULL;
	return (room);
}

t_room	*find_by_name(t_room *list, char *name)
{
	while(list)
	{
		if (ft_strcmp(list->name, name) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}

void	check_connection(t_link *links, t_room *room)
{
	while(links)
	{
		if (links->room == room)
			error("Error! duplicate connection");
		links = links->next;
	}
}

void	add_connection(t_room *a, t_room *b)
{
	t_link *link;

	link = create_link(b);
	if (a->links != NULL)
		link->next = a->links;
	a->links = link;
}

void	connect(t_room *a, t_room *b)
{
	check_connection(a->links, b);
	check_connection(b->links, a);

}