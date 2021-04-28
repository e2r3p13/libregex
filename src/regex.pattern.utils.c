/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.pattern.utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:00:11 by bccyv             #+#    #+#             */
/*   Updated: 2021/04/28 19:08:12 by glafond-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.fa.h>
#include <regex.ft.h>

int	pattern_match(t_pattern pattern, int c)
{
	int			div;

	div = c / 8;
	if (div > PATTERN_BYTES_LENGTH)
		return (0);
	if (pattern[div] & (1 << (c % 8)))
		return (1);
	return (0);
}

void	pattern_epsilon(t_pattern *pattern)
{
	pattern_add_char(pattern, '\0');
}

int	is_epsilon(t_pattern pattern)
{
	return (pattern_match(pattern, '\0'));
}

int	pattern_copy(t_pattern dst, t_pattern src)
{
	ft_memcpy(dst, src, sizeof(t_pattern));
	return (0);
}

int	pattern_cmp(t_pattern a, t_pattern b)
{
	return (ft_memcmp(a, b, sizeof(t_pattern)));
}
