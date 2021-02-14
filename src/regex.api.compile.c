/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.api.compile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glafond- <glafond-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 09:11:02 by glafond-          #+#    #+#             */
/*   Updated: 2021/02/14 10:02:45 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libregex.h>

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
