/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.api.free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:08:04 by bccyv             #+#    #+#             */
/*   Updated: 2021/02/16 16:24:49 by bccyv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libregex.h>
#include <regex.dfa.h>
#include <stdlib.h>

void	re_free(t_regex *re)
{
	free(re->re_string);
	dfa_free(re->entrypoint);
}
