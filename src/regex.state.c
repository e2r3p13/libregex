/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 21:29:49 by bccyv             #+#    #+#             */
/*   Updated: 2021/02/04 08:09:07 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libregex.h"
#include <stdlib.h>

t_state	*state_new(void)
{
	t_state *st;

	if (!(st = malloc(sizeof(t_state))))
		return (NULL);
	st->is_final = false;
	link_init(&st->left);
	link_init(&st->right);
	st->flag = 0;
	return (st);
}
