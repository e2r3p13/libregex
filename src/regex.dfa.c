/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 08:12:34 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/19 13:42:01 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.fa.h>
#include <stdlib.h>

static t_ds	*dfa_use_set(t_set *move_set, t_map *hole_map, t_alphabet *a)
{
	t_map	*next_st_map;
	t_ds	*next_state;

	next_state = state_in_map(hole_map, move_set);
	if (move_set->size > 0 && !next_state)
	{
		next_state = dfa_state_new();
		if (!next_state)
			return (NULL);
		next_st_map = map_new(next_state, move_set);
		if (!next_st_map)
		{
			dfa_free(next_state);
			return (NULL);
		}
		map_push(hole_map, next_st_map);
		dfa_build(next_st_map, hole_map, a);
	}
	else
		set_free(move_set);
	if (move_set->size > 0)
		return (next_state);
	return (NULL);
}

/*
**	Converts an nfa into a dfa, following the subset construction method:
**	https://tajseer.files.wordpress.com/2014/06/re-nfa-dfa.pdf
*/

int	dfa_build(t_map *st_map, t_map *hole_map, t_alphabet *a)
{
	t_alphabet	*c;
	t_set		*move_set;
	t_ds		*ns;

	if (set_contains_final_state(st_map->set))
		st_map->state->is_final = 1;
	c = a;
	while (c)
	{
		move_set = set_new();
		if (!move_set)
			return (-1);
		if (e_move_closure(st_map->set, &c->pattern, move_set) < 0)
		{
			set_free(move_set);
			return (-1);
		}
		ns = dfa_use_set(move_set, hole_map, a);
		if (move_set->size > 0)
			if (!ns || dfa_create_connection(st_map->state, &c->pattern, ns))
				return (-1);
		c = c->next;
	}
	return (0);
}

/*
**	Builds the first node of the dfa, and stores it in a t_map structure with
**	the epsilon closure of our nfa's entrypoint as its set.
**	The dfa_build call will construct our dfa from its first node.
*/

static int	nfa_to_dfa(t_ds *entrypoint, t_ns *nfa, t_alphabet *alphabet)
{
	t_map	*map;

	map = map_new(entrypoint, NULL);
	if (!map)
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

t_ds	*dfa_generate(const char *str)
{
	t_ds		*entrypoint;
	t_ns		*nfa;
	t_alphabet	*alphabet;

	alphabet = NULL;
	nfa = str_to_nfa(str, &alphabet);
	if (!nfa)
		return (NULL);
	entrypoint = dfa_state_new();
	if (!entrypoint)
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
	alphabet_free(alphabet);
	return (entrypoint);
}
