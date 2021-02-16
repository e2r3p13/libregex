/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:59:56 by bccyv             #+#    #+#             */
/*   Updated: 2021/02/16 16:57:07 by glafond-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libregex.h>
#include <stdlib.h>
#include <regex.dfa.h>

int	main(int ac, char **av)
{
	t_regex	regex;
	int		ret;

	if (ac != 3)
	{
		printf("Missing arguments\n");
		return (-1);
	}
	ret = re_compile(&regex, av[1]);
	if (ret < 0)
	{
		printf("Regex compilation error.\n");
		return (-1);
	}
//	dfa_print(regex.entrypoint);
	ret = re_execute(&regex, av[2]);
	if (!ret)
		printf("No match found!\n");
	else
		printf("Regex matches: %d\n", ret);
	re_free(&regex);
	return (0);
}
