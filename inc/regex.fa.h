/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.fa.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:27:43 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/19 14:57:35 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGEX_FA_H
# define REGEX_FA_H

# include <libregex.h>
# include <stddef.h>

/*
**	Size of the first allocation for the t_set dynamic array.
*/
# define SET_DFL_SIZE 8

/*
**	t_ns represents a state of a non deterministic finite automaton.
*/
typedef struct s_nfa_state
{
	int			is_final;
	t_link		left;
	t_link		right;
	uint8_t		flag : 1;
}	t_ns;

/*
**	A simple vector structure used to store nfa states addresses.
*/
typedef struct s_vec
{
	size_t	size;
	void	**addr;
}	t_vec;

/*
**	t_set is a dynamic array of nfa states pointers.
**	Used to generate a dfa from a nfa.
*/
typedef struct s_set
{
	t_ns	**addr;
	size_t	size;
	size_t	capacity;
}	t_set;

/*
**	t_map associates a t_set with a dfa state. It stores a list of those
**	associations.
**	Used to generate a dfa from a nfa.
*/
typedef struct s_map
{
	t_ds			*state;
	t_set			*set;
	struct s_map	*next;
}	t_map;

/* ************************************************************************** */
/*	NFA related functions                                                     */
/* ************************************************************************** */

t_ns		*nfa_generate(const char *str, t_alphabet **a);
t_ns		*nfa_create(t_ns *b, const char **p, int nested, t_alphabet **a);
t_ns		*nfa_state_new(void);
void		nfa_free(t_ns *nfa);

size_t		nfa_get_size(t_ns *st);
void		nfa_get_addresses(t_ns *st, t_vec *v);

void		nfa_link_init(t_link *ln);
void		nfa_link_add(t_ns *st, t_pattern pattern, t_ns *next);
void		nfa_links_destroy(t_ns *st);
void		nfa_links_cpy(t_ns *dst, t_ns *src);
int			nfa_has_link(t_pattern *p, t_ns *state);


/* ************************************************************************** */
/*	DFA related functions                                                     */
/* ************************************************************************** */

t_ds		*dfa_generate(const char *str);
int			dfa_create(t_map *st_map, t_map *hole_map, t_alphabet *a);
t_ds		*dfa_state_new(void);
void		dfa_free(t_ds *dfa);

void		dfa_get_addresses(t_ds *st, t_vec *v);
size_t		dfa_get_size(t_ds *st);

int			dfa_create_connection(t_ds *f, t_pattern *p, t_ds *l);

t_set		*set_new(void);
int			set_push(t_ns *state, t_set *set);
void		set_free(t_set *set);
int			is_state_in_set(t_ns *state, t_set *set);
int			set_cmp(t_set *a, t_set *b);
int			set_contains_final_state(t_set *set);
int			e_closure(t_ns *state, t_set *dst);
int			e_move_closure(t_set *src, t_pattern *p, t_set *dst);

t_map		*map_new(t_ds *state, t_set *set);
void		map_push(t_map *dst, t_map *src);
void		map_free(t_map *map);
t_ds		*state_in_map(t_map *map, t_set *set);

/* ************************************************************************** */
/*	Pattern related functions                                                 */
/* ************************************************************************** */

int			pattern_add_char(t_pattern *p, int c);
int			pattern_add_range(t_pattern *p, int s, int e);
int			pattern_add_pattern(t_pattern *dest, char *src);
int			pattern_parse(t_pattern *p, const char **ptr);
int			pattern_escape(t_pattern *p, const char **ptr);
void		pattern_epsilon(t_pattern *p);
int			is_epsilon(t_pattern p);
int			pattern_match(t_pattern p, int c);
int			pattern_copy(t_pattern dst, t_pattern src);
int			pattern_cmp(t_pattern a, t_pattern b);
int			alphabet_add_pattern(t_alphabet **head, t_pattern pattern);
void		alphabet_free(t_alphabet *a);

/* ************************************************************************** */
/*	Debug functions                                                           */
/* ************************************************************************** */

void		pattern_print(t_pattern pattern);
void		nfa_print(t_ns *nfa);
void		dfa_print(t_ds *entrypoint);

#endif
