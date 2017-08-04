/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:24:04 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/04 10:24:05 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*create_room(char *name, int x, int y)
{
	t_room *room;

	room = (t_room*)malloc(sizeof(t_room));
	room->name = name;
	room->x = x;
	room->y = y;
	room->is_free = 1;
	room->list = NULL;
	return (room);
}

t_room	*find_by_name(t_elem *list, char *name)
{
	while (list)
	{
		if (ft_strcmp(list->room->name, name) == 0)
			return (list->room);
		list = list->next;
	}
	return (NULL);
}

t_room	*find_by_index(t_elem *list, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		list = list->next;
		i++;
	}
	return (list->room);
}

t_room	*find_by_id(t_elem *list, t_room *room)
{
	while (list)
	{
		if (list->room == room)
			return (list->room);
		list = list->next;
	}
	return (NULL);
}

void	connect(t_room *a, t_room *b)
{
	t_elem *elem;

	if (find_by_id(a->list, b) || find_by_id(b->list, a))
		error("Error! duplicate connection\n");
	elem = create_element();
	elem->room = b;
	if (a->list != NULL)
		elem->next = a->list;
	a->list = elem;
	elem = create_element();
	elem->room = a;
	if (b->list != NULL)
		elem->next = b->list;
	b->list = elem;
}
