/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.link.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:45:42 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/14 11:57:24 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.dfa.h>
#include <stdlib.h>

/*
**	Connects first state to last state with the p pattern.
**	p pattern is added in front of links linked list of first if not
**	already present.
*/

int	dfa_create_connection(t_ds *first, t_pattern *p, t_ds *last)
{
	t_link_lst	*new_link;
	t_link_lst	*checker;

	checker = first->links;
	while (checker)
	{
		if (!pattern_cmp(checker->link.pattern, *p))
			return (0);
		checker = checker->next;
	}
	new_link = malloc(sizeof(t_link_lst));
	if (!new_link)
		return (-1);
	pattern_copy(new_link->link.pattern, *p);
	new_link->link.next = last;
	new_link->next = first->links;
	first->links = new_link;
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
