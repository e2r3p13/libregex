/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 21:29:49 by bccyv             #+#    #+#             */
/*   Updated: 2021/02/01 17:03:42 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libregex.h"
#include <stdlib.h>

static t_bool match_pattern(t_pattern p, char c)
{
	if (!p.start)
		return (true); // Epsilon link

	if (p.start == p.end)
		return (*(p.start) == c); // Single char pattern

	return (false); // More complex patterns need to be implemented
}

static void	link_init(t_link *ln)
{
	ft_bzero(ln, sizeof(t_link));
	ln->match = &match_pattern;
}

t_state *state_new()
{
	t_state *st;

	if (!(st = malloc(sizeof(t_state))))
		return (NULL);

	st->is_final = false;

	link_init(&st->left);
	link_init(&st->right);

	return (st);
}

void state_add_link(t_state *st, t_pattern pattern, t_state *next)
{
	if (!st->left.next)
	{
		st->left.next = next;
		st->left.pattern = pattern;
	}
	else
	{
		st->right.next = next;
		st->right.pattern = pattern;
	}
}
