//
// Created by lush on 8/1/17.
//

#include "lem-in.h"

t_path	*find_shortest(t_path *path)
{
	t_path	*result;

	result = path;
	path = path->next;
	while(path)
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
	while(path)
	{
		if (path->weight > result->weight)
			result = path;
		path = path->next;
	}
	return (result);
}

void	calculate_efficiency(t_graph *graph)
{
	t_group	*group;
	t_path	*path;
	int 	i;

	group = graph->groups;
	if (group == NULL)
		error("Error! no paths found");
	while(group)
	{
		i = 0;
		while(i < graph->number_of_ants)
		{
			path = find_shortest(group->paths);
			path->weight += 1;
			path->ants_count += 1;
			i++;
		}
		path = find_hardest(group->paths);
		group->efficiency = path->weight;
		group = group->next;
	}
}

t_group	*find_optimal_group(t_group	*group)
{
	t_group	*result;

	result = group;
	group = group->next;
	while(group)
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