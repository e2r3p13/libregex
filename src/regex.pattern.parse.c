/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.pattern.parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glafond- <glafond-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 04:57:16 by glafond-          #+#    #+#             */
/*   Updated: 2021/02/17 09:16:28 by glafond-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.fa.h>
#include <libft.h>

static char	*g_esc_table[128] = {
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

static int	pattern_invert(t_pattern *pattern)
{
	int			index;

	index = 0;
	while (index < PATTERN_BYTES_LENGTH)
		(*pattern)[index++] ^= 0xff;
	return (0);
}

int	pattern_escape(t_pattern *pattern, const char **ptr)
{
	if (**ptr == '\0')
		return (-1);
	if (g_esc_table[(int)**ptr])
		pattern_add_pattern(pattern, g_esc_table[(int)*(*ptr)++]);
	else
		pattern_add_char(pattern, *(*ptr)++);
	return (0);
}

int	pattern_parse(t_pattern *pattern, const char **ptr)
{
	int			invert;

	invert = 0;
	if (**ptr == '^')
	{
		pattern_add_char(pattern, '\0');
		invert = 1;
		(*ptr)++;
	}
	while (**ptr && **ptr != ']')
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
	if (!**ptr)
		return (-1);
	(*ptr)++;
	if (invert)
		pattern_invert(pattern);
	return (0);
}
