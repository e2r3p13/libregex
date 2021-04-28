/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:37:02 by lfalkau           #+#    #+#             */
/*   Updated: 2021/04/28 19:54:06 by glafond-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <regex.fa.h>
#include <regex.ft.h>

static void	nfa_modifier(t_ns *ns[3], const char **ptr, int nested,
				t_alphabet **a)
{
	t_ns		*beg_end[2];

	if (ft_isinset("*+?", **ptr))
		ns[1] = nfa_quantifier(ns[2], ns[1], ptr);
	if (**ptr == '|')
	{
		beg_end[0] = ns[0];
		beg_end[1] = ns[1];
		ns[1] = nfa_or(beg_end, ptr, nested, a);
	}
}

/*
**	Converts a string into a NFA, following the Thompson's construction method.
**	See ttps://tajseer.files.wordpress.com/2014/06/re-nfa-dfa.pdf.
*/

t_ns	*nfa_create(t_ns *beg, const char **ptr, int nested, t_alphabet **a)
{
	t_ns		*ns[3];

	if (!beg)
		return (NULL);
	ns[0] = beg;
	ns[1] = beg;
	while (**ptr && (!nested || **ptr != ')'))
	{
		ns[2] = ns[1];
		if (**ptr == '(' && (*ptr)++)
		{
			ns[1] = nfa_create(ns[1], ptr, 1, a);
			if (!ns[1] || *(*ptr)++ != ')')
				return (NULL);
		}
		else
			ns[1] = nfa_pattern(ns[1], ptr, a);
		nfa_modifier(ns, ptr, nested, a);
		if (!ns[1])
			return (NULL);
	}
	return (ns[1]);
}

t_ns	*nfa_generate(const char *str, t_alphabet **a)
{
	t_ns	*entrypoint;
	t_ns	*final_state;

	if (*str == '\0')
		return (NULL);
	entrypoint = nfa_state_new();
	if (!entrypoint)
		return (NULL);
	final_state = nfa_create(entrypoint, &str, 0, a);
	if (!final_state)
	{
		nfa_free(entrypoint);
		return (NULL);
	}
	final_state->is_final = 1;
	return (entrypoint);
}
