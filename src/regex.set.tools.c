/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.set.tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glafond- <glafond-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:38:00 by glafond-          #+#    #+#             */
/*   Updated: 2021/04/28 18:53:31 by glafond-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.fa.h>
#include <stdlib.h>
#include <libft.h>

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

int	set_push(t_ns *st, t_set *set)
{
	if (set->size == set->capacity && set_realloc(set) < 0)
		return (-1);
	set->addr[set->size++] = st;
	return (0);
}

void	set_free(t_set *set)
{
	if (set)
	{
		if (set->addr)
			free(set->addr);
		free(set);
	}
}

int	set_cmp(t_set *a, t_set *b)
{
	int		found;
	size_t	i;
	size_t	j;

	if (a->size != b->size)
		return (0);
	i = 0;
	while (i < a->size)
	{
		found = 0;
		j = 0;
		while (j < b->size)
		{
			if (a->addr[i] == b->addr[j])
				found = 1;
			j++;
		}
		if (!found)
			return (0);
		i++;
	}
	return (1);
}
