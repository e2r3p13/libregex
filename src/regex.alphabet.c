/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.alphabet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glafond- <glafond-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 05:13:38 by glafond-          #+#    #+#             */
/*   Updated: 2021/02/14 10:47:44 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int					alphabet_add_pattern(t_alphabet **head, t_pattern pattern)
{
	t_alphabet	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (!pattern_cmp(pattern, tmp->pattern))
			return (0);
		tmp = tmp->next;
	}
	if (!(tmp = alphabet_new_pattern(pattern)))
		return (-1);
	tmp->next = *head;
	*head = tmp;
	return (0);
}
