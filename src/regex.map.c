/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:05:03 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/20 20:00:21 by bccyv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.fa.h>
#include <stdlib.h>

t_map	*map_new(t_ds *st, t_set *set)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->state = st;
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

void	map_push(t_map *dst, t_map *src)
{
	if (!dst)
		return ;
	while (dst->next)
		dst = dst->next;
	dst->next = src;
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
