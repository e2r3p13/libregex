/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 08:12:34 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/20 01:04:00 by bccyv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.fa.h>
#include <stdlib.h>

static int	dfa_create(t_map *, t_map *, t_alphabet *);

static t_ds	*dfa_state_new(void)
{
	t_ds	*st;

	st = malloc(sizeof(t_ds));
	if (!st)
		return (NULL);
	st->is_final = 0;
	st->links = NULL;
	st->flag = 0;
	return (st);
}

int	e_closure(t_ns *st, t_set *dst)
{
	if (!is_state_in_set(st, dst))
	{
		if (set_push(st, dst) < 0)
			return (-1);
		if (is_epsilon(st->left.pattern))
		{
			if (e_closure(st->left.next, dst) < 0)
				return (-1);
		}
		if (is_epsilon(st->right.pattern))
		{
			if (e_closure(st->right.next, dst) < 0)
				return (-1);
		}
	}
	return (0);
}

int	move_closure(t_set *dst, t_set *src, t_pattern *p)
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

static t_ds	*dfa_get_next_state(t_set *set, t_map *wmap, t_alphabet *a)
{
	t_map	*nmap;
	t_ds	*st;

	st = state_in_map(wmap, set);
	if (set->size > 0 && !st)
	{
		st = dfa_state_new();
		if (!st)
			return (NULL);
		nmap = map_new(st, set);
		if (!nmap)
		{
			dfa_free(st);
			return (NULL);
		}
		map_push(wmap, nmap);
		dfa_create(nmap, wmap, a);
	}
	else
		set_free(set);
	if (set->size > 0)
		return (st);
	return (NULL);
}

/*
**	Converts a NFA into a DFA, following the subset construction method.
**	See ttps://tajseer.files.wordpress.com/2014/06/re-nfa-dfa.pdf.
*/

static int	dfa_create(t_map *cmap, t_map *wmap, t_alphabet *a)
{
	t_alphabet	*c;
	t_set		*set;
	t_ds		*st;

	if (set_contains_final_state(cmap->set))
		cmap->state->is_final = 1;
	c = a;
	while (c)
	{
		set = set_new();
		if (!set)
			return (-1);
		if (move_closure(set, cmap->set, &c->pattern) < 0)
		{
			set_free(set);
			return (-1);
		}
		st = dfa_get_next_state(set, wmap, a);
		if (set->size && (!st || dfa_link_add(st, cmap->state, &c->pattern)))
			return (-1);
		c = c->next;
	}
	return (0);
}

static int	nfa_to_dfa(t_ds *entrypoint, t_ns *nfa, t_alphabet *a)
{
	t_map	*map;

	map = map_new(entrypoint, NULL);
	if (!map)
		return (-1);
	if (e_closure(nfa, map->set) < 0 || dfa_create(map, map, a) < 0)
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
	t_alphabet	*a;

	a = NULL;
	nfa = nfa_generate(str, &a);
	if (!nfa)
		return (NULL);
	entrypoint = dfa_state_new();
	if (!entrypoint)
	{
		nfa_free(nfa);
		alphabet_free(a);
		return (NULL);
	}
	if (nfa_to_dfa(entrypoint, nfa, a))
	{
		nfa_free(nfa);
		alphabet_free(a);
		free(entrypoint);
		return (NULL);
	}
	nfa_free(nfa);
	alphabet_free(a);
	return (entrypoint);
}
