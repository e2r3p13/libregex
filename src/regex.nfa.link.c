/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.link.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:34:55 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/19 15:35:07 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.fa.h>
#include <libft.h>

/*
**	Inits a t_link
*/

void	nfa_link_init(t_link *ln)
{
	ft_memset(ln, 0, sizeof(t_link));
	ln->match = &pattern_match;
}

/*
**	Adds a link to an existing nfa state.
**	NFA states have at most 2 links, that is why if its left link already points
**	to another state, we create the link on its right.
*/

void	nfa_link_add(t_ns *st, t_pattern pattern, t_ns *next)
{
	if (!st->left.next)
	{
		st->left.next = next;
		ft_memcpy(st->left.pattern, pattern, sizeof(t_pattern));
	}
	else
	{
		st->right.next = next;
		ft_memcpy(st->right.pattern, pattern, sizeof(t_pattern));
	}
}

/*
**	Resets either the left and the right link of a nfa state.
*/

void	nfa_links_destroy(t_ns *st)
{
	nfa_link_init(&st->left);
	nfa_link_init(&st->right);
}

/*
**	Copies src links into dst links, including patterns and destination states.
*/

void	nfa_links_cpy(t_ns *dst, t_ns *src)
{
	dst->left = src->left;
	dst->right = src->right;
}

/*
**	Returns 1 if right or left link of a given state match the given pattern.
*/

int	nfa_has_link(t_pattern *p, t_ns *state)
{
	return (!pattern_cmp(*p, state->left.pattern)
		|| !pattern_cmp(*p, state->right.pattern));
}
