/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:40:00 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/10 11:25:02 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libregex.h>
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

t_nfa			*nfa_new(const char *str)
{
	t_nfa *nfa;

	if (!str || !(nfa = malloc(sizeof(t_nfa))))
		return (NULL);
	ft_bzero(nfa, sizeof(t_nfa));
	if (!(nfa->re_expr = ft_strdup(str)))
	{
		free(nfa);
		return (NULL);
	}
	if (!(nfa->entrypoint = state_new()))
	{
		nfa_free(nfa);
		return (NULL);
	}
	return (nfa);
}

void			nfa_free(t_nfa *nfa)
{
	t_vec	vec;
	size_t	i;

	vec.size = 0;
	vec.addr = malloc(sizeof(void *) * nfa_get_size(nfa->entrypoint));
	nfa_get_addresses(nfa->entrypoint, &vec);
	i = 0;
	while (i < vec.size)
	{
		free(vec.addr[i]);
		i++;
	}
	free(vec.addr);
	if (nfa->re_expr)
		free(nfa->re_expr);
	free(nfa);
}

static int	fa(t_ns *st, t_vec *v)
{
	for (size_t i = 0; i < v->size; i++)
		if (v->addr[i] == st)
			return (i + 1);
	return (0);
}

void		nfa_print(t_nfa *nfa)
{
	t_vec	vec;
	size_t	i;

	vec.size = 0;
	vec.addr = malloc(sizeof(void *) * nfa_get_size(nfa->entrypoint));
	nfa_get_addresses(nfa->entrypoint, &vec);
	i = 0;
	while (i < vec.size)
	{
		int l = fa(vec.addr[i]->left.next, &vec);
		int r = fa(vec.addr[i]->right.next, &vec);
		printf("%zu:\tleft --> %d\tright --> %d\n", i + 1, l, r);
		i++;
	}
}
