/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_groups.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 19:08:38 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/18 19:08:39 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	calculate_step(t_room *room, t_path *queue)
{
	t_elem	*list;

	list = room->list;
	while (list)
	{
		if (list->room->dist > room->dist + 1)
		{
			list->room->dist = room->dist + 1;
			add_to_path(queue, list->room);
		}
		list = list->next;
	}
}

void	calculate_graph(t_room *room)
{
	t_path	*queue;
	t_elem	*step;
	t_path	*new_queue;

	queue = create_path();
	room->dist = 0;
	calculate_step(room, queue);
	while (queue->list)
	{
		step = queue->list;
		new_queue = create_path();
		while (step)
		{
			calculate_step(step->room, new_queue);
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

void	reset_rooms(t_elem *list)
{
	while (list)
	{
		if (list->room->dist > 0)
			list->room->dist = INT_MAX;
		list = list->next;
	}
}

void	hard_reset_rooms(t_elem *list)
{
	while (list)
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

void	step(t_graph *graph, int i)
{
	t_group *group;
	t_path	*path;
	t_elem	*elem;
	t_room	*a;
	t_room	*b;

	if (i == 0)
		return ;
	i--;
	group = find_group(graph);
	if (group->paths)
	{
		calc_group_efficiency(group, graph->number_of_ants);
		if (graph->groups == NULL ||
			group->efficiency < find_optimal_group(graph->groups)->efficiency)
			append_to_group(&graph->groups, group);
		else
		{
			free_groups(group);
			return ;
		}
	}
	else
	{
		free_groups(group);
		return ;
	}
	path = group->paths;
	while (path)
	{
		elem = path->list;
		while (elem->next)
		{
			a = elem->room;
			b = elem->next->room;
			disconnect(a, b);
			step(graph, i);
			connect(a, b);
			elem = elem->next;
		}
		path = path->next;
	}
}

int		get_connections_count(t_room *room)
{
	t_elem	*elem;
	int		i;

	elem = room->list;
	i = 0;
	while (elem)
	{
		i++;
		elem = elem->next;
	}
	return (i);
}

void	find_path_groups(t_graph *graph)
{
	t_group	*group;
	t_path	*direct;
	int		i;

	direct = get_one_step_path(graph->start_room, graph->end_room);
	i = get_connections_count(graph->start_room);
	step(graph, i);
	if (direct)
		connect(graph->start_room, graph->end_room);
	if (direct)
	{
		group = graph->groups;
		if (group == NULL)
		{
			graph->groups = create_group();
			add_path(graph->groups, direct);
		}
		else
			while (group)
			{
				add_path(group, direct);
				group = group->next;
			}
	}
}
