/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libregex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:40:30 by bccyv             #+#    #+#             */
/*   Updated: 2021/01/29 16:20:15 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBREGEX_H
#define LIBREGEX_H

#include <stdbool.h>
#include <stddef.h>

#define DFL_VEC_CAPACITY 5

typedef struct s_nfa t_nfa;
typedef struct s_link t_link;
typedef struct s_substr t_substr;

struct s_substr;
{
	const char *start;
	const char *end;
};

/*
**	This structure represent the epsilon transition between two states of an NFA
**	It keeps a char, that must match our next string's char in order to go to
**	the next state
**	This next state is stored as a t_nfa pointer
*/
struct s_link
{
	bool		(*match)(t_substr s, char c);
	t_substr	substr;
	t_nfa		*next;
};

/*
**	NFA stands for nondeterministic finite automaton
**	We will use this kind of automate to search for regex patterns
**	This structure stores a nfa node
*/
struct s_nfa
{
	bool	is_final_state;
	t_link	left;
	t_link	right;
};

t_nfa *nfa_new_node(bool is_final_state);
int nfa_add_link(t_nfa *node, char c, t_nfa *next);
t_nfa *exprtonfa(const char *regexp);
bool dostrmatch(t_nfa *nfa, const char *str);

#endif
