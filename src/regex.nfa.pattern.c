/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.pattern.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:38:12 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/03 09:16:28 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libregex.h"
#include "libft.h"
#include <stdlib.h>

void *g_esc_table[128] =
{
	['c'] = &ft_iscontrol,
	['s'] = &ft_isspace,
	['S'] = &ft_isntspace,
	['d'] = &ft_isdigit,
	['D'] = &ft_isntdigit,
	['w'] = &ft_isworld,
	['W'] = &ft_isntworld,
	['x'] = &ft_ishexdigit,
	['O'] = &ft_isoctaldigit,
	['n'] = &ft_isnewline,
	['r'] = &ft_iscarriage,
	['t'] = &ft_ishtab,
	['v'] = &ft_isvtab,
	['f'] = &ft_isffeed
};

/*
**	pattern_length returns 0 if a [] pattern is invalid, otherwise, it returns
**	the length of the pattern, including the enclosing "[]"
*/

static int	pattern_length(const char *ptr)
{
	int i;

	i = 0;
	while (*ptr && *ptr != ']')
	{
		i++;
		ptr++;
	}
	return (*ptr ? i : 0);
}

/*
**	nfa_add_pattern push a new state to the nfa and try to create a link
**	between begin and this new state, with the next pattern in *ptr
**	returns a pointer to the new state on success, NULL otherwise
*/

t_state		*nfa_add_pattern(t_state *beg, const char **ptr)
{
	t_state		*next_state;
	t_pattern	pattern;
	int			plen;

	if (!(next_state = state_new()))
		return (NULL);
	pattern.start = *ptr;
	if (**ptr == '[' && (plen = pattern_length(*ptr)))
		*ptr += plen;
	else if (**ptr == 92 && (g_esc_table[(int)*(*ptr + 1)] ||
		ft_isinset(SPE_CHAR, **ptr)))
		(*ptr)++;
	else if (**ptr == 92 || **ptr == '[' || !ft_isprint(**ptr) ||
		ft_isinset(SPE_CHAR, **ptr))
	{
		free(next_state);
		return (NULL);
	}
	pattern.end = *ptr;
	(*ptr)++;
	link_add(beg, pattern, next_state);
	return (next_state);
}
