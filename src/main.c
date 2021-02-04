/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:59:56 by bccyv             #+#    #+#             */
/*   Updated: 2021/02/04 14:48:01 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libregex.h"
#include <stdlib.h>

void __attribute__((destructor)) calledLast();

int main(__unused int ac, char **av)
{
	t_nfa *regex;


	if (!(regex = str_to_nfa(av[1])))
	{
		printf("Error while creating nfa\n");
		return (1);
	}

	nfa_print(regex);
	nfa_free(regex);

	return (0);
}

void calledLast()
{
    // system("leaks a.out");
}
