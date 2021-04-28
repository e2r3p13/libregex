/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glafond- <glafond-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:48:45 by glafond-          #+#    #+#             */
/*   Updated: 2021/04/28 19:50:49 by glafond-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <regex.fa.h>
#include <regex.ft.h>

t_ns	*nfa_state_new(void)
{
	t_ns	*st;

	st = malloc(sizeof(t_ns));
	if (!st)
		return (NULL);
	st->is_final = 0;
	nfa_link_init(&st->left);
	nfa_link_init(&st->right);
	st->flag = 0;
	return (st);
}

int	nfa_surround(t_ns *beg, t_ns *end, t_ns **new_beg, t_ns **new_end)
{
	t_pattern	p;

	if (!end)
		return (-1);
	*new_beg = nfa_state_new();
	if (!*new_beg)
		return (-1);
	*new_end = nfa_state_new();
	if (!*new_end)
	{
		free(*new_beg);
		return (-1);
	}
	nfa_links_cpy(*new_beg, beg);
	nfa_links_destroy(beg);
	pattern_epsilon(&p);
	nfa_link_add(*new_beg, beg, p);
	nfa_link_add(*new_end, end, p);
	return (0);
}

t_ns	*nfa_or(t_ns *ns[2], const char **ptr, int nested, t_alphabet **a)
{
	t_ns		*new_beg;
	t_ns		*new_end;
	t_ns		*right_beg;
	t_ns		*right_end;
	t_pattern	p;

	if (nfa_surround(ns[0], ns[1], &new_beg, &new_end) < 0)
		return (NULL);
	right_beg = nfa_state_new();
	if (!right_beg)
		return (NULL);
	pattern_epsilon(&p);
	nfa_link_add(right_beg, ns[0], p);
	(*ptr)++;
	right_end = nfa_create(right_beg, ptr, nested, a);
	if (!right_end)
		return (NULL);
	nfa_link_add(new_end, right_end, p);
	return (new_end);
}

t_ns	*nfa_quantifier(t_ns *beg, t_ns *end, const char **ptr)
{
	t_ns		*new_beg;
	t_ns		*new_end;
	t_pattern	p;

	if (nfa_surround(beg, end, &new_beg, &new_end) < 0)
		return (NULL);
	pattern_epsilon(&p);
	if (**ptr != '+')
		nfa_link_add(new_end, beg, p);
	if (**ptr != '?')
		nfa_link_add(new_beg, end, p);
	(*ptr)++;
	return (new_end);
}

t_ns	*nfa_pattern(t_ns *beg, const char **ptr, t_alphabet **a)
{
	t_ns		*new_end;
	t_pattern	pattern;

	if (!beg)
		return (NULL);
	ft_memset(pattern, 0, sizeof(pattern));
	if (**ptr == '[' || **ptr == '\\' || **ptr == '.')
	{
		if (pattern_parse(&pattern, ptr))
			return (NULL);
	}
	else if (pattern_add_char(&pattern, *(*ptr)++))
		return (NULL);
	if (alphabet_add_pattern(a, pattern))
		return (NULL);
	new_end = nfa_state_new();
	if (!new_end)
		return (NULL);
	nfa_link_add(new_end, beg, pattern);
	return (new_end);
}
