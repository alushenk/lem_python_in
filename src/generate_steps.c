//
// Created by lush on 8/1/17.
//

#include "lem-in.h"

void	create_steps(t_path *path, int start_name, t_room *end)
{
	t_step	*step;
	t_move	*move;
	t_room	*current_room;
	t_room	*next_room;
	int 	number_of_ants;
	int 	i;
	int 	index;
	int 	ant_name;
	int 	name;

	name = start_name;
	number_of_ants = path->ants_count;
	i = 0;
	while(number_of_ants > 0)
	{
		step = create_step();
		index = i;
		ant_name = name;
		while(index >= 0 && ant_name < path->ants_count + start_name)
		{
			current_room = find_by_index(path->list, index);
			next_room = find_by_index(path->list, index + 1);
			if (next_room->is_free)
			{
				move = create_move(ant_name, next_room->name);
				add_move(step, move);
				next_room->is_free = 0;
				current_room->is_free = 1;
				index -= 1;
				ant_name += 1;
				if (next_room == end)
				{
					end->is_free = 1;
					number_of_ants -= 1;
					name += 1;
					i--;
				}
			}
		}
		add_step(path, step);
		i++;
	}

}

t_step	*combine_steps(t_path *list, int paths_count)
{
	t_path	*path;
	t_step	*step;
	t_step	*temp;
	t_move	*move;
	t_step	*result;
	int		empty;
	int 	ended;

	result = NULL;
	while(1)
	{
		empty = 0;
		step = create_step();
		ended = 0;
		while(ended < paths_count)
		{
			path = list;
			while(path)
			{
				if (path->steps)
				{
					move = path->steps->move;
					path->steps->move = move->next;
					if (move->next == NULL)
					{
						temp = path->steps;
						path->steps = temp->next;
						free(temp);
						ended += 1;
					}
					move->next = NULL;
					add_move(step, move);
				}
				else
				{
					empty += 1;
					ended += 1;
				}
				path = path->next;
			}
		}
		if (empty == paths_count)
			break;
		append_step(&result, step);
	}
	return (result);
}

void	generate_steps(t_graph *graph)
{
	t_path	*path;
	int		i;

	i = 1;
	path = graph->chosen_group->paths;
	while(path)
	{
		create_steps(path, i, graph->end_room);
		i += path->ants_count;
		path = path->next;
	}
	graph->steps = combine_steps(graph->chosen_group->paths, graph->chosen_group->number_of_paths);
}