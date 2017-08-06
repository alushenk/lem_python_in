/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:23:58 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/04 10:23:59 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	errors_check(char *str, t_graph *graph)
{
	if (ft_strlen(str) > 0 && str[0] == 'L')
		error("Error! wrong parameters\n", graph);
	if (ft_strlen(str) == 0)
		error("Error! empty line\n", graph);
}

void	parse_ants(t_graph *graph, int fd, char *line)
{
	get_next_line(fd, &line);
	while (ft_strlen(line) > 0 && line[0] == '#')
	{
		free(line);
		get_next_line(fd, &line);
	}
	ft_putstr(line);
	ft_putchar('\n');
	graph->number_of_ants = err_atoi(line, graph);
	free(line);
	if (graph->number_of_ants == 0)
		error("Error! no ants given\n", graph);
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

void	parse_lines(t_graph *graph, int fd, char *line)
{
	while (line || get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		if (line[0] != '#')
			add_line(graph, line);
		free(line);
		line = NULL;
	}
}

void	parse(t_graph *graph, int fd)
{
	char	*line;

	line = NULL;
	parse_ants(graph, fd, line);
	parse_rooms(graph, fd, &line);
	parse_lines(graph, fd, line);
}
