//
// Created by lush on 7/31/17.
//

#include "lem-in.h"

t_elem	*create_element()
{
	t_elem *result;

	result = (t_elem*)malloc(sizeof(t_elem));
	result->room = NULL;
	result->next = NULL;
	return (result);
}

size_t	get_length(t_elem *list)
{
	size_t i;

	i = 0;
	while(list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

t_path	*create_path()
{
	t_path *result;

	result = (t_path*)malloc(sizeof(t_path));
	result->list = NULL;
	result->length = 0;
	result->next = NULL;
	return (result);
}

void	add_to_path(t_path *path, t_room *room)
{
	t_elem	*new_elem;
	t_elem	*list;

	new_elem = create_element();
	new_elem->room = room;
	list = path->list;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new_elem;
	}
	else
		path->list = new_elem;
	path->length += 1;
}

t_path	*copy_path(t_path *path)
{
	t_path	*result;
	t_elem	*elem;

	result = create_path();
	if (path == NULL)
		return (result);
	elem = path->list;
	while(elem)
	{
		add_to_path(result, elem->room);
		elem = elem->next;
	}
	return (result);
}