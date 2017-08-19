/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_groups_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 14:42:43 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/19 14:42:44 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	add_to_front(t_path *path, t_room *room)
{
	t_elem	*new_elem;

	new_elem = create_element();
	new_elem->room = room;
	if (path->list != NULL)
		new_elem->next = path->list;
	path->list = new_elem;
	path->weight += 1;
}

t_path	*pop_path(t_room *start, t_room *end)
{
	t_path	*result;
	t_elem	*list;
	t_room	*room;

	result = create_path();
	room = end;
	add_to_front(result, end);
	while (room != start)
	{
		list = room->list;
		while (list && list->room->dist != room->dist - 1)
			list = list->next;
		if (list == NULL)
			return (result);
		add_to_front(result, list->room);
		room = list->room;
	}
	list = result->list->next;
	while (list->next)
	{
		list->room->dist = -1;
		list = list->next;
	}
	return (result);
}

t_group	*find_group(t_graph *graph)
{
	t_group *group;
	t_path	*path;

	group = create_group();
	while (1)
	{
		calculate_graph(graph->start_room);
		path = pop_path(graph->start_room, graph->end_room);
		reset_rooms(graph->list);
		if (path->list->room != graph->start_room)
		{
			free_paths(path);
			break ;
		}
		add_path(group, path);
		free(path);
	}
	hard_reset_rooms(graph->list);
	return (group);
}

void	disconnect(t_room *a, t_room *b)
{
	pop_room(a, b);
	pop_room(b, a);
}

void	append_to_group(t_group **list, t_group *group)
{
	t_group *elem;

	if (*list == NULL)
	{
		*list = group;
		return ;
	}
	elem = *list;
	while (elem->next)
		elem = elem->next;
	elem->next = group;
}
