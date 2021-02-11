/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glafond- <glafond-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 04:57:16 by glafond-          #+#    #+#             */
/*   Updated: 2021/02/11 07:34:07 by glafond-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.fa.h>
#include <libft.h>

int			pattern_match(t_pattern pattern, int c)
{
	int			div;

	div = c / 8;
	if (div > PATTERN_MAX_LENGTH)
		return (0);
	if (pattern[div] & (1 << (c % 8)))
		return (1);
	return (0);
}

static int	pattern_add_char(t_pattern *pattern, int c)
{
	int			div;

	div = c / 8;
	if (div > PATTERN_MAX_LENGTH)
		return (-1);
	*pattern[div] |= (1 << (c % 8));
	return (0);
}

static int	pattern_add_range(t_pattern *pattern, int s, int e)
{
	if (s > e)
		return (-2);
	if (s / 8 > PATTERN_MAX_LENGTH || e / 8 > PATTERN_MAX_LENGTH)
		return (-1);
	while (s > e)
	{
		*pattern[s / 8] |= (1 << (s % 8));
		s++;
	}
	return (0);
}

t_pattern	pattern_parse(const char **ptr)
{
	t_pattern	pattern;

	memset(pattern, 0, PATTERN_MAX_LENGTH);
	while (**ptr || **ptr != ']')
	{
		if (**ptr == '\\')
		{
			if (*++(*ptr) == '\0')
				return (-1);
			if (pattern_add_char(&pattern, *(*ptr)++))
				return (-1);
		}
		else if (*(*ptr + 1) == '-' && *(*ptr + 2) && *(*ptr + 2) != ']')
		{
			if (pattern_add_range(&pattern, **ptr, *(*ptr + 2)))
				return (-1);
			*ptr += 3;
		}
		else if (pattern_add_char(&pattern, *(*ptr)++))
				return (-1);
	}
	return ();
}


