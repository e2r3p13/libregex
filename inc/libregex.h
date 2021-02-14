/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libregex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:40:30 by bccyv             #+#    #+#             */
/*   Updated: 2021/02/14 10:03:32 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBREGEX_H
# define LIBREGEX_H

# include <regex.nfa.h>
# include <regex.dfa.h>

typedef struct	s_regex
{
	t_ds		*entrypoint;
	char		*re_string;
}				t_regex;

int				re_compile(t_regex *regex, const char *str);
int				re_execute(t_regex *regex, const char *str);

#endif
