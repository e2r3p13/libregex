/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:59:56 by bccyv             #+#    #+#             */
/*   Updated: 2021/02/13 18:55:06 by bccyv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libregex.h>
#include <stdlib.h>

void __attribute__((destructor)) calledLast();

int main(int ac, char **av)
{
	t_nfa *nfa;
	t_dfa *regex;

	t_alphabet	*alphabet = NULL;

	(void)ac;
	if (!(nfa = str_to_nfa(av[1], &alphabet)))
	{
		printf("Error while creating nfa\n");
		return (1);
	}

	printf("nfa:\n");
	nfa_print(nfa);
	regex = nfa_to_dfa(nfa, alphabet);
	printf("\ndfa:\n");
	dfa_print(regex);
	nfa_free(nfa);

	return (0);
}

void calledLast()
{
    // system("leaks a.out");
}
