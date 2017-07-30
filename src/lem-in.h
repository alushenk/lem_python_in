//
// Created by lush on 7/28/17.
//

#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H

#include <stdio.h>
# include <stdlib.h>
# include <limits.h>
#include "../get_next_line/get_next_line.h"

typedef struct		s_link
{
	t_room			*room;
	struct s_link	*next;
}					t_link;

typedef struct		s_room
{
	char 			*name;
	int 			x;
	int 			y;
	t_link			*links;
	struct s_room	*next;
	struct s_room	*prev;
}					t_room;

typedef struct		s_graph
{
	int				number_of_ants;
	int 			number_of_rooms;
	t_room			*start_room;
	t_room			*end_room;
	t_room			*list;

}					t_graph;

/*
 * graph.c
 */
t_graph *create_graph();
t_room	*add_room(t_graph *graph, char *str);
void	add_start(t_graph *graph, char *str);
void	add_end(t_graph *graph, char *str);
void	add_line(t_graph *graph, char *str);
/*
 * errors.c
 */
void error(char *str);
/*
 * parsing.c
 */
void	parse(t_graph *graph, int fd);
/*
 * err_atoi.c
 */
int		err_atoi(const char *str);
/*
 * room.c
 */
t_room	*create_room(char *name, int x, int y);
t_room	*find_by_name(t_room *list, char *name);
void	connect(t_room *a, t_room *b);
/*
 * links.c
 */
t_link	*create_link(t_room *room);

#endif //LEM_IN_LEM_IN_H
