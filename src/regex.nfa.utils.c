/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:40:00 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/14 09:34:05 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.nfa.h>
#include <regex.fa.h>
#include <stdlib.h>
#include <stdio.h>

static size_t	nfa_get_size(t_ns *st)
{
	if (!st || st->flag == 1)
		return (0);
	st->flag = 1;
	return (1 + nfa_get_size(st->left.next) + nfa_get_size(st->right.next));
}

static void		nfa_get_addresses(t_ns *st, t_vec *v)
{
	if (!st || st->flag == 0)
		return ;
	st->flag = 0;
	v->addr[v->size++] = st;
	nfa_get_addresses(st->left.next, v);
	nfa_get_addresses(st->right.next, v);
}

t_ns			*nfa_new_state(void)
{
	t_ns *st;

	if (!(st = malloc(sizeof(t_ns))))
		return (NULL);
	st->is_final = false;
	link_init(&st->left);
	link_init(&st->right);
	st->flag = 0;
	return (st);
}

void			nfa_free(t_ns *nfa)
{
	t_vec	vec;
	size_t	i;

	vec.size = 0;
	vec.addr = malloc(sizeof(void *) * nfa_get_size(nfa));
	nfa_get_addresses(nfa, &vec);
	i = 0;
	while (i < vec.size)
	{
		free(vec.addr[i]);
		i++;
	}
	free(vec.addr);
}

static int		fa(t_ns *st, t_vec *v)
{
	size_t	i;

	i = 0;
	while (i < v->size)
	{
		if (v->addr[i] == st)
			return (i + 1);
	}
	return (0);
}

void			pattern_print(t_pattern pattern)
{
	int		i;
	char	b;
	char	c;

	i = 0;
	while (i < PATTERN_MAX_LENGTH)
	{
		b = 1;
		c = pattern[i++];
		while (b)
		{
			printf("%c", c & b ? '1' : '0');
			b <<= 1;
		}
	}
}

void			nfa_print(t_ns *nfa)
{
	t_vec	vec;
	size_t	i;
	t_ns	*node;

	vec.size = 0;
	vec.addr = malloc(sizeof(void *) * nfa_get_size(nfa));
	nfa_get_addresses(nfa, &vec);
	i = 0;
	while (i < vec.size)
	{
		node = (t_nfa_state *)(vec.addr)[i];
		printf("%zu: left -> %d ", i + 1, fa(node->left.next, &vec));
		printf(" right -> %d ", fa(node->right.next, &vec));
		printf("\n");
		i++;
	}
}
