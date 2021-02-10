/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:41:09 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/10 11:10:37 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGEX_DFA_H
#define REGEX_DFA_H

typedef struct s_dfa	t_dfa;

/*
**	This structure represents a deterministic finite automaton.
**	It keeps a pointer to its entry state.
**	It also keeps a pointer to an allocated string,
**	containing the regex expression.
*/
struct s_dfa
{
	t_state	*entrypoint;
	char	*re_expr;
};

#endif /* REGEX_DFA_H */
