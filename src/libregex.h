/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libregex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:40:30 by bccyv             #+#    #+#             */
/*   Updated: 2021/01/29 09:41:41 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBREGEX_H
#define LIBREGEX_H

#include <stdbool.h>
#include <stddef.h>

#define DFL_VEC_CAPACITY 5

typedef struct s_nfa t_nfa;
typedef struct s_lnk t_lnk;
typedef struct s_lnkv t_lnkv;

/*
//	This structure represent the epsilon transition between two states of an NFA
//	It keeps a char, that must match our next string's char in order to go to
//	the next state
//	This next state is stored as a t_nfa pointer
*/
struct s_lnk
{
	char	c;
	t_nfa	*next;
};

/*
//	A dynamic array used by a NFA nodes to keep their epslion links
//	A reallocation occur when size == capacity
*/
struct s_lnkv
{
	t_lnk	*links;
	size_t	size;
	size_t	capacity;
};

/*
//	NFA stands for nondeterministic finite automaton
//	We will use this kind of automate to search for regex patterns
//	This structure stores a nfa node
*/
struct s_nfa
{
	bool		is_final_state;
	t_lnkv		links;
};


t_nfa *nfa_new_node(bool is_final_state);
int nfa_add_link(t_nfa *node, char c, t_nfa *next);
t_nfa *exprtonfa(const char *regexp);
bool dostrmatch(t_nfa *nfa, const char *str);

#endif
