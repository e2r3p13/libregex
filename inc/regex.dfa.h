/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:41:09 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/12 18:20:34 by bccyv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGEX_DFA_H
#define REGEX_DFA_H

#include <regex.fa.h>
#include <regex.nfa.h>
#include <libft.h>

#define SET_DFL_SIZE 8

typedef struct s_set		t_set;
typedef struct s_map		t_map;
typedef struct s_link_lst	t_link_lst;
typedef struct s_dfa_state	t_ds;
typedef struct s_dfa		t_dfa;

struct s_set
{
	t_ns	**addr;
	size_t	size;
	size_t	capacity;
};

struct s_map
{
	t_ds	*state;
	t_set	*set;
	t_map	*next;
};

struct s_link_lst
{
	t_link		link;
	t_link_lst	*next;
};

/*
**	t_ns represents a state of an automaton.
**	It keeps two links which can lead to its two children (at most).
**	t_ns nodes are used to construct our nfa / dfa.
*/
struct	s_dfa_state
{
	t_bool			is_final;
	t_link_lst		*links;
	unsigned int	flag : 1;
};

/*
**	This structure represents a deterministic finite automaton.
**	It keeps a pointer to its entry state.
**	It also keeps a pointer to an allocated string,
**	containing the regex expression.
*/
struct s_dfa
{
	t_ds	*entrypoint;
	char	*re_expr;
};

t_dfa	*dfa_new(void);
t_ds	*dfa_state_new(void);
int		dfa_create_connection(t_ds *first, t_pattern *p, t_ds *last);
t_set	*set_new();
int		set_push(t_ns *state, t_set *set);
t_bool	is_state_in_set(t_ns *state, t_set *set);
void	set_free(t_set *set);
t_bool	set_cmp(t_set *a, t_set *b);
t_ds	*state_in_map(t_map *map, t_set *set);
void	dfa_links_free(t_link_lst *links);
t_map	*map_new(t_ds *state, t_set *set);
void	map_push(t_map *dst, t_map *src);
void	dfa_state_free(t_ds *state);
void	map_free(t_map *map);
t_dfa	*nfa_to_dfa(t_nfa *nfa);
void	dfa_print(t_dfa *dfa);

#endif /* REGEX_DFA_H */
