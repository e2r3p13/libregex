/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:37:02 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/14 10:29:31 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.nfa.h>
#include <stdlib.h>

int		nfa_surruond(t_ns *b, t_ns *e, t_ns **nb, t_ns **ne)
{
	t_pattern	epsilon;

	if (!(*nb = nfa_new_state()))
		return (-1);
	if (!(*ne = nfa_new_state()))
	{
		free(*nb);
		return (-1);
	}
	links_cpy(*nb, b);
	links_destroy(b);
	pattern_epsilon(&epsilon);
	link_add(b, epsilon, *nb);
	link_add(e, epsilon, *ne);
	return (0);
}

t_ns	*nfa_create(t_ns *beg, t_alphabet **a, const char **ptr, t_bool nested)
{
	t_ns		*end;
	t_ns		*tmp;

	if (!beg)
		return (NULL);
	end = beg;
	while (nested ? **ptr && **ptr != ')' : **ptr)
	{
		tmp = end;
		if (**ptr == '(' && (*ptr)++)
		{
			if (!(end = nfa_create(end, a, ptr, true)) || **ptr != ')')
				return (NULL);
			(*ptr)++;
		}
		else if (!(end = nfa_add_pattern(end, a, ptr)))
			return (NULL);
		if (ft_isinset("*+?", **ptr) &&
			!(end = nfa_build_quantifier(tmp, end, ptr)))
			return (NULL);
		if (**ptr == '|' && !(end = nfa_build_or(beg, a, end, ptr, nested)))
			return (NULL);
	}
	return (end);
}

t_ns	*str_to_nfa(const char *str, t_alphabet **a)
{
	t_ns		*entrypoint;
	t_ns		*final;

	if (!(entrypoint = nfa_new_state()))
		return (NULL);
	if (!(final = nfa_create(entrypoint, a, &str, false)))
	{
		nfa_free(entrypoint);
		return (NULL);
	}
	final->is_final = true;
	return (entrypoint);
}
