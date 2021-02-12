/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:40:58 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/12 17:57:06 by bccyv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGEX_NFA_H
#define REGEX_NFA_H

#include <libft.h>
#include <regex.fa.h>

typedef struct s_nfa_state	t_ns;
typedef struct s_nfa_state	t_nfa_state;
typedef struct s_vec		t_vec;
typedef struct s_nfa		t_nfa;
typedef struct s_alphabet	t_alphabet;

/*
**	t_ns represents a state of an automaton.
**	It keeps two links which can lead to its two children (at most).
**	t_ns nodes are used to construct our nfa / dfa.
*/
struct	s_nfa_state
{
	t_bool			is_final;
	t_link			left;
	t_link			right;
	unsigned int	flag : 1;
};

/*
**	A simple vector structure used to store nfa states addresses.
*/
struct s_vec
{
	size_t	size;
	void	**addr;
};

/*
//	A linked list containing all accepted patterns
*/
struct s_alphabet
{
	t_pattern	pattern;
	t_alphabet	*next;
};

/*
**	This structure represents a non deterministic finite automaton.
**	It keeps a pointer to its entry state, and to its final state.
**	It also keeps a pointer to an allocated string,
**	containing the regex expression.
*/
struct	s_nfa
{
	t_ns		*entrypoint;
	char		*re_expr;
	t_alphabet	*alphabet;
};

t_ns		*state_new(void);
void		link_init(t_link *ln);
void		link_add(t_ns *st, t_pattern pattern, t_ns *next);
void		links_destroy(t_ns *st);
void		links_cpy(t_ns *dst, t_ns *src);
t_nfa		*str_to_nfa(const char *str);
t_bool		nfa_match(t_nfa *nfa, const char *str);
void		nfa_free(t_nfa *nfa);
void		pattern_epsilon(t_pattern *pattern);
t_ns		*nfa_create(t_ns *beg, const char **ptr, t_bool nested);
t_ns		*nfa_build_or(t_ns *b, t_ns *e, const char **p, t_bool n);
t_ns		*nfa_add_pattern(t_ns *beg, const char **p);
t_ns		*nfa_build_quantifier(t_ns *b, t_ns *e, const char **p);
int			nfa_surruond(t_ns *b, t_ns *e, t_ns **nb, t_ns **ne);
t_nfa		*nfa_new(const char *str);
void		nfa_print(t_nfa *nfa);
t_bool		nfa_has_link(t_pattern *p, t_ns *state);
t_bool		pattern_cmp(t_pattern *a, t_pattern *b);

#endif /* REGEX_NFA_H */
