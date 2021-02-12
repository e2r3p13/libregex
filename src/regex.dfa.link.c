/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.link.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:45:42 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/12 15:51:47 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.dfa.h>
#include <stdlib.h>

int		dfa_create_connection(t_ds *first, t_pattern *p, t_ds *last)
{
	t_link_lst	*lklst;
	t_link_lst	*tmp;

	if (!(lklst = malloc(sizeof(t_link_lst))))
		return (-1);
	ft_memcpy(lklst->link.pattern, p, sizeof(t_pattern));
	lklst->link.next = last;
	if ((tmp = first->links))
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = lklst;
	}
	else
		first->links = lklst;
	return (0);
}

void	dfa_links_free(t_link_lst *links)
{
	if (links)
	{
		dfa_links_free(links->next);
		free(links);
	}
}
