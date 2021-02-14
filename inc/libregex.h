/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libregex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:40:30 by bccyv             #+#    #+#             */
/*   Updated: 2021/02/14 04:19:17 by glafond-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBREGEX_H
#define LIBREGEX_H

#include <regex.nfa.h>
#include <regex.dfa.h>

int		re_compile(t_regex *regex, const char *str);
int		re_execute(t_regex *regex, const char *str);

#endif /* LIBREGEX_H */
