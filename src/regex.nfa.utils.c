/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:40:00 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/19 14:55:01 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.fa.h>
#include <stdlib.h>
#include <stdio.h>

size_t	nfa_get_size(t_ns *st)
{
	if (!st || st->flag == 1)
		return (0);
	st->flag = 1;
	return (1 + nfa_get_size(st->left.next) + nfa_get_size(st->right.next));
}

void	nfa_get_addresses(t_ns *st, t_vec *v)
{
	if (!st || st->flag == 0)
		return ;
	st->flag = 0;
	v->addr[v->size++] = st;
	nfa_get_addresses(st->left.next, v);
	nfa_get_addresses(st->right.next, v);
}

t_ns	*nfa_state_new(void)
{
	t_ns	*st;

	st = malloc(sizeof(t_ns));
	if (!st)
		return (NULL);
	st->is_final = 0;
	nfa_link_init(&st->left);
	nfa_link_init(&st->right);
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
