/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libregex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:40:30 by bccyv             #+#    #+#             */
/*   Updated: 2021/02/10 11:12:08 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBREGEX_H
#define LIBREGEX_H

#include <regex.nfa.h>
#include <regex.dfa.h>

/*
**	Following characters need to be escaped to be part of a pattern
*/
#define SPE_CHAR "[]{}()|*+?^"

#endif /* LIBREGEX_H */
