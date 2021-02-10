/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:41:09 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/10 11:30:45 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGEX_DFA_H
#define REGEX_DFA_H

#include <regex.fa.h>

typedef struct s_dfa_state	t_ds;
typedef struct s_dfa		t_dfa;

/*
**	t_ns represents a state of an automaton.
**	It keeps two links which can lead to its two children (at most).
**	t_ns nodes are used to construct our nfa / dfa.
*/
struct	s_dfa_state
{
	t_bool			is_final;
	t_vlink			links;
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

#endif /* REGEX_DFA_H */
