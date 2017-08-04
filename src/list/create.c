/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 11:10:11 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/04 11:10:13 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_elem	*create_element(void)
{
	t_elem *result;

	result = (t_elem*)malloc(sizeof(t_elem));
	result->room = NULL;
	result->next = NULL;
	return (result);
}

t_path	*create_path(void)
{
	t_path *result;

	result = (t_path*)malloc(sizeof(t_path));
	result->list = NULL;
	result->weight = 0;
	result->ants_count = 0;
	result->ended = 0;
	result->next = NULL;
	return (result);
}

t_group	*create_group(void)
{
	t_group *group;

	group = (t_group*)malloc(sizeof(t_group));
	group->paths = NULL;
	group->efficiency = 0;
	group->number_of_paths = 0;
	group->next = NULL;
	return (group);
}

t_step	*create_step(void)
{
	t_step	*result;

	result = (t_step*)malloc(sizeof(t_step));
	result->move = NULL;
	result->next = NULL;
	return (result);
}

t_move	*create_move(int ant, char *room)
{
	t_move *result;

	result = (t_move*)malloc(sizeof(t_move));
	result->ant = ant;
	result->room = room;
	result->next = NULL;
	return (result);
}
