/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:37:02 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/03 10:41:38 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libregex.h"
#include <stdlib.h>

void			nfa_free(t_nfa *nfa)
{
	(void)nfa;
}

static t_nfa	*nfa_new(const char *str)
{
	t_nfa *nfa;

	if (!str || !(nfa = malloc(sizeof(t_nfa))))
		return (NULL);
	ft_bzero(nfa, sizeof(t_nfa));
	if (!(nfa->re_expr = ft_strdup(str)))
	{
		free(nfa);
		return (NULL);
	}
	if (!(nfa->entrypoint = state_new()))
	{
		nfa_free(nfa);
		return (NULL);
	}
	nfa->finalstate = NULL;
	return (nfa);
}

int				nfa_surruond(t_state *b, t_state *e, t_state **nb, t_state **ne)
{
	if (!(*nb = state_new()))
		return (-1);
	if (!(*ne = state_new()))
	{
		free(*nb);
		return (-1);
	}
	links_cpy(*nb, b);
	links_destroy(b);
	link_add(b, pattern_epsilon(), *nb);
	link_add(e, pattern_epsilon(), *ne);
	return (0);
}

t_state			*nfa_create(t_state *beg, const char **ptr, t_bool nested)
{
	t_state	*end;
	t_state	*tmp;

	if (!beg)
		return (NULL);
	end = beg;
	while (nested ? **ptr && **ptr != ')' : **ptr)
	{
		tmp = end;
		if (**ptr == '(' && (*ptr)++)
		{
			if (!(end = nfa_create(end, ptr, true)) || **ptr != ')')
				return (NULL);
			(*ptr)++;
		}
		else if (!(end = nfa_add_pattern(end, ptr)))
			return (NULL);
		if (!(end = nfa_build_quantifier(tmp, end, ptr)))
			return (NULL);
		if (**ptr == '|' && !(end = nfa_build_or(beg, end, ptr, nested)))
			return (NULL);
	}
	return (end);
}

t_nfa			*str_to_nfa(const char *str)
{
	t_nfa		*nfa;
	const char	*ptr;

	if (!(nfa = nfa_new(str)))
		return (NULL);
	ptr = nfa->re_expr;
	if (!(nfa->finalstate = nfa_create(nfa->entrypoint, &ptr, false)))
	{
		nfa_free(nfa);
		return (NULL);
	}
	nfa->finalstate->is_final = true;
	return (nfa);
}
