/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.quantifiers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:37:26 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/03 10:43:54 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libregex.h"
#include <stdlib.h>

static t_state	*spe_length(t_state *beg, t_state *end, const char **p)
{
	return (NULL);
}

static t_state	*wildcard(t_state *beg, t_state *end, const char **ptr)
{
	t_state *new_beg;
	t_state *new_end;

	if (nfa_surruond(beg, end, &new_beg, &new_end) < 0)
		return (NULL);
	link_add(beg, pattern_epsilon(), new_end);
	link_add(end, pattern_epsilon(), new_beg);
	(*ptr)++;
	return (new_end);
}

static t_state	*plus(t_state *beg, t_state *end, const char **ptr)
{
	t_state *new_beg;
	t_state *new_end;

	if (nfa_surruond(beg, end, &new_beg, &new_end) < 0)
		return (NULL);
	link_add(end, pattern_epsilon(), new_beg);
	(*ptr)++;
	return (new_end);
}

static t_state	*imark(t_state *beg, t_state *end, const char **ptr)
{
	t_state *new_beg;
	t_state *new_end;

	if (nfa_surruond(beg, end, &new_beg, &new_end) < 0)
		return (NULL);
	link_add(beg, pattern_epsilon(), new_end);
	(*ptr)++;
	return (new_end);
}

t_state			*nfa_build_quantifier(t_state *b, t_state *e, const char **p)
{
	if (**p == '{')
		return (spe_length(b, e, p));
	if (**p == '*')
		return (wildcard(b, e, p));
	if (**p == '+')
		return (plus(b, e, p));
	if (**p == '?')
		return (imark(b, e, p));
	return (b);
}
