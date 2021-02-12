/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.state.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 21:29:49 by bccyv             #+#    #+#             */
/*   Updated: 2021/02/12 15:27:00 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.dfa.h>
#include <stdlib.h>
#include <libft.h>

t_ds	*dfa_state_new(void)
{
	t_ds *st;

	if (!(st = malloc(sizeof(t_ds))))
		return (NULL);
	st->is_final = false;
	st->links = NULL;
	st->flag = 0;
	return (st);
}

void	dfa_state_free(t_ds *state)
{
	dfa_links_free(state->links);
	free(state);
}
