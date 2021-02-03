/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.quantifiers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:37:26 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/03 11:26:13 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libregex.h"
#include <stdlib.h>

static t_state	*spe_length(__unused t_state *beg, t_state *end, const char **ptr)
{
	int min;
	int max;

	(*ptr)++;
	if ((min = ft_atoi(*ptr)) <= 0)
		return (NULL);
	while (ft_isdigit(**ptr))
		(*ptr)++;
	if (**ptr == ',')
	{
		(*ptr)++;
		if (**ptr == '}')
			max = -1;
		else if ((max = ft_atoi(*ptr)) < min)
			return (NULL);
		else
			while (ft_isdigit(**ptr))
				(*ptr)++;
	}
	if (**ptr != '}')
		return (NULL);
	(*ptr)++;
	return (end);
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
