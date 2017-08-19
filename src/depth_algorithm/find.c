/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 14:50:08 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/19 14:50:09 by alushenk         ###   ########.fr       */
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
