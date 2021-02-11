/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.fa.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:27:43 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/11 07:45:08 by glafond-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGEX_FA_H
# define REGEX_FA_H

/*
**	This structure store all character in the pattern with 128bits.
*/
# define PATTERN_MAX_LENGTH 16
typedef char	t_pattern[PATTERN_MAX_LENGTH];

typedef struct	s_alphabet
{
	t_pattern	pattern;
	t_alphabet	*next;
}				t_alphabet;

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

#endif /* REGEX_FA_H */
