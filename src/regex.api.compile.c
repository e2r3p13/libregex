/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.api.compile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glafond- <glafond-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 09:11:02 by glafond-          #+#    #+#             */
/*   Updated: 2021/02/19 15:45:13 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libregex.h>
#include <regex.fa.h>
#include <stdlib.h>
#include <libft.h>

/*
**	Create a t_regex structure from a literal regex expression.
**	Returns 0 on success, -1 on failure.
*/

int	re_compile(t_regex *regex, const char *str)
{
	regex->entrypoint = dfa_generate(str);
	if (!regex->entrypoint)
		return (-1);
	regex->re_string = ft_strdup(str);
	if (!regex->re_string)
		return (-1);
	return (0);
}

/*
**	Free the regex struct. Needs to be called after each re_compile call, on its
**	return value.
*/

void	re_free(t_regex *re)
{
	free(re->re_string);
	dfa_free(re->entrypoint);
}
