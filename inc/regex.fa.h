/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.fa.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:27:43 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/10 11:28:42 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGEX_FA_H
#define REGEX_FA_H

typedef struct s_pattern	t_pattern;
typedef struct s_link		t_link;

/*
**	This structure represents a pattern substring from a regex string.
**	It internally keeps a pointer to the beginning of the substring,
**	and another one to the end.
*/
struct	s_pattern
{
	const char *start;
	const char *end;
};

/*
**	This structure represents a link to go from one state to another.
**	In order to follow the link, the next input character must
**	match the stored pattern.
**	It can be evaluated with the match function.
**	A link with a next set to NULL is considered to be an epsilon link,
**	meaning the match function will always return true.
*/
struct	s_link
{
	int			(*match)(t_pattern s, int c);
	t_pattern	pattern;
	void		*next;
};

#endif /* REGEX_FA_H */
