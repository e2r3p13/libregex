/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:51:56 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/12 18:45:41 by bccyv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.dfa.h>
#include <stdlib.h>
#include <stdio.h>

t_dfa	*dfa_new(void)
{
	t_dfa	*dfa;

	if (!(dfa = malloc(sizeof(t_dfa))))
		return (NULL);
	if (!(dfa->entrypoint = dfa_state_new()))
	{
		free(dfa);
		return (NULL);
	}
	return (dfa);
}

static void		dfa_get_addresses(t_ds *st, t_vec *v)
{
	if (!st || st->flag == 0)
		return ;
	st->flag = 0;
	v->addr[v->size++] = st;
	t_link_lst *links = st->links;
	while (links)
	{
		dfa_get_addresses(st->links->link.next, v);
		links = links->next;
	}
}

static size_t	dfa_get_size(t_ds *st)
{
	int total = 1;
	if (!st || st->flag == 1)
		return (0);
	st->flag = 1;
	t_link_lst *links = st->links;
	while (links)
	{
		total += dfa_get_size(st->links->link.next);
		links = links->next;
	}
	return (total);
}

static int	fa(t_ds *st, t_vec *v)
{
	for (size_t i = 0; i < v->size; i++)
		if (v->addr[i] == st)
			return (i + 1);
	return (0);
}

void		dfa_print(t_dfa *dfa)
{
	t_vec	vec;
	size_t	i;

	vec.size = 0;
	vec.addr = malloc(sizeof(void *) * dfa_get_size(dfa->entrypoint));
	dfa_get_addresses(dfa->entrypoint, &vec);
	i = 0;
	while (i < vec.size)
	{
		printf("%zu:", i + 1);
		t_ds *st = (t_ds *)(vec.addr[i]);
		t_link_lst *links = st->links;
		while (links)
		{
			printf("\t%d", fa(st->links->link.next, &vec));
			links = links->next;
		}
		i++;
	}
}
