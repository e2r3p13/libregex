/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.pattern.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:38:12 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/03 08:45:56 by lfalkau          ###   ########.fr       */
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

static int pattern_length(const char *ptr)
{
	// TODO: For now it accepts everything in between hooks
	int i = 0;
	while (*ptr && *ptr != ']')
		ptr++;
	return (*ptr ? i : 0);
}

t_state *nfa_add_char_to(t_state *beg, const char **p)
{
	t_state		*new;
	t_pattern	pattern;
	int			plen;
	const char	*ptr;

	ptr = *p;
	if (!(new = state_new()))
		return (NULL);
	pattern.start = ptr;
	if (*ptr == '[' && (plen = pattern_length(ptr)))
		ptr += plen - 1;
	else if (*ptr == 92 && g_esc_table[(int)*(ptr + 1)]) // 92 is backslash
		ptr++;
	else if (*ptr == 92 || *ptr == '[' || !ft_isprint(*ptr))
	{
		free(new);
		return (NULL);
	}
	pattern.end = ptr;
	*p = ptr + 1;
	link_add(beg, pattern, new);
	return (new);
}
