/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 08:54:45 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/01 13:26:06 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libregex.h"

static t_nfa *nfa_new(const char *str)
{
	t_nfa *nfa;

	if (!str || !(nfa = malloc(sizeof(t_nfa))))
		return (NULL);
	bzero(nfa, sizeof(t_nfa));
	if (!(nfa->re_expr = ft_strdup(str)))
	{
		nfa_free(nfa);
		return (NULL);
	}
	if (!(nfa->entrypoint = state_new(false)))
	{
		nfa_free(nfa);
		return (NULL);
	}
	nfa->finalstate = NULL;

	return (nfa);
}

static void nfa_free(t_nfa *nfa)
{
	// TODO
}

static int nfa_add_char_to(t_state *beg, const char *ptr)
{

}

static int nfa_build_quantifier()
{

}

static int nfa_build_or(t_nfa *left, t_nfa *right)
{

}

static t_state *nfa_create(t_state *beg const char **ptr)
{
	t_state *end;

	if (!beg) return (NULL);
	if (!end) end = beg;

	while (is_parenthesis ? **ptr && **ptr != ')' : **ptr)
	{
		t_state *tmp = end;
		if (**ptr == '(' && (*ptr)++)
		{
			if (!(end = nfa_create(end, ptr)) || **ptr != ')')
				return (NULL);
			(*ptr)++;
		}
		else
		{
			if (!(end = nfa_add_char_to(end, &ptr)))
				return (NULL);
		}
		if (!(end = nfa_build_quantifier(tmp, end, &ptr)))
			return (NULL);
		if (*ptr == '|' && !(end = nfa_build_or(&being, end, &ptr)))
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
	if (!(nfa->finalstate = nfa_create(nfa->entrypoint, &ptr)))
	{
		nfa_free(nfa);
		return (NULL);
	}
	nfa->finalstate->is_final = true;

	return (nfa);
}
