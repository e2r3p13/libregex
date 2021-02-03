/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:37:02 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/03 08:48:16 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libregex.h"
#include <stdlib.h>

void nfa_free(t_nfa *nfa)
{
	// TODO: free each allocated states
	free(nfa->re_expr);
	free(nfa);
}

static t_nfa *nfa_new(const char *str)
{
	t_nfa *nfa;

	if (!str || !(nfa = malloc(sizeof(t_nfa))))
		return (NULL);
	ft_bzero(nfa, sizeof(t_nfa));
	if (!(nfa->re_expr = ft_strdup(str)))
	{
		nfa_free(nfa);
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

t_state *nfa_create(t_state *beg, const char **ptr, t_bool nested)
{
	t_state *end;

	if (!beg)
		return (NULL);
	end = beg;

	while (nested ? **ptr && **ptr != ')' : **ptr)
	{
		// t_state *tmp = end;
		if (**ptr == '(' && (*ptr)++)
		{
			if (!(end = nfa_create(end, ptr, true)) || **ptr != ')')
				return (NULL);
			(*ptr)++;
		}
		else
			if (!(end = nfa_add_pattern(end, ptr)))
				return (NULL);
		// if (!(end = nfa_build_quantifier(tmp, end, &ptr)))
		// 	return (NULL);
		if (**ptr == '|' && !(end = nfa_build_or(beg, end, ptr, nested)))
			return (NULL);
	}
	return (end);
}

t_nfa *str_to_nfa(const char *str)
{
	t_nfa *nfa;
	char *ptr;

	if (!(nfa = nfa_new(str)))
		return (NULL);
	ptr = nfa->re_expr;
	if (!(nfa->finalstate = nfa_create(nfa->entrypoint, (const char **)&ptr, false)))
	{
		nfa_free(nfa);
		return (NULL);
	}
	nfa->finalstate->is_final = true;

	return (nfa);
}
