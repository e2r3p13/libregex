/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.link.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:34:55 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/11 09:29:38 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.nfa.h>
#include <libft.h>

void	link_add(t_ns *st, t_pattern pattern, t_ns *next)
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

void	links_destroy(t_ns *st)
{
	link_init(&st->left);
	link_init(&st->right);
}

void	links_cpy(t_ns *dst, t_ns *src)
{
	dst->left = src->left;
	dst->right = src->right;
}

void	link_init(t_link *ln)
{
	ft_bzero(ln, sizeof(t_link));
	ln->match = &pattern_match;
}
