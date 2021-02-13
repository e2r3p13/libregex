/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:01:45 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/13 12:36:47 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.dfa.h>
#include <stdlib.h>
#include <stdio.h>
#include <libft.h>

/*
**	Allocates a new set (which basically is a dynamic array of states addresses)
**	SET_DFL_SIZE is the size of the array before a reallocation.
*/
t_set		*set_new()
{
	t_set	*set;

	if (!(set = malloc(sizeof(t_set))))
		return (NULL);
	if (!(set->addr = malloc(sizeof(t_ns *) * SET_DFL_SIZE)))
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
	if (!(new_addr = malloc(sizeof(t_ns *) * new_cap)))
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
int			set_push(t_ns *state, t_set *set)
{
	if (set->size == set->capacity && set_realloc(set) < 0)
		return (-1);
	set->addr[set->size++] = state;
	return (0);
}

/*
**	Return true if a state is in a set, false otherwise
*/
t_bool		is_state_in_set(t_ns *state, t_set *set)
{
	size_t i;

	i = 0;
	while (i < set->size)
	{
		if (set->addr[i] == state)
			return (true);
		i++;
	}
	return (false);
}

t_bool		set_contains_final_state(t_set *set)
{
	size_t	i;

	i = 0;
	while (i < set->size)
	{
		if (set->addr[i]->is_final)
			return (true);
		i++;
	}
	return (false);
}

/*
**	Too obvious to comment, I guess
*/
void		set_free(t_set *set)
{
	if (set)
	{
		if (set->addr)
			free(set->addr);
		free(set);
	}
}

/*
**	Compares two sets. The order of the elements doesn't matter, e.g.
**	{0, 3, 2, 1} and {0, 1, 2, 3} are equal
*/
t_bool		set_cmp(t_set *a, t_set *b)
{
	t_bool	found;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < a->size)
	{
		found = false;
		j = 0;
		while (j < b->size)
		{
			if (a->addr[i] == b->addr[j])
				found = true;
			j++;
		}
		if (!found)
			return (false);
		i++;
	}
	return (true);
}

void	set_print(t_set *set)
{
	printf("{");
	for (size_t i = 0; i < set->size; i++)
	{
		printf("%p", set->addr[i]);
		if (i < set->size - 1)
			printf(", ");
	}
	printf("}");
}
