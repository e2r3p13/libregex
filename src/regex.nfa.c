/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:37:02 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/19 15:35:14 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.fa.h>
#include <stdlib.h>
#include <libft.h>

/*
**	Followings functions builds a NFA (non deterministic finite automaton),
**	using the Thompson's construct.
**	see https://tajseer.files.wordpress.com/2014/06/re-nfa-dfa.pdf.
*/

/*
**	nfa_surrond is useful for nfa_or and nfa_quantifier functions.
**
**	return value: A pointer to the end of the structure on success,
**	NULL on error.
*/

static int	nfa_surround(t_ns *b, t_ns *e, t_ns **nb, t_ns **ne)
{
	t_pattern	epsilon;

	if (!e)
		return (-1);
	*nb = nfa_state_new();
	if (!*nb)
		return (-1);
	*ne = nfa_state_new();
	if (!*ne)
	{
		free(*nb);
		return (-1);
	}
	nfa_links_cpy(*nb, b);
	nfa_links_destroy(b);
	pattern_epsilon(&epsilon);
	nfa_link_add(b, epsilon, *nb);
	nfa_link_add(e, epsilon, *ne);
	return (0);
}

/*
**	nfa_or builds a or structure if the next input character
**	is a pipe.
**
**	return value: A pointer to the end of the structure on success,
**	NULL on error.
*/

static t_ns	*nfa_or(t_ns *beg, t_ns *end, const char **p, int n, t_alphabet **a)
{
	t_ns		*new_beg;
	t_ns		*new_end;
	t_ns		*rend;
	t_ns		*reps;
	t_pattern	epsilon;

	if (nfa_surround(beg, end, &new_beg, &new_end) < 0)
		return (NULL);
	reps = nfa_state_new();
	if (!reps)
		return (NULL);
	pattern_epsilon(&epsilon);
	nfa_link_add(beg, epsilon, reps);
	(*p)++;
	rend = nfa_create(reps, p, n, a);
	if (!rend)
		return (NULL);
	nfa_link_add(rend, epsilon, new_end);
	return (new_end);
}

/*
**	nfa_quantifier builds a quantifier structure if the next input character
**	is a quantifier (*+?).
**
**	return value: A pointer to the end of the structure on success,
**	NULL on error.
*/

static t_ns	*nfa_quantifier(t_ns *beg, t_ns *end, const char **ptr)
{
	t_ns		*new_beg;
	t_ns		*new_end;
	t_pattern	epsilon;

	if (nfa_surround(beg, end, &new_beg, &new_end) < 0)
		return (NULL);
	pattern_epsilon(&epsilon);
	if (**ptr != '+')
		nfa_link_add(beg, epsilon, new_end);
	if (**ptr != '?')
		nfa_link_add(end, epsilon, new_beg);
	(*ptr)++;
	return (new_end);
}

/*
**	nfa_pattern pushes a new state to the nfa and tries to create a link
**	between begin and this new state, with the next pattern in *ptr.
**
**	return value: A pointer to the new state on success, NULL on error.
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
	new_end = nfa_state_new();
	if (!new_end)
		return (NULL);
	nfa_link_add(beg, pattern, new_end);
	return (new_end);
}

/*
**	nfa_create creates the nfa. It first gets the next character of the input.
**	If it is a vharacter, it builds it, else if ot is an opening brace,
**	nfa_create calls itself to build the braced nfa and concatenate it with the
**	one it already has.
**	Next, it tries to build a quantifier structure, then a or structure.
**	Repeats until it reaches the end of the input, or finds an error.
**
**	beg: A pointer to the currently last allocated state.
**	ptr: A pointer going through the literal regular expression.
**	nested: Indicates weither we build a braced nfa or not. (1 or 0).
**	a: The alphabet to fill.
**
**	return value: The entry state of the created nfa, NULL on error.
*/

t_ns	*nfa_create(t_ns *beg, const char **ptr, int nested, t_alphabet **a)
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
			end = nfa_create(end, ptr, 1, a);
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

/*
**	nfa_generate tries to create a nfa from a string.
**
**	str: The literal regular expression.
**	a: A pointer to pointer to the head of the fa's alphabet (empty at start).
**
**	return value: the nfa entry state on success, NULL on failure.
*/

t_ns	*nfa_generate(const char *str, t_alphabet **a)
{
	t_ns	*entrypoint;
	t_ns	*final;

	if (*str == '\0')
		return (NULL);
	entrypoint = nfa_state_new();
	if (!entrypoint)
		return (NULL);
	final = nfa_create(entrypoint, &str, 0, a);
	if (!final)
	{
		nfa_free(entrypoint);
		return (NULL);
	}
	final->is_final = 1;
	return (entrypoint);
}
