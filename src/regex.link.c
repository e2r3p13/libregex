/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:30:26 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/10 11:24:47 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libregex.h>
#include <stdio.h>

extern void *g_esc_table[128];

static int	match_pattern(t_pattern p, int c)
{
	t_bool (*match)(int);

	if (!p.start)
		return (2);
	match = g_esc_table[(int)*p.end];
	if (p.start == p.end)
		return (*(p.start) == c);
	return (*p.start == 92 && match(c));
}

void		link_init(t_link *ln)
{
	ft_bzero(ln, sizeof(t_link));
	ln->match = &match_pattern;
}

void		link_add(t_ns *st, t_pattern pattern, t_ns *next)
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

void		links_destroy(t_ns *st)
{
	link_init(&st->left);
	link_init(&st->right);
}

void		links_cpy(t_ns *dst, t_ns *src)
{
	dst->left = src->left;
	dst->right = src->right;
}
