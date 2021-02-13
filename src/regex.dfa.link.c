/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.link.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:45:42 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/13 12:57:28 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.dfa.h>
#include <stdlib.h>
#include <stdio.h>

/*
**	Connects first state to last state with the p pattern.
**	p pattern is added to the link linked list of first.
*/
int		dfa_create_connection(t_ds *first, t_pattern *p, t_ds *last)
{
	t_link_lst	*lklst;
	t_link_lst	*tmp;

	if (!(lklst = malloc(sizeof(t_link_lst))))
		return (-1);
	pattern_copy(lklst->link.pattern, *p);

	lklst->link.next = last;
	lklst->next = NULL;
	if ((tmp = first->links))
	{
		while (tmp->next)
		{
			tmp = tmp->next;
			printf("%p\n", tmp);
		}
		tmp->next = lklst;
	}
	else
		first->links = lklst;
	return (0);
}

/*
**	Recursively free a link linked list. Used by dfa_free
*/
void	dfa_links_free(t_link_lst *links)
{
	if (links)
	{
		dfa_links_free(links->next);
		free(links);
	}
}
