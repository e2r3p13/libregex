/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.quantifiers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:37:26 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/14 10:25:14 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.nfa.h>
#include <stdlib.h>

t_ns		*nfa_build_quantifier(t_ns *beg, t_ns *end, const char **ptr)
{
	t_ns		*new_beg;
	t_ns		*new_end;
	t_pattern	epsilon;

	if (nfa_surruond(beg, end, &new_beg, &new_end) < 0)
		return (NULL);
	pattern_epsilon(&epsilon);
	if (**ptr != '+')
		link_add(beg, epsilon, new_end);
	if (**ptr != '?')
		link_add(end, epsilon, new_beg);
	(*ptr)++;
	return (new_end);
}
