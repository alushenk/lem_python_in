/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 14:42:51 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/19 14:42:52 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

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
