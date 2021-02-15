/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:40:00 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/15 11:48:27 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.nfa.h>
#include <stdlib.h>
#include <stdio.h>

static size_t	nfa_get_size(t_ns *st)
{
	if (!st || st->flag == 1)
		return (0);
	st->flag = 1;
	return (1 + nfa_get_size(st->left.next) + nfa_get_size(st->right.next));
}

static void	nfa_get_addresses(t_ns *st, t_vec *v)
{
	if (!st || st->flag == 0)
		return ;
	st->flag = 0;
	v->addr[v->size++] = st;
	nfa_get_addresses(st->left.next, v);
	nfa_get_addresses(st->right.next, v);
}

t_ns	*nfa_new_state(void)
{
	t_ns	*st;

	st = malloc(sizeof(t_ns));
	if (!st)
		return (NULL);
	st->is_final = false;
	link_init(&st->left);
	link_init(&st->right);
	st->flag = 0;
	return (st);
}

void	nfa_free(t_ns *nfa)
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

int	nfa_surround(t_ns *b, t_ns *e, t_ns **nb, t_ns **ne)
{
	t_pattern	epsilon;

	if (!e)
		return (-1);
	*nb = nfa_new_state();
	if (!*nb)
		return (-1);
	*ne = nfa_new_state();
	if (!*ne)
	{
		free(*nb);
		return (-1);
	}
	links_cpy(*nb, b);
	links_destroy(b);
	pattern_epsilon(&epsilon);
	link_add(b, epsilon, *nb);
	link_add(e, epsilon, *ne);
	return (0);
}

/*
**	static int		fa(t_ns *st, t_vec *v)
**	{
**		size_t	i;
**
**		i = 0;
**		while (i < v->size)
**		{
**			if (v->addr[i] == st)
**				return (i + 1);
**			i++;
**		}
**		return (0);
**	}
**
**	void			pattern_print(t_pattern pattern)
**	{
**		int		i;
**		char	b;
**		char	c;
**
**		i = 0;
**		while (i < PATTERN_BYTES_LENGTH)
**		{
**			b = 1;
**			c = pattern[i++];
**			while (b)
**			{
**				printf("%c", c & b ? '1' : '0');
**				b <<= 1;
**			}
**		}
**	}
**
**	void			nfa_print(t_ns *nfa)
**	{
**		t_vec	vec;
**		size_t	i;
**		t_ns	*node;
**
**		vec.size = 0;
**		vec.addr = malloc(sizeof(void *) * nfa_get_size(nfa));
**		nfa_get_addresses(nfa, &vec);
**		i = 0;
**		while (i < vec.size)
**		{
**			node = (t_ns *)(vec.addr)[i];
**			printf("%zu: left -> %d ", i + 1, fa(node->left.next, &vec));
**			printf(" right -> %d ", fa(node->right.next, &vec));
**			printf("\n");
**			i++;
**		}
**	}
*/
