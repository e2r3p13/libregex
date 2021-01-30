/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 08:54:45 by lfalkau           #+#    #+#             */
/*   Updated: 2021/01/30 15:30:12 by lfalkau          ###   ########.fr       */
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
	if (!(nfa->entrypoint = state_new(true)))
	{
		nfa_free(nfa);
		return (NULL);
	}
	nfa->finalstate = nfa->entrypoint;

	return (nfa);
}

static void nfa_free(t_nfa *nfa)
{
	// TODO
}

t_state *nfa_build_wildcard(t_nfa *nfa)
{

}

int nfa_build_plus()
{

}

int nfa_build_imark()
{

}

int nfa_build_or(t_nfa *left, t_nfa *right)
{

}

int nfa_add_char(t_nfa *nfa, const char *ptr)
{
	t_state		*new;
	t_pattern	pattern;

	new = state_new(true);
	if (!new)
		return (-1);
	state_add_link(nfa->finalstate, pattern, new);
	nfa->finalstate.is_final = false;
	nfa->finalstate = new;
	
	return (0);
}

t_nfa *str_to_nfa(const char *str)
{
	t_nfa *nfa;

	nfa = nfa_new(str, new);
}
