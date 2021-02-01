/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 08:54:45 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/01 20:42:28 by bccyv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libregex.h"
#include <stdlib.h>
#include <stdio.h>

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

t_bool nfa_match(t_nfa *nfa, const char *str)
{
	t_state *curr = nfa->entrypoint;

	while (*str)
	{
		if (curr->left.next && curr->left.match(curr->left.pattern, *str))
			curr = curr->left.next;
		else if (curr->right.next && curr->right.match(curr->right.pattern, *str))
			curr = curr->right.next;
		else
			return (false);
		str++;
	}
	return (curr->is_final);
}

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

static int pattern_length(const char *ptr)
{
	// TODO: For now it accepts everything in between hooks
	int i = 0;
	while (*ptr && *ptr != ']')
		ptr++;
	return (*ptr ? i : 0);
}

static t_state *nfa_add_char_to(t_state *beg, const char **p)
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
	else if (*ptr == 92 && g_esc_table[(int)*ptr]) // 92 is backslash
		ptr++;
	else if (*ptr == 92 || *ptr == '[' || !ft_isprint(*ptr))
	{
		free(new);
		return (NULL);
	}
	pattern.end = ptr;
	*p = ptr + 1;
	state_add_link(beg, pattern, new);
	return (new);
}

// static t_state *nfa_build_quantifier(t_state *begin, t_state *end)
// {
//
// }
//
// static t_state *nfa_build_or(t_state **beg, t_state *end)
// {
//
// }

static t_state *nfa_create(t_state *beg, const char **ptr, t_bool nested)
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
		{
			if (!(end = nfa_add_char_to(end, ptr)))
				return (NULL);
		}
		// if (!(end = nfa_build_quantifier(tmp, end, &ptr)))
		// 	return (NULL);
		// if (*ptr == '|' && !(end = nfa_build_or(&being, end, &ptr)))
		// 	return (NULL);
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
