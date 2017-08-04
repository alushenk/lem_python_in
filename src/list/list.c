/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 11:10:38 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/04 11:10:39 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_path	*copy_path(t_path *path)
{
	t_path	*result;
	t_elem	*elem;

	result = create_path();
	if (path == NULL)
		return (result);
	elem = path->list;
	while (elem)
	{
		add_to_path(result, elem->room);
		elem = elem->next;
	}
	return (result);
}
