/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.compile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glafond- <glafond-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 09:11:02 by glafond-          #+#    #+#             */
/*   Updated: 2021/02/14 03:30:24 by glafond-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.dfa.h>

int		re_compile(t_regex	*regex, const char *str)
{
	regex->entrypoint = dfa_generate(str);
	if (!regex->entrypoint)
		return (-1);
	regex->re_string = ft_strdup(str);
	if (!regex->re_string)
		return (-1);
	return (0);
}
