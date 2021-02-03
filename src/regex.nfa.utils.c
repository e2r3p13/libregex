/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 08:40:00 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/03 08:41:01 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libregex.h"
#include <stdio.h>

void nfa_print(t_state *st, int lvl)
{
	for (int i = 0; i < lvl; i++)
		printf("\t");
	printf("ST: %p, LEFT: %p (%.*s), RIGHT: %p (%.*s)\n", st, st->left.next, st->left.pattern.start ? (int)(st->left.pattern.end - st->left.pattern.start) + 1 : 0 , st->left.pattern.start, st->right.next, st->right.pattern.start ? (int)(st->right.pattern.end - st->right.pattern.start) + 1 : 0 , st->right.pattern.start);
	if ( st->left.next)
		nfa_print(st->left.next, lvl + 1);
	if ( st->right.next)
		nfa_print(st->right.next, lvl + 1);
}
