/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:22:40 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/04 10:22:42 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	display_steps(t_step *step)
{
	t_move *move;

	ft_putchar('\n');
	while (step)
	{
		move = step->move;
		while (move)
		{
			ft_putchar('L');
			ft_putnbr(move->ant);
			ft_putchar('-');
			ft_putstr(move->room);
			ft_putchar(' ');
			move = move->next;
		}
		if (step->move)
			ft_putchar('\n');
		step = step->next;
	}
}

void	display_room(t_room *room)
{
	ft_putstr(room->name);
	ft_putchar(' ');
	ft_putnbr(room->x);
	ft_putchar(' ');
	ft_putnbr(room->y);
	ft_putchar('\n');
}

void	display_rooms(t_elem *room, t_room *start, t_room *end)
{
	while (room)
	{
		if (room->room != start && room->room != end)
			display_room(room->room);
		room = room->next;
	}
}

void	display_lines(t_line *list)
{
	while (list)
	{
		ft_putendl(list->name);
		list = list->next;
	}
}

void	display_data(t_graph *graph)
{
	ft_putnbr(graph->number_of_ants);
	ft_putchar('\n');
	ft_putendl("##start");
	display_room(graph->start_room);
	display_rooms(graph->list, graph->start_room, graph->end_room);
	ft_putendl("##end");
	display_room(graph->end_room);
	display_lines(graph->lines);
	display_steps(graph->steps);
}
