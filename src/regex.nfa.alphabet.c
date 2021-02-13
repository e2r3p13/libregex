/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.alphabet.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glafond- <glafond-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 05:13:38 by glafond-          #+#    #+#             */
/*   Updated: 2021/02/13 09:03:42 by glafond-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.nfa.h>
#include <regex.fa.h>
#include <stdlib.h>

static t_alphabet	*alphabet_new_pattern(t_pattern pattern)
{
	t_alphabet	*node;

	if (!(node = (t_alphabet *)malloc(sizeof(t_alphabet))))
		return (NULL);
	pattern_copy(node->pattern, pattern);
	node->next = NULL;
	return (node);
}

int					*alphabet_add_pattern(t_alphabet **head, t_pattern pattern)
{
	t_alphabet	*walk;
	t_alphabet	**ptr;

	if (!*head)
	{
		if (!(*head = alphabet_new_pattern(t_pattern pattern)))
			return (-1);
		return (0);
	}
	walk = *head;
	while (walk->next)
	{
		if (!pattern_cmp(pattern, walk->pattern))
			return (0);
		walk = walk->next;
	}
	if (!(walk->next = alphabet_new_pattern(t_pattern pattern)))
		return (-1);
	return (0);
}
