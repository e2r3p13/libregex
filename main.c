/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:59:56 by bccyv             #+#    #+#             */
/*   Updated: 2021/02/14 08:46:53 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libregex.h>
#include <stdlib.h>

void __attribute__((destructor)) calledLast();

int main(int ac, char **av)
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
	ret = re_execute(&regex, av[2]);
	if (!ret)
		printf("Regex not match!\n");
	else
		printf("Regex match: %d\n",  ret);
	return (0);
}

void calledLast()
{
    // system("leaks a.out");
}
