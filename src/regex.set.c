/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:01:45 by lfalkau           #+#    #+#             */
/*   Updated: 2021/04/28 19:08:45 by glafond-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <regex.fa.h>
#include <regex.ft.h>

t_set	*set_new(void)
{
	t_set	*set;

	set = malloc(sizeof(t_set));
	if (!set)
		return (NULL);
	set->addr = malloc(sizeof(t_ns *) * SET_DFL_SIZE);
	if (!set->addr)
	{
		free(set);
		return (NULL);
	}
	ft_memset(set->addr, 0, sizeof(t_ns *) * SET_DFL_SIZE);
	set->capacity = SET_DFL_SIZE;
	set->size = 0;
	return (set);
}

int	is_state_in_set(t_ns *st, t_set *set)
{
	size_t	i;

	i = 0;
	while (i < set->size)
	{
		if (set->addr[i] == st)
			return (1);
		i++;
	}
	return (0);
}

int	set_contains_final_state(t_set *set)
{
	size_t	i;

	i = 0;
	while (i < set->size)
	{
		if (set->addr[i]->is_final)
			return (1);
		i++;
	}
	return (0);
}
