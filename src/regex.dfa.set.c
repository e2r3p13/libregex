/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:01:45 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/14 10:17:21 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.dfa.h>
#include <stdlib.h>
#include <libft.h>

/*
**	Return true if a state is in a set, false otherwise
*/

t_bool		is_state_in_set(t_ns *state, t_set *set)
{
	size_t i;

	i = 0;
	while (i < set->size)
	{
		if (set->addr[i] == state)
			return (true);
		i++;
	}
	return (false);
}

t_bool		set_contains_final_state(t_set *set)
{
	size_t	i;

	i = 0;
	while (i < set->size)
	{
		if (set->addr[i]->is_final)
			return (true);
		i++;
	}
	return (false);
}

/*
**	Compares two sets. The order of the elements doesn't matter, e.g.
**	{0, 3, 2, 1} and {0, 1, 2, 3} are equal
*/

t_bool		set_cmp(t_set *a, t_set *b)
{
	t_bool	found;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < a->size)
	{
		found = false;
		j = 0;
		while (j < b->size)
		{
			if (a->addr[i] == b->addr[j])
				found = true;
			j++;
		}
		if (!found)
			return (false);
		i++;
	}
	return (true);
}
