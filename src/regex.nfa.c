/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:37:02 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/15 11:47:01 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.nfa.h>
#include <stdlib.h>

static t_ns	*nfa_or(t_ns *beg, t_ns *end, const char **ptr, t_bool nstd, t_alphabet **a)
{
	t_ns		*new_beg;
	t_ns		*new_end;
	t_ns		*rend;
	t_ns		*reps;
	t_pattern	epsilon;

	if (nfa_surround(beg, end, &new_beg, &new_end) < 0)
		return (NULL);
	reps = nfa_new_state();
	if (!reps)
		return (NULL);
	pattern_epsilon(&epsilon);
	link_add(beg, epsilon, reps);
	(*ptr)++;
	rend = nfa_create(reps, ptr, nstd, a);
	if (!rend)
	{
		free(reps);
		return (NULL);
	}
	link_add(rend, epsilon, new_end);
	return (new_end);
}

static t_ns	*nfa_quantifier(t_ns *beg, t_ns *end, const char **ptr)
{
	t_ns		*new_beg;
	t_ns		*new_end;
	t_pattern	epsilon;

	if (nfa_surround(beg, end, &new_beg, &new_end) < 0)
		return (NULL);
	pattern_epsilon(&epsilon);
	if (**ptr != '+')
		link_add(beg, epsilon, new_end);
	if (**ptr != '?')
		link_add(end, epsilon, new_beg);
	(*ptr)++;
	return (new_end);
}

/*
**	nfa_add_pattern push a new state to the nfa and try to create a link
**	between begin and this new state, with the next pattern in *ptr
**	returns a pointer to the new state on success, NULL otherwise
**
**	begin --> NULL	to	begin -[pattern]-> next_ns
*/

static t_ns	*nfa_pattern(t_ns *beg, t_alphabet **a, const char **ptr)
{
	t_ns		*new_end;
	t_pattern	pattern;

	if (!beg)
		return (NULL);
	ft_memset(pattern, 0, sizeof(pattern));
	if (**ptr == '[')
	{
		if (!(*ptr)++ || pattern_parse(&pattern, ptr))
			return (NULL);
	}
	else if (**ptr == '\\')
	{
		if (!(*ptr)++ || pattern_escape(&pattern, ptr))
			return (NULL);
	}
	else if (pattern_add_char(&pattern, *(*ptr)++))
		return (NULL);
	if (alphabet_add_pattern(a, pattern))
		return (NULL);
	new_end = nfa_new_state();
	if (!new_end)
		return (NULL);
	link_add(beg, pattern, new_end);
	return (new_end);
}

t_ns	*nfa_create(t_ns *beg, const char **ptr, t_bool nested, t_alphabet **a)
{
	t_ns		*end;
	t_ns		*tmp;

	if (!beg)
		return (NULL);
	end = beg;
	while (nested ? **ptr && **ptr != ')' : **ptr)
	{
		tmp = end;
		if (**ptr == '(' && (*ptr)++)
		{
			end = nfa_create(end, ptr, true, a);
			if (!end || *(*ptr)++ != ')')
				return (NULL);
		}
		else
			end = nfa_pattern(end, a, ptr);
		if (ft_isinset("*+?", **ptr))
			end = nfa_quantifier(tmp, end, ptr);
		if (**ptr == '|')
			end = nfa_or(beg, end, ptr, nested, a);
		if (!end)
			return (NULL);
	}
	return (end);
}

t_ns	*str_to_nfa(const char *str, t_alphabet **a)
{
	t_ns	*entrypoint;
	t_ns	*final;

	if (*str == '\0')
		return (NULL);
	entrypoint = nfa_new_state();
	if (!entrypoint)
		return (NULL);
	final = nfa_create(entrypoint, &str, false, a);
	if (!final)
	{
		nfa_free(entrypoint);
		return (NULL);
	}
	final->is_final = true;
	nfa_print(entrypoint);
	return (entrypoint);
}
