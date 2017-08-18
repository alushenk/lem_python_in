/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_path_group.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:22:34 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/04 10:22:36 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_path	*find_shortest(t_path *path)
{
	t_path	*result;

	result = path;
	path = path->next;
	while (path)
	{
		if (path->weight < result->weight)
			result = path;
		path = path->next;
	}
	return (result);
}

t_path	*find_hardest(t_path *path)
{
	t_path	*result;

	result = path;
	path = path->next;
	while (path)
	{
		if (path->weight > result->weight)
			result = path;
		path = path->next;
	}
	return (result);
}

int		find_path_weigth(t_path *path)
{
	int		result;
	t_elem	*elem;

	result = 0;
	elem = path->list;
	while (elem)
	{
		result++;
		elem = elem->next;
	}
	return (result);
}

void	reset_group(t_group *group)
{
	t_path *path;

	group->efficiency = 0;
	path = group->paths;
	while (path)
	{
		path->ants_count = 0;
		path->weight = find_path_weigth(path);
		path = path->next;
	}
}

void	calc_group_efficiency(t_group *group, int number_of_ants)
{
	t_path	*path;
	int		i;

	reset_group(group);
	i = 0;
	while (i < number_of_ants)
	{
		path = find_shortest(group->paths);
		path->weight += 1;
		path->ants_count += 1;
		i++;
	}
	path = find_hardest(group->paths);
	group->efficiency = path->weight;
}

void	calculate_efficiency(t_graph *graph)
{
	t_group	*group;

	group = graph->groups;
	if (group == NULL)
		error("Error! no paths found\n", graph);
	while (group)
	{
		calc_group_efficiency(group, graph->number_of_ants);
		group = group->next;
	}
}

t_group	*find_optimal_group(t_group *group)
{
	t_group	*result;

	result = group;
	group = group->next;
	while (group)
	{
		if (group->efficiency < result->efficiency)
			result = group;
		group = group->next;
	}
	return (result);
}

void	choose_path_group(t_graph *graph)
{
	calculate_efficiency(graph);
	graph->chosen_group = find_optimal_group(graph->groups);
}
