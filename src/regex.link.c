/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:30:26 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/10 11:40:16 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.fa.h>
#include <libft.h>

extern void *g_esc_table[128];

static int	match_pattern(t_pattern p, int c)
{
	int (*match)(int);

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
