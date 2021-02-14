/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.pattern.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:38:12 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/14 08:43:02 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libregex.h>
#include <stdlib.h>

/*
**	nfa_add_pattern push a new state to the nfa and try to create a link
**	between begin and this new state, with the next pattern in *ptr
**	returns a pointer to the new state on success, NULL otherwise
**
**	begin --> NULL	to	begin -[pattern]-> next_ns
*/

t_ns	*nfa_add_pattern(t_ns *ns_begin, t_alphabet **a, const char **ptr)
{
	t_nfa_state	*ns_next;
	t_pattern	pattern;

	ft_memset(pattern, 0, sizeof(pattern));
	if (**ptr == '[')
	{
		(*ptr)++;
		if (pattern_parse(&pattern, ptr))
			return (NULL);
	}
	else if (**ptr == '\\')
	{
		(*ptr)++;
		if (pattern_escape(&pattern, ptr))
			return (NULL);
	}
	else if (pattern_add_char(&pattern, *(*ptr)++))
		return (NULL);
	if (alphabet_add_pattern(a, pattern))
		return (NULL);
	if (!(ns_next = nfa_new_state()))
		return (NULL);
	link_add(ns_begin, pattern, ns_next);
	return (ns_next);
}
