/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:40:58 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/10 11:11:58 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGEX_NFA_H
#define REGEX_NFA_H

#include <libft.h>

typedef struct s_pattern	t_pattern;
typedef struct s_link		t_link;
typedef struct s_state		t_state;
typedef struct s_vec		t_vec;
typedef struct s_nfa		t_nfa;

/*
**	This structure represents a pattern substring from a regex string.
**	It internally keeps a pointer to the beginning of the substring,
**	and another one to the end.
*/
struct	s_pattern
{
	const char *start;
	const char *end;
};

/*
**	This structure represents a link to go from one state to another.
**	In order to follow the link, the next input character must
**	match the stored pattern.
**	It can be evaluated with the match function.
**	A link with a next set to NULL is considered to be an epsilon link,
**	meaning the match function will always return true.
*/
struct	s_link
{
	int			(*match)(t_pattern s, int c);
	t_pattern	pattern;
	void		*next;
};

/*
**	t_state represents a state of an automaton.
**	It keeps two links which can lead to its two children (at most).
**	t_state nodes are used to construct our nfa / dfa.
*/
struct	s_state
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
	t_state	**addr;
};

/*
**	This structure represents a non deterministic finite automaton.
**	It keeps a pointer to its entry state, and to its final state.
**	It also keeps a pointer to an allocated string,
**	containing the regex expression.
*/
struct	s_nfa
{
	t_state	*entrypoint;
	char	*re_expr;
};

t_state		*state_new(void);
void		link_init(t_link *ln);
void		link_add(t_state *st, t_pattern pattern, t_state *next);
void		links_destroy(t_state *st);
void		links_cpy(t_state *dst, t_state *src);
t_nfa		*str_to_nfa(const char *str);
t_bool		nfa_match(t_nfa *nfa, const char *str);
void		nfa_free(t_nfa *nfa);
t_pattern	pattern_epsilon(void);
t_state		*nfa_create(t_state *beg, const char **ptr, t_bool nested);
t_state		*nfa_build_or(t_state *b, t_state *e, const char **p, t_bool n);
t_state		*nfa_add_pattern(t_state *beg, const char **p);
t_state		*nfa_build_quantifier(t_state *b, t_state *e, const char **p);
int			nfa_surruond(t_state *b, t_state *e, t_state **nb, t_state **ne);
t_nfa		*nfa_new(const char *str);
void		nfa_print(t_nfa *nfa);

#endif /* REGEX_NFA_H */
