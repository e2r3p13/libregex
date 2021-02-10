/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:37:13 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/10 11:05:37 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libregex.h>
#include <stdlib.h>

t_state	*nfa_build_or(t_state *beg, t_state *end, const char **ptr, t_bool nstd)
{
	t_state *new_beg;
	t_state *new_end;
	t_state *rend;
	t_state *reps;

	if (nfa_surruond(beg, end, &new_beg, &new_end) < 0)
		return (NULL);
	if (!(reps = state_new()))
	{
		free(new_beg);
		free(new_end);
		return (NULL);
	}
	link_add(beg, pattern_epsilon(), reps);
	(*ptr)++;
	if (!(rend = nfa_create(reps, ptr, nstd)))
	{
		free(new_end);
		free(new_end);
		free(reps);
		return (NULL);
	}
	link_add(rend, pattern_epsilon(), new_end);
	return (new_end);
}
