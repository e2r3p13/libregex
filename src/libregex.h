/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libregex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:40:30 by bccyv             #+#    #+#             */
/*   Updated: 2021/02/02 14:50:51 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBREGEX_H
#define LIBREGEX_H

#include <stddef.h>
#include "libft.h"

typedef struct s_state t_state;
typedef struct s_link t_link;
typedef struct s_pattern t_pattern;
typedef struct s_automaton t_nfa;
typedef struct s_automaton t_dfa;
typedef struct s_automaton t_re;

/*
**	This structure represents a pattern substring from a regex string.
**	It internally keeps a pointer to the beginning of the substring,
**	and another one to the end.
*/
struct s_pattern
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
struct s_link
{
	int			(*match)(t_pattern s, int c);
	t_pattern	pattern;
	t_state		*next;
};

/*
**	t_state represents a state of an automaton.
**	It keeps two links which can lead to its two children (at most).
**	t_state nodes are used to construct our nfa / dfa.
*/
struct s_state
{
	t_bool	is_final;
	t_link	left;
	t_link	right;
};

/*
**	This structure represents an automaton, it keeps a pointer to its
**	entrypoint state (q0).
**	As this automaton will be used to store NFA and DFA, it also keeps a pointer
**	to an allocated string, containing the regex expression.
**	all t_pattern pointers that belongs to the automaton will point
**	somewhere in the regexpr string.
*/
struct s_automaton
{
	t_state *entrypoint;
	t_state *finalstate;
	char	*re_expr;
};

/*
**	t_state functions, will be used to construct an automaton.
*/
t_state		*state_new();
void		link_init(t_link *ln);
void		link_add(t_state *st, t_pattern pattern, t_state *next);
void		links_destroy(t_state *st);
void		links_cpy(t_state *dst, t_state *src);
t_nfa		*str_to_nfa(const char *str);
t_bool		nfa_match(t_nfa *nfa, const char *str);
void		nfa_free(t_nfa *nfa);
t_dfa		*nfa_to_dfa(t_nfa *entrypoint);
t_pattern	pattern_epsilon();
t_state		*nfa_create(t_state *beg, const char **ptr, t_bool nested);
void		nfa_print(t_state *st, int lvl);

#endif /* LIBREGEX_H */
