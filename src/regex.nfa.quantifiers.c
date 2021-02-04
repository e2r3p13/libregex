/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.quantifiers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:37:26 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/04 14:50:32 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libregex.h"
#include <stdlib.h>

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

static int		parse_length(int *min, int *max, const char **ptr)
{
	(*ptr)++;
	if ((*min = ft_atoi(*ptr)) <= 0)
		return (-1);
	*max = *min;
	while (ft_isdigit(**ptr))
		(*ptr)++;
	if (**ptr == ',')
	{
		(*ptr)++;
		if (**ptr == '}')
			*max = -1;
		else if ((*max = ft_atoi(*ptr)) < *min)
			return (-1);
		else
			while (ft_isdigit(**ptr))
				(*ptr)++;
	}
	if (**ptr != '}')
		return (-1);
	(*ptr)++;
	return (0);
}

static t_state	*spe_length(__unused t_state *beg, t_state *end, const char **ptr)
{
	int		min;
	int		max;
	// int		i;
	// t_state	*tmp;

	if (parse_length(&min, &max, ptr) < 0)
		return (NULL);
	if (min == 0)
	{
		if (max == -1)
			return (wildcard(beg, end, ptr));
		else if (max == 0)
			return (NULL);
		else if (max == 1)
			return (imark(beg, end, ptr));
	}
	// i = 1;
	// while (i < min)
	// {
	// 	tmp = end;
	// 	if (!(end = dupcat(beg)))
	// 		return (NULL);
	// 	beg = tmp;
	// 	i++;
	// }
	return (end);
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
	return (e);
}
