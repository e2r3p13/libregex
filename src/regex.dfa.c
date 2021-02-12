/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 08:12:34 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/12 14:10:53 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.nfa.h>
#include <regex.dfa.h>
#include <stdlib.h>
#include <libft.h>

typedef struct s_set	t_set;
typedef struct s_map	t_map;

#define SET_DFL_SIZE 8

struct s_set
{
	t_ns	**addr;
	size_t	size;
	size_t	capacity;
};

struct s_map
{
	t_ds	*state;
	t_set	*set;
	t_map	*next;
};

t_set	*set_new()
{
	t_set	*set;

	if (!(set = malloc(sizeof(t_set))))
		return (NULL);
	if (!(set->addr = malloc(sizeof(t_ns *) * SET_DFL_SIZE)))
	{
		free(set);
		return (NULL);
	}
	set->capacity = SET_DFL_SIZE;
	set->size = 0;
	return (set);
}

static int set_realloc(t_set *set)
{
	t_ns	**new_addr;
	size_t	new_cap;
	size_t	i;

	new_cap = set->capacity * 2;
	if (!(new_addr = malloc(sizeof(t_ns *) * new_cap)))
		return (-1);
	i = 0;
	while (i < set->size)
	{
		new_addr[i] = set->addr[i];
		i++;
	}
	free(set->addr);
	set->addr = new_addr;
	set->capacity = new_cap;
	return (0);
}

static int set_push(t_ns *state, t_set *set)
{
	if (set->size == set->capacity && set_realloc(set) < 0)
		return (-1);
	set->addr[set->size++] = state;
	return (0);
}

static t_bool is_state_in_set(t_ns *state, t_set *set)
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

static int e_closure(t_ns *s, t_set *set)
{
	if (!is_state_in_set(s, set))
	{
		if (set_push(s, set) < 0)
			return (-1);
		if (is_epsilon(s->left.pattern))
		{
			if (e_closure(s->left.next, set) < 0)
				return (-1);
		}
		if (is_epsilon(s->right.pattern))
		{
			if (e_closure(s->left.next, set) < 0)
				return (-1);
		}
	}
	return (0);
}

static int e_closure_set(t_set *t, t_set *set)
{
	size_t i = 0;

	while (i < t->size)
	{
		if (e_closure(t->addr[i], set) < 0)
			return (-1);
		i++;
	}
	return (0);
}

static int	move(t_set *t, t_pattern *p, t_set *set)
{
	size_t i = 0;

	while (i < t->size)
	{
		// if (is_state_in_set(s, set))
	}
	return (0);
}

static t_map *map_new(t_ds *state, t_set *set)
{
	t_map	*map;

	if (!(map = malloc(sizeof(t_map))))
		return (NULL);
	map->state = state;
	map->next = NULL;
	if (set)
		map->set = set;
	else if (!(map->set = set_new()))
	{
		free(map);
		return (NULL);
	}
	return (map);
}

int dfa_push(t_ds *state, t_pattern p)
{
	t_ds	*new;

	if (!(new = dfa_state_new()))
		return (-1);
	dfa_create_connection(state, new, pattern);
}

/*
**	Converts an nfa into a dfa, following the subset construction method:
**	https://tajseer.files.wordpress.com/2014/06/re-nfa-dfa.pdf
*/
int	dfa_build(t_map *st_map, t_map *hole_map, t_alphabet *a)
{
	t_alphabet	*current_letter;
	t_set		*move_set;
	t_ds		*next_state;
	t_map		*next_st_map;

	current_letter = a;
	while (current_letter)
	{
		if (!(move_set = set_new()))
			return (NULL);
		if (move_epsilon(st_map->set, current_letter->pattern, move_set) < 0)
		{
			set_free(move_set);
			return (NULL);
		}
		if (!(next_state = state_in_map(hole_map, move_set)))
		{
			if (!(next_state = dfa_state_new()))
			{
				set_free(move_set);
				return (NULL);
			}
			if (!(next_st_map = map_new(next_state, move_set)))
			{
				set_free(move_set);
				dfa_state_free(next_state);
				return (NULL);
			}
			map_push(hole_map, next_st_map);
			dfa_build(next_st_map, hole_map, a);
		}
		else
			set_free(move_set);
		if (dfa_create_connection(st_map->state, next_state, current_letter) < 0)
			return (NULL);
		current_letter = current_letter->next;
	}
}

/*
**	Builds the first node of the dfa, and stores it in a t_map structure with
**	the epsilon closure of our nfa's entrypoint as its set.
**	The dfa_build call will construct our dfa from its first node.
*/
t_dfa *nfa_to_dfa(t_nfa *nfa)
{
	t_dfa	*dfa;
	t_map	*map;

	if (!(dfa = dfa_new()))
		return (NULL);
	if (!(map = map_new(dfa->entrypoint, NULL)))
	{
		free(dfa);
		return (NULL);
	}
	if (e_closure(nfa->entrypoint, map->set) < 0)
	{
		free(dfa);
		free(map);
		return (NULL);
	}
	if (!dfa_build(map, map, nfa->alphabet)
	{
		free(dfa);
		free(map);
		return (NULL);
	}
	map_free(map);
	return (dfa);
}
