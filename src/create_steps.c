/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_steps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 14:27:33 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/06 14:27:34 by alushenk         ###   ########.fr       */
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

void	create_steps(t_path *path, int start, t_room *end, int i)
{
	t_step	*step;
	int		number_of_ants;
	int		index;
	int		ant_name;
	int		name;

	name = start;
	number_of_ants = path->ants_count;
	while (number_of_ants > 0)
	{
		step = create_step();
		index = i;
		ant_name = name;
		while (index >= 0 && ant_name < path->ants_count + start)
		{
			if (perform_step(path->list, step, &ant_name, &index) == end)
				change_data(end, &number_of_ants, &name, &i);
		}
		add_step(path, step);
		i++;
	}
}
