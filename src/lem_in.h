/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:23:39 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/04 10:23:40 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_LEM_IN_H
# define LEM_IN_LEM_IN_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include "../get_next_line/get_next_line.h"

typedef struct		s_elem
{
	struct s_room	*room;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				is_free;
	t_elem			*list;
}					t_room;

typedef struct		s_move
{
	int				ant;
	char			*room;
	struct s_move	*next;
}					t_move;

typedef struct		s_step
{
	t_move			*move;
	struct s_step	*next;
}					t_step;

typedef struct		s_path
{
	t_elem			*list;
	t_step			*steps;
	int				weight;
	int				ants_count;
	int				ended;
	struct s_path	*next;
}					t_path;

typedef struct		s_group
{
	t_path			*paths;
	int				number_of_paths;
	size_t			efficiency;
	struct s_group	*next;
}					t_group;

typedef struct		s_graph
{
	int				number_of_ants;
	t_room			*start_room;
	t_room			*end_room;
	t_elem			*list;
	t_path			*paths;
	t_group			*groups;
	t_group			*chosen_group;
	t_step			*steps;
}					t_graph;

/*
** graph.c
*/
t_graph				*create_graph();
t_room				*add_room(t_graph *graph, char *str);
void				add_start(t_graph *graph, char *str);
void				add_end(t_graph *graph, char *str);
void				add_line(t_graph *graph, char *str);
/*
** errors.c
*/
void				error(char *str, t_graph *graph);
/*
** parsing.c
*/
void				parse(t_graph *graph, int fd);
/*
** err_atoi.c
*/
int					err_atoi(const char *str, t_graph *graph);
/*
** room.c
*/
t_room				*create_room(char *name, int x, int y);
t_room				*find_by_name(t_elem *list, char *name);
t_room				*find_by_id(t_elem *list, t_room *room);
t_room				*find_by_index(t_elem *list, int index);
void				connect(t_room *a, t_room *b, t_graph *graph);
/*
** list.c
*/
t_elem				*create_element();
t_path				*create_path();
void				add_to_path(t_path *path, t_room *room);
t_path				*copy_path(t_path *path);
t_step				*create_step();
void				add_step(t_path *path, t_step *step);
t_move				*create_move(int ant, char *room);
void				add_move(t_step *step, t_move *move);
t_group				*create_group();
void				add_path(t_group *group, t_path *path);
void				append_step(t_step	**list, t_step *step);
/*
** search.c
*/
void				get_all_paths(t_graph *graph);
t_path				*find_paths(t_room *start, t_room *end, t_path *path);
/*
** free.c
*/
void				free_list(t_elem *list);
void				free_graph(t_graph *graph);
/*
** display.c
*/
void				display_path(t_path *path);
void				display_paths(t_path *paths);
void				display_groups(t_group *groups);
void				display_steps(t_step *step);
/*
** find_path_groups.c
*/
void				find_path_groups(t_graph *graph);
/*
** choose_path_group.c
*/
void				choose_path_group(t_graph *graph);
/*
** generate_steps.c
*/
void				generate_steps(t_graph *graph);

#endif
