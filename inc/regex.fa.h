/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.fa.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:27:43 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/14 11:53:24 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGEX_FA_H
# define REGEX_FA_H

# include <stdint.h>

/*
**	This typedef stores accepted characters in the pattern
**	with a 128 bits bitfield. (always a mupliple of 8 bytes)
*/
# define PATTERN_BYTES_LENGTH 16

typedef uint8_t				t_pattern[PATTERN_BYTES_LENGTH];
typedef struct s_alphabet	t_alphabet;
typedef struct s_link		t_link;

/*
**	A linked list containing all accepted patterns
*/
struct s_alphabet
{
	t_pattern	pattern;
	t_alphabet	*next;
};

/*
**	This structure represents a link to go from one state to another.
**	In order to follow the link, the next input character must
**	match the stored pattern.
**	It can be evaluated with the match function.
**	A link with a next set to NULL is considered to be an epsilon link,
**	meaning the match function will always return true.
*/
struct s_link
{
	int			(*match)(t_pattern s, int c);
	t_pattern	pattern;
	void		*next;
};

int		alphabet_add_pattern(t_alphabet **head, t_pattern p);
int		pattern_add_char(t_pattern *p, int c);
int		pattern_parse(t_pattern *p, const char **ptr);
int		pattern_escape(t_pattern *p, const char **ptr);
void	pattern_epsilon(t_pattern *p);
int		is_epsilon(t_pattern p);
int		pattern_match(t_pattern p, int c);
int		pattern_copy(t_pattern dst, t_pattern src);
int		pattern_cmp(t_pattern a, t_pattern b);

#endif
