/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.api.execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glafond- <glafond-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 03:34:58 by glafond-          #+#    #+#             */
/*   Updated: 2021/02/19 15:46:10 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libregex.h>
#include <regex.fa.h>

static char	*match(t_ds *state, const char *str)
{
	const char	*ptr;
	t_link_lst	*links;

	ptr = str;
	while (*ptr)
	{
		links = state->links;
		if (!links)
			break ;
		while (!pattern_match(links->link.pattern, *ptr))
		{
			links = links->next;
			if (!links)
			{
				if (state->is_final)
					return ((char *)ptr);
				return (NULL);
			}
		}
		state = (t_ds *)links->link.next;
		ptr++;
	}
	if (state->is_final)
		return ((char *)ptr);
	return (NULL);
}

/*
**	TODO: Big function with flags
*/

int	re_execute(t_regex *regex, const char *str)
{
	char		*ret;
	int			nb_match;

	nb_match = 0;
	while (*str)
	{
		ret = match(regex->entrypoint, str);
		if (!ret || ret == str)
		{
			str++;
			continue ;
		}
		nb_match++;
		str = (const char *)ret;
	}
	return (nb_match);
}

/*
**	Returns 1 if the hole string str match the given regex struct, 0 otherwise.
*/

int	re_match(t_regex *regex, const char *str)
{
	char		*ret;

	ret = match(regex->entrypoint, str);
	if (!ret || *ret)
		return (0);
	return (1);
}

/*
**	Bastard function, waiting for re_execute to be improved to be deleted.
*/

char	*re_bmatch(t_regex *regex, const char *str)
{
	return (match(regex->entrypoint, str));
}
