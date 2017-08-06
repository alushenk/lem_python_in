/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_steps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:23:17 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/04 10:23:18 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*perform_step(t_elem *list, t_step *step, int *name, int *index)
{
	t_room	*current_room;
	t_room	*next_room;
	t_move	*move;

	current_room = find_by_index(list, *index);
	next_room = find_by_index(list, *index + 1);
	if (next_room->is_free)
	{
		move = create_move(*name, next_room->name);
		add_move(step, move);
		next_room->is_free = 0;
		current_room->is_free = 1;
		*name += 1;
		*index -= 1;
	}
	return (next_room);
}

void	change_data(t_room *end, int *number_of_ants, int *name, int *i)
{
	end->is_free = 1;
	*number_of_ants -= 1;
	*name += 1;
	*i -= 1;
}
void	create_steps(t_path *path, int start_name, t_room *end, int i)
{
	t_step	*step;
	int		number_of_ants;
	int		index;
	int		ant_name;
	int		name;

	name = start_name;
	number_of_ants = path->ants_count;
	while (number_of_ants > 0)
	{
		step = create_step();
		index = i;
		ant_name = name;
		while (index >= 0 && ant_name < path->ants_count + start_name)
		{
			if (perform_step(path->list, step, &ant_name, &index) == end)
				change_data(end, &number_of_ants, &name, &i);
		}
		add_step(path, step);
		i++;
	}
}

void	toggle_next_step(t_path *path, int len)
{
	t_step	*temp;

	while (len > 0)
	{
		temp = path->steps;
		if (temp != NULL)
		{
			path->steps = temp->next;
		}
		free(temp);
		path->ended = 0;
		path = path->next;
		len--;
	}
}

int		pop_move(t_path *list, t_step *step, int ended)
{
	t_move	*move;

	move = list->steps->move;
	list->steps->move = move->next;
	if (move->next == NULL)
	{
		list->ended = 1;
		ended += 1;
	}
	move->next = NULL;
	add_move(step, move);
	return (ended);
}

void	combine_steps(t_step **result, t_path *list, int paths_count, int empty)
{
	t_step	*step;
	int		ended;

	while (empty < paths_count)
	{
		empty = 0;
		ended = 0;
		step = create_step();
		while (empty < paths_count && ended < paths_count)
		{
			list = list->next;
			if (list->steps == NULL && list->ended == 0)
			{
				list->ended = 1;
				empty += 1;
				ended += 1;
				continue;
			}
			if (list->ended == 1)
				continue;
			ended = pop_move(list, step, ended);
		}
		append_step(result, step);
		toggle_next_step(list, paths_count);
	}
}

void	generate_steps(t_graph *graph)
{
	t_path	*path;
	int		num;
	int		start_name;

	start_name = 1;
	path = graph->chosen_group->paths;
	while (1)
	{
		create_steps(path, start_name, graph->end_room, 0);
		start_name += path->ants_count;
		if (path->next == NULL)
		{
			path->next = graph->chosen_group->paths;
			break ;
		}
		path = path->next;
	}
	path = graph->chosen_group->paths;
	num = graph->chosen_group->number_of_paths;
	combine_steps(&graph->steps, path, num, 0);
}
