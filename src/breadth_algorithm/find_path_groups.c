//
// Created by lush on 8/16/17.
//

#include "../lem_in.h"

void	calculate_graph(t_room *room)
{
	t_elem	*list;
	t_path	*queue;

	queue = create_path();
	room->dist = 0;
	list = room->list;
	while(list)
	{
		if (list->room->dist > room->dist + 1)
		{
			list->room->dist = room->dist + 1;
			add_to_path(queue, list->room);
		}
		list = list->next;
	}

	t_elem	*step;
	t_path	*new_queue;
	while (queue->list)
	{
		step = queue->list;
		new_queue = create_path();
		while (step)
		{
			list = step->room->list;
			while(list)
			{
				if (list->room->dist > step->room->dist + 1)
				{
					list->room->dist = step->room->dist + 1;
					add_to_path(new_queue, list->room);
				}
				list = list->next;
			}
			step = step->next;
		}
		free_paths(queue);
		queue = new_queue;
	}
	free_paths(queue);
}

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
	while(room != start)
	{
		list = room->list;
		while(list && list->room->dist != room->dist - 1)
			list = list->next;
		if (list == NULL)
			return (result);
		add_to_front(result, list->room);
		room = list->room;
	}

	list = result->list->next;
	while(list->next)
	{
		list->room->dist = -1;
		list = list->next;
	}
	return (result);
}

void	reset_rooms(t_elem *list)
{
	while(list)
	{
		if (list->room->dist > 0)
			list->room->dist = INT_MAX;
		list = list->next;
	}
}

void	hard_reset_rooms(t_elem *list)
{
	while(list)
	{
		list->room->dist = INT_MAX;
		list = list->next;
	}
}

t_group	*find_group(t_graph *graph)
{
	t_group *group;
	t_path	*path;

	group = create_group();
	while(1)
	{
		calculate_graph(graph->start_room);
		path = pop_path(graph->start_room, graph->end_room);
		reset_rooms(graph->list);
		if (path->list->room != graph->start_room)
		{
			free_paths(path);
			break;
		}
		add_path(group, path);
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

	if(*list == NULL)
	{
		*list = group;
		return;
	}
	elem = *list;
	while (elem->next)
		elem = elem->next;
	elem->next = group;
}

t_path	*get_one_step_path(t_room *start, t_room *end)
{
	t_path	*result;

	result = NULL;
	if (find_by_id(start->list, end))
	{
		result = create_path();
		add_to_path(result, start);
		add_to_path(result, end);
		disconnect(start, end);
	}
	return (result);
}

void	find_path_groups(t_graph *graph)
{
	t_group	*groups;
	t_group *group;
	t_path	*path;
	t_path	*direct;
	t_elem	*elem;
	t_room	*a;
	t_room	*b;

	direct = get_one_step_path(graph->start_room, graph->end_room);

	groups = NULL;
	while(1)
	{
		group = find_group(graph);
		append_to_group(&groups, group);
		path = group->paths;
		if (direct)
			add_path(group, direct);
		while(path)
		{
			elem = path->list;
			while(elem->next)
			{
				a = elem->room;
				b = elem->next->room;
				disconnect(a, b);

				group = find_group(graph);
				if (group->paths)
				{
					if (direct)
						add_path(group, direct);
					append_to_group(&groups, group);
				}
				else
					free_groups(group);
				connect(a, b);
				elem = elem->next;
			}
			path = path->next;
		}
		break;
	}
	if (direct)
		connect(graph->start_room, graph->end_room);
	graph->groups = groups;
}