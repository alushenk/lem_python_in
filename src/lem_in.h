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
	int				dist;
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
	int				efficiency;
	struct s_group	*next;
}					t_group;

typedef struct		s_line
{
	char			*name;
	struct s_line	*next;
}					t_line;

typedef struct		s_graph
{
	int				number_of_ants;
	t_room			*start_room;
	t_room			*end_room;
	t_elem			*list;
	t_line			*lines;
	t_path			*paths;
	t_group			*groups;
	t_group			*chosen_group;
	t_step			*steps;
}					t_graph;

/*
** graph.c
*/
t_graph				*create_graph();
void				add_line(t_graph *graph, char *str);
char				*ft_strsep(char **str, char sep);
/*
** errors.c
*/
void				error(char *str, t_graph *graph);
/*
** parse/parse.c
*/
void				parse(t_graph *graph, int fd);
/*
** parse/parse_rooms.c
*/
void				parse_rooms(t_graph *graph, int fd, char **line);
void				errors_check(char *str, t_graph *graph);
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
void				connect(t_room *a, t_room *b);
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
t_room				*add_room(t_graph *graph, char *str);
void				pop_room(t_room *a, t_room *b);
/*
** search.c
*/
void				get_all_paths(t_graph *graph);
t_path				*find_paths(t_room *start, t_room *end, t_path *path);
/*
** free.c
*/
void				free_graph(t_graph *graph);
void				free_list(t_elem *list);
void				free_lines(t_line *line);
void				free_rooms(t_elem *list);
void				free_paths(t_path *path);
void				free_groups(t_group *group);
/*
** display.c
*/
void				display_path(t_path *path);
void				display_paths(t_path *paths);
void				display_groups(t_group *groups);
void				display_steps(t_step *step);
void				display_data(t_graph *graph);
void				display_lines(t_line *list);
/*
** find_path_groups.c
*/
void				find_path_groups(t_graph *graph);
void				find_groups(t_graph *graph, int i);
/*
** choose_path_group.c
*/
void				choose_path_group(t_graph *graph);
void				calc_group_efficiency(t_group *group, int number_of_ants);
t_group				*find_optimal_group(t_group *group);
/*
** generate_steps.c
*/
void				generate_steps(t_graph *graph);
/*
** create_steps.c
*/
void				create_steps(t_path *path, int start, t_room *end, int i);
/*
** get_next_write.c
*/
int					get_next_write(const int fd, char **str, t_graph *graph);
/*
** reset.c
*/
void				reset_rooms(t_elem *list);
void				hard_reset_rooms(t_elem *list);
/*
** calculate.c
*/
void				calculate_graph(t_room *room);
/*
** find_path_groups_helpers.c
*/
void				append_to_group(t_group **list, t_group *group);
void				disconnect(t_room *a, t_room *b);
t_group				*find_group(t_graph *graph);
/*
** find.c
*/
t_path				*find_shortest(t_path *path);
t_path				*find_hardest(t_path *path);
int					find_path_weigth(t_path *path);

#endif
