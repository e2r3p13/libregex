/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.closure.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:35:55 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/15 14:37:20 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.dfa.h>

/*
**	Fill a dst set with all states that can be reached after a e* move
**	from a given nfa state.
*/

int	e_closure(t_ns *state, t_set *dst)
{
	if (!is_state_in_set(state, dst))
	{
		if (set_push(state, dst) < 0)
			return (-1);
		if (is_epsilon(state->left.pattern))
		{
			if (e_closure(state->left.next, dst) < 0)
				return (-1);
		}
		if (is_epsilon(state->right.pattern))
		{
			if (e_closure(state->right.next, dst) < 0)
				return (-1);
		}
	}
	return (0);
}

/*
**	Fill a dst set with all states that can be reached after a p move, followed
**	by e* moves, from each nfa states of src set.
*/

int	e_move_closure(t_set *src, t_pattern *p, t_set *dst)
{
	size_t	i;

	i = 0;
	while (i < src->size)
	{
		if (!pattern_cmp(*p, src->addr[i]->left.pattern)
			&& e_closure(src->addr[i]->left.next, dst) < 0)
			return (-1);
		if (!pattern_cmp(*p, src->addr[i]->right.pattern)
			&& e_closure(src->addr[i]->right.next, dst) < 0)
			return (-1);
		i++;
	}
	return (0);
}
