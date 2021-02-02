/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 08:54:45 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/02 16:00:43 by lfalkau          ###   ########.fr       */
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

void nfa_print(t_state *st, int lvl)
{
	for (int i = 0; i < lvl; i++)
		printf("\t");
	printf("ST: %p, LEFT: %p (%.*s), RIGHT: %p (%.*s)\n", st, st->left.next, st->left.pattern.start ? (int)(st->left.pattern.end - st->left.pattern.start) + 1 : 0 , st->left.pattern.start, st->right.next, st->right.pattern.start ? (int)(st->right.pattern.end - st->right.pattern.start) + 1 : 0 , st->right.pattern.start);
	if ( st->left.next)
		nfa_print(st->left.next, lvl + 1);
	if ( st->right.next)
		nfa_print(st->right.next, lvl + 1);
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

// static t_state *nfa_build_quantifier(t_state *begin, t_state *end)
// {
//
// }

static t_state *nfa_build_or(t_state *beg, t_state *lend, const char **ptr, t_bool nested)
{
	t_state *new_beg;
	t_state *new_end;
	t_state *rend;
	t_state *reps;

	if (!(new_beg = state_new()))
		return (NULL);
	if (!(new_end = state_new()))
	{
		free(new_beg);
		return (NULL);
	}
	links_cpy(new_beg, beg);
	links_destroy(beg);
	link_add(beg, pattern_epsilon(), new_beg);
	if (!(reps = state_new()))
	{
		free(new_beg);
		free(new_end);
		return (NULL);
	}
	link_add(beg, pattern_epsilon(), reps);
	(*ptr)++;
	if (!(rend = nfa_create(reps, ptr, nested)))
	{
		free(new_end);
		free(new_end);
		free(reps);
		return (NULL);
	}
	link_add(lend, pattern_epsilon(), new_end);
	link_add(rend, pattern_epsilon(), new_end);
	return (new_end);
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
			if (!(end = nfa_add_char_to(end, ptr)))
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
