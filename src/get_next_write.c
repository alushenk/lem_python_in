/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 14:35:01 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/08 14:35:02 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_line	*create_line(char *str)
{
	t_line *result;

	result = (t_line*)malloc(sizeof(t_line));
	result->name = ft_strdup(str);
	result->next = NULL;
	return (result);
}

int get_next_write(const int fd, char **str, t_graph *graph)
{
	int		result;
	t_line	*line;
	t_line	*elem;

	result = get_next_line(fd, str);
	line = create_line(*str);
	elem = graph->lines;
	if (elem == NULL)
		graph->lines = line;
	else
	{
		while (elem->next)
			elem = elem->next;
		elem->next = line;
	}
	return (result);
}
