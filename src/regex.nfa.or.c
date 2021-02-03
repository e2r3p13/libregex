/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:37:13 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/03 08:43:49 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libregex.h"
#include <stdlib.h>

t_state *nfa_build_or(t_state *beg, t_state *lend, const char **ptr, t_bool nested)
{
	t_state *new_beg;
	t_state *new_end;
	t_state *rend;
	t_state *reps;

	if (!(new_beg = state_new()))
		return (NULL);
	if (!(new_end = state_new()))
	{
		free(new_beg);
		return (NULL);
	}
	links_cpy(new_beg, beg);
	links_destroy(beg);
	link_add(beg, pattern_epsilon(), new_beg);
	if (!(reps = state_new()))
	{
		free(new_beg);
		free(new_end);
		return (NULL);
	}
	link_add(beg, pattern_epsilon(), reps);
	(*ptr)++;
	if (!(rend = nfa_create(reps, ptr, nested)))
	{
		free(new_end);
		free(new_end);
		free(reps);
		return (NULL);
	}
	link_add(lend, pattern_epsilon(), new_end);
	link_add(rend, pattern_epsilon(), new_end);
	return (new_end);
}
