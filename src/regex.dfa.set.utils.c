/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.set.utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 10:16:32 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/14 12:02:28 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.dfa.h>
#include <stdlib.h>
#include <libft.h>

/*
**	Allocates a new set (which basically is a dynamic array of states addresses)
**	SET_DFL_SIZE is the size of the array before a reallocation.
*/

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

/*
**	Allocates twice as space as current, in order to store more addresses
*/

static int	set_realloc(t_set *set)
{
	t_ns	**new_addr;
	size_t	new_cap;
	size_t	i;

	new_cap = set->capacity * 2;
	new_addr = malloc(sizeof(t_ns *) * new_cap);
	if (!new_addr)
		return (-1);
	i = 0;
	while (i < set->size)
	{
		new_addr[i] = set->addr[i];
		i++;
	}
	free(set->addr);
	set->addr = new_addr;
	set->capacity = new_cap;
	return (0);
}

/*
**	Pushes a state address into a set
*/

int	set_push(t_ns *state, t_set *set)
{
	if (set->size == set->capacity && set_realloc(set) < 0)
		return (-1);
	set->addr[set->size++] = state;
	return (0);
}

/*
**	Too obvious to comment, I guess
*/

void	set_free(t_set *set)
{
	if (set)
	{
		if (set->addr)
			free(set->addr);
		free(set);
	}
}
