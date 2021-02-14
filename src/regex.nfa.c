/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:37:02 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/14 10:58:36 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.nfa.h>
#include <stdlib.h>

static t_ns *nfa_or(t_ns *beg, t_alphabet **a, t_ns *end, const char **ptr, t_bool nstd)
{
	t_ns		*new_beg;
	t_ns		*new_end;
	t_ns		*rend;
	t_ns		*reps;
	t_pattern	epsilon;

	if (nfa_surruond(beg, end, &new_beg, &new_end) < 0)
		return (NULL);
	if (!(reps = nfa_new_state()))
	{
		free(new_beg);
		free(new_end);
		return (NULL);
	}
	pattern_epsilon(&epsilon);
	link_add(beg, epsilon, reps);
	(*ptr)++;
	if (!(rend = nfa_create(reps, a, ptr, nstd)))
	{
		free(new_end);
		free(new_end);
		free(reps);
		return (NULL);
	}
	link_add(rend, epsilon, new_end);
	return (new_end);
}

static t_ns *nfa_quantifier(t_ns *beg, t_ns *end, const char **ptr)
{
	t_ns		*new_beg;
	t_ns		*new_end;
	t_pattern	epsilon;

	if (nfa_surruond(beg, end, &new_beg, &new_end) < 0)
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

static t_ns *nfa_pattern(t_ns *ns_begin, t_alphabet **a, const char **ptr)
{
	t_ns		*ns_next;
	t_pattern	pattern;

	ft_memset(pattern, 0, sizeof(pattern));
	if (**ptr == '[')
	{
		(*ptr)++;
		if (pattern_parse(&pattern, ptr))
			return (NULL);
	}
	else if (**ptr == '\\')
	{
		(*ptr)++;
		if (pattern_escape(&pattern, ptr))
			return (NULL);
	}
	else if (pattern_add_char(&pattern, *(*ptr)++))
		return (NULL);
	if (alphabet_add_pattern(a, pattern))
		return (NULL);
	if (!(ns_next = nfa_new_state()))
		return (NULL);
	link_add(ns_begin, pattern, ns_next);
	return (ns_next);
}

int nfa_surruond(t_ns *b, t_ns *e, t_ns **nb, t_ns **ne)
{
	t_pattern	epsilon;

	if (!(*nb = nfa_new_state()))
		return (-1);
	if (!(*ne = nfa_new_state()))
	{
		free(*nb);
		return (-1);
	}
	links_cpy(*nb, b);
	links_destroy(b);
	pattern_epsilon(&epsilon);
	link_add(b, epsilon, *nb);
	link_add(e, epsilon, *ne);
	return (0);
}

t_ns *nfa_create(t_ns *beg, t_alphabet **a, const char **ptr, t_bool nested)
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
			if (!(end = nfa_create(end, a, ptr, true)) || **ptr != ')')
				return (NULL);
			(*ptr)++;
		}
		else if (!(end = nfa_pattern(end, a, ptr)))
			return (NULL);
		if (ft_isinset("*+?", **ptr) &&
			!(end = nfa_quantifier(tmp, end, ptr)))
			return (NULL);
		if (**ptr == '|' && !(end = nfa_or(beg, a, end, ptr, nested)))
			return (NULL);
	}
	return (end);
}

t_ns		*str_to_nfa(const char *str, t_alphabet **a)
{
	t_ns		*entrypoint;
	t_ns		*final;

	if (!(entrypoint = nfa_new_state()))
		return (NULL);
	if (!(final = nfa_create(entrypoint, a, &str, false)))
	{
		nfa_free(entrypoint);
		return (NULL);
	}
	final->is_final = true;
	return (entrypoint);
}
