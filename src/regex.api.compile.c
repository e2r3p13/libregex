/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.api.compile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glafond- <glafond-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 09:11:02 by glafond-          #+#    #+#             */
/*   Updated: 2021/02/19 20:55:36 by bccyv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libregex.h>
#include <regex.fa.h>
#include <stdlib.h>
#include <libft.h>

int	re_compile(t_regex *regex, const char *str)
{
	regex->entrypoint = dfa_generate(str);
	if (!regex->entrypoint)
		return (-1);
	regex->re_string = ft_strdup(str);
	if (!regex->re_string)
	{
		dfa_free(regex->entrypoint);
		return (-1);
	}
	return (0);
}

void	re_free(t_regex *re)
{
	free(re->re_string);
	dfa_free(re->entrypoint);
}
