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

int		is_room(char *str, t_graph *graph)
{
	errors_check(str, graph);
	if (*str == '#')
		return (1);
	while (*str)
	{
		if (*str == ' ' &&
			(ft_isdigit(*(str + 1)) || *(str + 1) == '+' || *(str + 1) == '-'))
			return (1);
		str++;
	}
	return (0);
}

void	parse_start(t_graph *graph, int fd, char **line)
{
	free(*line);
	if (graph->start_room)
		error("Error! start room already exists\n", graph);
	if (get_next_write(fd, line, graph) == 1)
	{
		errors_check(*line, graph);
		graph->start_room = add_room(graph, *line);
	}
	else
		error("Error! no start found\n", graph);
}

void	parse_end(t_graph *graph, int fd, char **line)
{
	free(*line);
	if (graph->end_room)
		error("Error! end room already exists\n", graph);
	if (get_next_write(fd, line, graph) == 1)
	{
		errors_check(*line, graph);
		graph->end_room = add_room(graph, *line);
	}
	else
		error("Error! no end found\n", graph);
}

void	parse_rooms(t_graph *graph, int fd, char **line)
{
	while (get_next_write(fd, line, graph) == 1 && is_room(*line, graph))
	{
		if (ft_strcmp(*line, "##start") == 0)
			parse_start(graph, fd, line);
		else if (ft_strcmp(*line, "##end") == 0)
			parse_end(graph, fd, line);
		else if (*line[0] != '#')
		{
			errors_check(*line, graph);
			add_room(graph, *line);
		}
		free(*line);
		*line = NULL;
	}
}
