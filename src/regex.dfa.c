/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 08:12:34 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/19 20:58:47 by bccyv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.fa.h>
#include <stdlib.h>

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
		dfa_create(next_st_map, hole_map, a);
	}
	else
		set_free(move_set);
	if (move_set->size > 0)
		return (next_state);
	return (NULL);
}

/*
**	Converts a NFA into a DFA, following the subset construction method.
**	See ttps://tajseer.files.wordpress.com/2014/06/re-nfa-dfa.pdf.
*/

int	dfa_create(t_map *st_map, t_map *hole_map, t_alphabet *a)
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
	if (dfa_create(map, map, alphabet) < 0)
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
	nfa = nfa_generate(str, &alphabet);
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
