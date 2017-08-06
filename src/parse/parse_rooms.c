/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 14:05:33 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/06 14:05:34 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	errors_check(char *str, t_graph *graph)
{
	if (ft_strlen(str) > 0 && str[0] == 'L')
		error("Error! wrong parameters\n", graph);
	if (ft_strlen(str) == 0)
		error("Error! empty line\n", graph);
}

int		is_room(char *str)
{
	if (*str == '#')
		return (1);
	while (*str)
	{
		if (*str == ' ')
			return (1);
		str++;
	}
	return (0);
}

void	parse_start(t_graph *graph, int fd, char **line)
{
	free(*line);
	if (get_next_line(fd, line) == 1)
	{
		ft_putstr(*line);
		ft_putchar('\n');
		errors_check(*line, graph);
		add_start(graph, *line);
	}
	else
		error("Error! no start found\n", graph);
}

void	parse_end(t_graph *graph, int fd, char **line)
{
	free(*line);
	if (get_next_line(fd, line) == 1)
	{
		ft_putstr(*line);
		ft_putchar('\n');
		errors_check(*line, graph);
		add_end(graph, *line);
	}
	else
		error("Error! no end found\n", graph);
}

void	parse_rooms(t_graph *graph, int fd, char **line)
{
	while (get_next_line(fd, line) == 1 && is_room(*line))
	{
		ft_putstr(*line);
		ft_putchar('\n');
		if (ft_strcmp(*line, "##start") == 0)
			parse_start(graph, fd, line);
		else if (ft_strcmp(*line, "##end") == 0)
			parse_end(graph, fd, line);
		else if (*line[0] != '#')
			add_room(graph, *line);
		free(*line);
		*line = NULL;
	}
}
