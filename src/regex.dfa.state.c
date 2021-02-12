/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.state.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 21:29:49 by bccyv             #+#    #+#             */
/*   Updated: 2021/02/12 21:30:28 by bccyv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.dfa.h>
#include <stdlib.h>
#include <libft.h>

/*
**	Allocates and initialize a dfa state.
*/
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

/*
**	Free a dfa state and its related data.
*/
void	dfa_state_free(t_ds *state)
{
	dfa_links_free(state->links);
	free(state);
}
