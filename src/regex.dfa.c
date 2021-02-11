/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 08:12:34 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/11 12:03:21 by lfalkau          ###   ########.fr       */
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
		if (is_state_in_set(s, set))
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

int	dfa_build(t_map *m, t_map *t, t_alphabet *a)
{
	t_alphabet	*p;
	t_set		*s;
	t_ds		*d;

	p = a;
	while (p)
	{
		set = set_new();
		move(m->set, p->pattern, set);
		if (!(node = set_in_table(set, table)))
		{
			d = dfa_push(m->state, p->pattern);
			m = map_push(t, d, set);
			dfa_build(m, t, a);
		}
		else
		{
			free(set);
			dfa_create_connection(m->state, node->state ,p->pattern);
		}
		p = p->next;
	}
	return (0);
}

t_dfa *nfa_to_dfa(t_nfa *nfa)
{
	t_dfa	*dfa;
	t_map	*table;

	dfa = dfa_new();
	table = map_new(dfa->entrypoint, NULL);
	e_closure(nfa->entrypoint, table->set);
	if (contains_final_state(table->set))
		dfa->entrypoint->is_final = true;
	dfa_build(dfa->entrypoint, table, nfa->s_alphabet);
	map_free(table);
	return (dfa);
}
