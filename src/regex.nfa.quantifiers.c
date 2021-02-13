/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.quantifiers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:37:26 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/13 09:07:55 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.nfa.h>
#include <stdlib.h>

static t_ns	*wildcard(t_ns *beg, t_ns *end, const char **ptr)
{
	t_ns		*new_beg;
	t_ns		*new_end;
	t_pattern	epsilon;

	if (nfa_surruond(beg, end, &new_beg, &new_end) < 0)
		return (NULL);
	pattern_epsilon(&epsilon);
	link_add(beg, epsilon, new_end);
	link_add(end, epsilon, new_beg);
	(*ptr)++;
	return (new_end);
}

static t_ns	*plus(t_ns *beg, t_ns *end, const char **ptr)
{
	t_ns		*new_beg;
	t_ns		*new_end;
	t_pattern	epsilon;

	if (nfa_surruond(beg, end, &new_beg, &new_end) < 0)
		return (NULL);
	pattern_epsilon(&epsilon);
	link_add(end, epsilon, new_beg);
	(*ptr)++;
	return (new_end);
}

static t_ns	*imark(t_ns *beg, t_ns *end, const char **ptr)
{
	t_ns		*new_beg;
	t_ns		*new_end;
	t_pattern	epsilon;

	if (nfa_surruond(beg, end, &new_beg, &new_end) < 0)
		return (NULL);
	pattern_epsilon(&epsilon);
	link_add(beg, epsilon, new_end);
	(*ptr)++;
	return (new_end);
}

t_ns		*nfa_build_quantifier(t_ns *b, t_ns *e, const char **p)
{
	if (**p == '*')
		return (wildcard(b, e, p));
	if (**p == '+')
		return (plus(b, e, p));
	if (**p == '?')
		return (imark(b, e, p));
	return (e);
}
