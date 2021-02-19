/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:05:03 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/19 13:42:42 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.fa.h>
#include <stdlib.h>

/*
**	Allocates and returns a t_map node. its set member is eithen given in
**	argument, or allocated here. state member is always given and should be
**	valid.
*/

t_map	*map_new(t_ds *state, t_set *set)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->state = state;
	map->next = NULL;
	if (set)
		map->set = set;
	else
	{
		map->set = set_new();
		if (!map->set)
		{
			free(map);
			return (NULL);
		}
	}
	return (map);
}

/*
**	As t_map acts also as a linked list, this function pushes a t_map node
**	(src) at the end of a t_map list (src).
*/

void	map_push(t_map *dst, t_map *src)
{
	if (!dst)
		return ;
	while (dst->next)
		dst = dst->next;
	dst->next = src;
}

/*
**	If the given set already exists in map (unordered), this function returns
**	the corresponding map's state.
*/

t_ds	*state_in_map(t_map *map, t_set *set)
{
	while (map)
	{
		if (set_cmp(set, map->set))
			return (map->state);
		map = map->next;
	}
	return (NULL);
}

void	map_free(t_map *map)
{
	if (map)
	{
		map_free(map->next);
		set_free(map->set);
		free(map);
	}
}
