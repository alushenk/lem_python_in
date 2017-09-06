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

void	step(t_graph *graph, t_group *group, int i)
{
	t_path	*path;
	t_elem	*elem;
	t_room	*a;
	t_room	*b;

	path = group->paths;
	while (path)
	{
		elem = path->list;
		while (elem->next)
		{
			a = elem->room;
			b = elem->next->room;
			disconnect(a, b);
			find_groups(graph, i - 1);
			connect(a, b);
			elem = elem->next;
		}
		path = path->next;
	}
}

void	find_groups(t_graph *graph, int i)
{
	t_group *group;

	if (i == 0)
		return;
	group = find_group(graph);
	if (group->paths == NULL)
	{
		free_groups(group);
		return;
	}
	calc_group_efficiency(group, graph->number_of_ants);
	if (graph->groups == NULL)
		graph->groups = group;
	else
	{
		if (group->efficiency < graph->groups->efficiency)
			append_to_group(&graph->groups, group);
		else
		{
			free_groups(group);
			return;
		}
	}
	step(graph, group, i - 1);
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
	find_groups(graph, i);
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
		free(direct);
	}
}
