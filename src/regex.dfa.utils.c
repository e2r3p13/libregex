/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:51:56 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/14 12:36:03 by bccyv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.dfa.h>
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
	st->is_final = false;
	st->links = NULL;
	st->flag = 0;
	return (st);
}

/*
**	Fills a vector with all addresses of a dfa, in order to free them or
**	whatever else (printing...).
**	Sets all states flag of the dfa to 0
*/

static void	dfa_get_addresses(t_ds *st, t_vec *v)
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

static size_t	dfa_get_size(t_ds *st)
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

/*
**	static int		fa(t_ds *st, t_vec *v)
**	{
**		size_t i;
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
**	void			dfa_print(t_ds *entrypoint)
**	{
**		t_vec		vec;
**		size_t		i;
**		t_link_lst	*links;
**
**		vec.size = 0;
**		vec.addr = malloc(sizeof(void *) * dfa_get_size(entrypoint));
**		dfa_get_addresses(entrypoint, &vec);
**		i = 0;
**		while (i < vec.size)
**		{
**			printf("%zu", i + 1);
**			if (((t_ds *)vec.addr[i])->is_final)
**				printf("f");
**			printf(": ");
**			links = ((t_ds *)vec.addr[i])->links;
**			while (links)
**			{
**				printf("\t%d ", fa(links->link.next, &vec));
**				links = links->next;
**			}
**			printf("\n");
**			i++;
**		}
**		printf("\n");
**	}
*/
