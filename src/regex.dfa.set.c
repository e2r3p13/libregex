/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:01:45 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/19 14:21:59 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.fa.h>
#include <stdlib.h>
#include <libft.h>

/*
**	Return 1 if a state is in a set, 0 otherwise
*/

int	is_state_in_set(t_ns *state, t_set *set)
{
	size_t	i;

	i = 0;
	while (i < set->size)
	{
		if (set->addr[i] == state)
			return (1);
		i++;
	}
	return (0);
}

int	set_contains_final_state(t_set *set)
{
	size_t	i;

	i = 0;
	while (i < set->size)
	{
		if (set->addr[i]->is_final)
			return (1);
		i++;
	}
	return (0);
}

/*
**	Compares two sets. The order of the elements doesn't matter, e.g.
**	{0, 3, 2, 1} and {0, 1, 2, 3} are equal
*/

int	set_cmp(t_set *a, t_set *b)
{
	int		found;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < a->size)
	{
		found = 0;
		j = 0;
		while (j < b->size)
		{
			if (a->addr[i] == b->addr[j])
				found = 1;
			j++;
		}
		if (!found)
			return (0);
		i++;
	}
	return (1);
}
