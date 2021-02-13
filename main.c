/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:59:56 by bccyv             #+#    #+#             */
/*   Updated: 2021/02/12 18:19:29 by bccyv            ###   ########.fr       */
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

	(void)ac;
	if (!(nfa = str_to_nfa(av[1])))
	{
		printf("Error while creating nfa\n");
		return (1);
	}

	nfa_print(nfa);
	regex = nfa_to_dfa(nfa);
	dfa_print(regex);
	nfa_free(nfa);

	return (0);
}

void calledLast()
{
    // system("leaks a.out");
}
