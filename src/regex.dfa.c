/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 08:12:34 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/14 08:46:06 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.nfa.h>
#include <regex.dfa.h>
#include <stdlib.h>
#include <libft.h>
#include <stdio.h>

/*
**	Fill a dst set with all states that can be reached after a e* move
**	from a given nfa state.
*/
static int	e_closure(t_ns *state, t_set *dst)
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
static int	e_move_closure(t_set *src, t_pattern *p, t_set *dst)
{
	size_t i = 0;

	while (i < src->size)
	{
		if (!pattern_cmp(*p, src->addr[i]->left.pattern) && e_closure(src->addr[i]->left.next, dst) < 0)
			return (-1);
		if (!pattern_cmp(*p, src->addr[i]->right.pattern) && e_closure(src->addr[i]->right.next, dst) < 0)
			return (-1);
		i++;
	}
	return (0);
}

/*
**	Converts an nfa into a dfa, following the subset construction method:
**	https://tajseer.files.wordpress.com/2014/06/re-nfa-dfa.pdf
*/
int			dfa_build(t_map *st_map, t_map *hole_map, t_alphabet *a)
{
	t_alphabet	*current_letter;
	t_set		*move_set;
	t_ds		*next_state;
	t_map		*next_st_map;

	if (set_contains_final_state(st_map->set))
		st_map->state->is_final = true;
	current_letter = a;
	while (current_letter)
	{
		if (!(move_set = set_new()))
			return (-1);
		if (e_move_closure(st_map->set, &current_letter->pattern, move_set) < 0)
		{
			set_free(move_set);
			return (-1);
		}
		if (move_set->size > 0)
		{
			if (!(next_state = state_in_map(hole_map, move_set)))
			{
				if (!(next_state = dfa_state_new()))
				{
					set_free(move_set);
					return (-1);
				}
				if (!(next_st_map = map_new(next_state, move_set)))
				{
					set_free(move_set);
					dfa_state_free(next_state);
					return (-1);
				}
				map_push(hole_map, next_st_map);
				dfa_build(next_st_map, hole_map, a);
			}
			else
				set_free(move_set);
			if (dfa_create_connection(st_map->state, &current_letter->pattern, next_state) < 0)
				return (-1);
		}
		else
			set_free(move_set);
		current_letter = current_letter->next;
 	}
	return (0);
}

/*
**	Builds the first node of the dfa, and stores it in a t_map structure with
**	the epsilon closure of our nfa's entrypoint as its set.
**	The dfa_build call will construct our dfa from its first node.
*/
int			nfa_to_dfa(t_ds *entrypoint, t_ns *nfa, t_alphabet *alphabet)
{
	t_map	*map;

	if (!(map = map_new(entrypoint, NULL)))
		return (-1);
	if (e_closure(nfa, map->set) < 0)
	{
		free(map);
		return (-1);
	}
	if (dfa_build(map, map, alphabet) < 0)
	{
		free(map);
		return (-1);
	}
	map_free(map);
	return (0);
}

t_ds		*dfa_generate(const char *str)
{
	t_ds		*entrypoint;
	t_ns		*nfa;
	t_alphabet	*alphabet;

	alphabet = NULL;
	if (!(nfa = str_to_nfa(str, &alphabet)))
		return (NULL);
	if (!(entrypoint = dfa_state_new()))
	{
		nfa_free(nfa);
		return (NULL);
	}
	if (nfa_to_dfa(entrypoint, nfa, alphabet))
	{
		nfa_free(nfa);
		free(entrypoint);
		return (NULL);
	}
	nfa_free(nfa);
	return (entrypoint);
}
