/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glafond- <glafond-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:42:50 by glafond-          #+#    #+#             */
/*   Updated: 2021/04/28 18:44:20 by glafond-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.fa.h>
#include <stdlib.h>

t_ds	*dfa_state_new(void)
{
	t_ds	*st;

	st = malloc(sizeof(t_ds));
	if (!st)
		return (NULL);
	st->is_final = 0;
	st->links = NULL;
	st->flag = 0;
	return (st);
}

int	e_closure(t_ns *st, t_set *set)
{
	if (!is_state_in_set(st, set))
	{
		if (set_push(st, set) < 0)
			return (-1);
		if (is_epsilon(st->left.pattern))
		{
			if (e_closure(st->left.next, set) < 0)
				return (-1);
		}
		if (is_epsilon(st->right.pattern))
		{
			if (e_closure(st->right.next, set) < 0)
				return (-1);
		}
	}
	return (0);
}
