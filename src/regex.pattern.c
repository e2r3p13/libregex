/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glafond- <glafond-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 04:57:16 by glafond-          #+#    #+#             */
/*   Updated: 2021/02/12 15:48:10 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.fa.h>
#include <libft.h>

static char *esc_table[128] =
{
	['c'] = "\x80\x3f\x00\x0c\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",
	['s'] = "\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",
	['S'] = "\xfe\xff\xff\xff\xfe\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x7f",
	['d'] = "\x00\x00\x00\x00\x00\x00\xff\x03\x00\x00\x00\x00\x00\x00\x00\x00",
	['D'] = "\xfe\xff\xff\xff\xff\xff\x00\xfc\xff\xff\xff\xff\xff\xff\xff\x7f",
	['w'] = "\x00\x00\x00\x00\x00\x00\x00\x00\xfe\xff\xff\x87\xfe\xff\xff\x07",
	['W'] = "\xfe\xff\xff\xff\xff\xff\xff\xff\x01\x00\x00\x78\x01\x00\x00\x78",
	['x'] = "\x00\x00\x00\x00\x00\x00\xff\x03\xfe\xff\xff\x07\xfe\xff\xff\x07",
	['O'] = "\x00\x00\x00\x00\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00",
	['n'] = "\x00\x04\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",
	['r'] = "\x00\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",
	['t'] = "\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",
	['v'] = "\x00\x08\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",
	['f'] = "\x00\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
};

static int	pattern_add_char(t_pattern *pattern, int c)
{
	int			div;

	div = c / 8;
	if (div > PATTERN_MAX_LENGTH)
		return (-1);
	(*pattern)[div] |= (1 << (c % 8));
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
		(*pattern)[s / 8] |= (1 << (s % 8));
		s++;
	}
	return (0);
}

int			pattern_escape(t_pattern *pattern, const char **ptr)
{
	if (**ptr == '\0')
		return (-1);
	if (esc_table[(int)**ptr])
		ft_memcpy(*pattern, esc_table[(int)*(*ptr)++], PATTERN_MAX_LENGTH);
	else
		pattern_add_char(pattern, *(*ptr)++);
	return (0);
}

int			pattern_parse(t_pattern *pattern, const char **ptr)
{
	while (**ptr || **ptr != ']')
	{
		if (**ptr == '\\')
		{
			(*ptr)++;
			if (pattern_escape(pattern, ptr))
				return (-1);
		}
		else if (*(*ptr + 1) == '-' && *(*ptr + 2) && *(*ptr + 2) != ']')
		{
			if (pattern_add_range(pattern, **ptr, *(*ptr + 2)))
				return (-1);
			*ptr += 3;
		}
		else if (pattern_add_char(pattern, *(*ptr)++))
				return (-1);
	}
	if (**ptr)
		(*ptr)++;
	return (0);
}

void		pattern_epsilon(t_pattern *pattern)
{
	pattern_add_char(pattern, '\0');
}

int			is_epsilon(t_pattern pattern)
{
	return (pattern_match(pattern, '\0'));
}

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

/*
**	Returns 0 if patterns a end b are equal
*/
int		pattern_cmp(t_pattern *a, t_pattern *b)
{
	return (ft_memcmp(a, b, sizeof(t_pattern)));
}
