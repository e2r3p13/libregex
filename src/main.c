/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:59:56 by bccyv             #+#    #+#             */
/*   Updated: 2021/02/03 11:23:36 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libregex.h"

int main(__unused int ac, char **av)
{
	t_nfa *regex;


	if (!(regex = str_to_nfa(av[1])))
	{
		printf("Error while creating nfa\n");
		return (1);
	}
	// nfa_print(regex->entrypoint, 0);
	//printf(nfa_match(regex, av[2]) ? "match" : "don't match");

	nfa_free(regex);
	return (0);
}
