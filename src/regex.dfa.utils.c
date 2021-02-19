/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:51:56 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/19 14:59:49 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.fa.h>
#include <stdlib.h>

/*
**	Allocates and initialize a new dfa state.
*/

t_ds	*dfa_state_new(void)
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

/*
**	Fills a vector with all addresses of a dfa, in order to free them or
**	whatever else (printing...).
**	Sets all states flag of the dfa to 0
*/

void	dfa_get_addresses(t_ds *st, t_vec *v)
{
	t_link_lst	*links;

	if (!st || st->flag == 0)
		return ;
	st->flag = 0;
	v->addr[v->size++] = st;
	links = st->links;
	while (links)
	{
		dfa_get_addresses(links->link.next, v);
		links = links->next;
	}
}

/*
**	Computes recursively the size of a dfa, in order to free them or
**	whatever else (printing...).
**	Sets all states flag of the dfa to 0.
*/

size_t	dfa_get_size(t_ds *st)
{
	t_link_lst	*links;
	int			total;

	if (!st || st->flag == 1)
		return (0);
	st->flag = 1;
	total = 1;
	links = st->links;
	while (links)
	{
		total += dfa_get_size(links->link.next);
		links = links->next;
	}
	return (total);
}

/*
**	Recursively free a link linked list. Used by dfa_free
*/

static void	dfa_links_free(t_link_lst *links)
{
	if (links)
	{
		dfa_links_free(links->next);
		free(links);
	}
}

/*
**	Free each states of a dfa, and their links.
*/

void	dfa_free(t_ds *dfa)
{
	t_vec	vec;
	size_t	i;

	vec.size = 0;
	vec.addr = malloc(sizeof(void *) * dfa_get_size(dfa));
	dfa_get_addresses(dfa, &vec);
	i = 0;
	while (i < vec.size)
	{
		dfa_links_free(((t_ds *)vec.addr[i])->links);
		free(vec.addr[i]);
		i++;
	}
	free(vec.addr);
}
