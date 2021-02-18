/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:59:56 by bccyv             #+#    #+#             */
/*   Updated: 2021/02/18 18:56:49 by glafond-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <libregex.h>
#include <stdlib.h>
#include <regex.dfa.h>

char	*readfile(const char *filename)
{
	FILE *f;
	long fsize;
	char *string;

	f = fopen(filename, "rb");
	if (!f)
		return (NULL);
	fseek(f, 0, SEEK_END);
	fsize = ftell(f);
	fseek(f, 0, SEEK_SET);
	string = malloc(fsize + 1);
	if (!string)
	{
		fclose(f);
		return (NULL);
	}
	fread(string, 1, fsize, f);
	fclose(f);
	return (string);
}

int	main(int ac, char **av)
{
	t_regex	regex;
	char	*ptr;
	int		ret;
	char	*string;

	if (ac != 3)
	{
		printf("Missing arguments\n");
		printf("usage: %s regex file\n", av[0]);
		return (-1);
	}
	ret = re_compile(&regex, "/\\*(\\*+[\\W\\w]|[\\W\\w]|/)*\\*+/");
	if (ret < 0)
	{
		printf("Regex compilation error.\n");
		return (-1);
	}
	string = readfile(av[2]);
	if (!string)
	{
		re_free(&regex);
		return (-1);
	}
	printf("%s", string);
//	dfa_print(regex.entrypoint);
	ptr = re_bmatch(&regex, string);
	if (!ptr)
		printf("No match found!\n");
	else
	{
		printf("Regex matches: \n");
		write(1, string, ptr - string);
	}
	re_free(&regex);
	return (0);
}
