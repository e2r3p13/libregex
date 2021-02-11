/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.fa.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:27:43 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/11 10:17:55 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGEX_FA_H
#define REGEX_FA_H

/*
**	This typedef stores accepted characters in the pattern
**	with a 128 bits bitfield.
*/
#define PATTERN_MAX_LENGTH 16
typedef char	t_pattern[PATTERN_MAX_LENGTH];

/*
**	This structure represents a link to go from one state to another.
**	In order to follow the link, the next input character must
**	match the stored pattern.
**	It can be evaluated with the match function.
**	A link with a next set to NULL is considered to be an epsilon link,
**	meaning the match function will always return true.
*/
typedef struct	s_link
{
	int			(*match)(t_pattern s, int c);
	t_pattern	pattern;
	void		*next;
}				t_link;

t_pattern	pattern_parse(const char **ptr);
int			is_epsilon(t_pattern pattern);
int			pattern_match(t_pattern pattern, int c);

#endif /* REGEX_FA_H */
