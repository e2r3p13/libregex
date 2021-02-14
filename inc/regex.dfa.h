/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:41:09 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/14 10:12:49 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGEX_DFA_H
# define REGEX_DFA_H

# include <regex.nfa.h>
# include <libft.h>

# define SET_DFL_SIZE 8

typedef struct			s_link_lst
{
	t_link				link;
	struct s_link_lst	*next;
}						t_link_lst;

/*
**	t_ns represents a state of an automaton.
**	It keeps two links which can lead to its two children (at most).
**	t_ns nodes are used to construct our nfa / dfa.
*/
typedef struct			s_dfa_state
{
	t_bool				is_final;
	t_link_lst			*links;
	unsigned int		flag : 1;
}						t_ds;

typedef struct			s_set
{
	t_ns				**addr;
	size_t				size;
	size_t				capacity;
}						t_set;

typedef struct			s_map
{
	t_ds				*state;
	t_set				*set;
	struct s_map		*next;
}						t_map;

t_ds					*dfa_state_new(void);
int						dfa_create_connection(t_ds *f, t_pattern *p, t_ds *l);
t_set					*set_new();
int						set_push(t_ns *state, t_set *set);
t_bool					is_state_in_set(t_ns *state, t_set *set);
void					set_free(t_set *set);
t_bool					set_cmp(t_set *a, t_set *b);
t_ds					*state_in_map(t_map *map, t_set *set);
void					dfa_links_free(t_link_lst *links);
t_map					*map_new(t_ds *state, t_set *set);
void					map_push(t_map *dst, t_map *src);
void					dfa_state_free(t_ds *state);
void					map_free(t_map *map);
void					map_print(t_map *map);
void					set_print(t_set *set);
t_bool					set_contains_final_state(t_set *set);
void					dfa_free(t_ds *dfa);
t_ds					*dfa_generate(const char *str);
int						nfa_to_dfa(t_ds *entrypoint, t_ns *nfa, t_alphabet *a);

#endif
