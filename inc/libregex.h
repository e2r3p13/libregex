/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libregex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:40:30 by bccyv             #+#    #+#             */
/*   Updated: 2021/02/20 00:55:58 by bccyv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBREGEX_H
# define LIBREGEX_H

# include <stdint.h>

/*
**	t_pattern is a bitfield. Each bit represents a character of the ascii table.
**	e.g. 'a' is encoded with the 97th bit of the field.
**	Bits set to 1 are 'accepted' by the pattern.
**	A pattern with the first bit set to 1 represents an epsilon pattern.
*/
# define PATTERN_BYTES_LENGTH 16
typedef uint8_t	t_pattern[PATTERN_BYTES_LENGTH];

/*
**	t_link - Link from one state to another.
**	@match: A function that returns 1 if the input character c can cross
**	the link with the pattern s.
**	@pattern: The pattern that must be matched to go over the link.
**	@next: The state the link points to.
*/
typedef struct s_link
{
	int			(*match)(t_pattern s, int c);
	t_pattern	pattern;
	void		*next;
}	t_link;

/*
**	t_link_lst - A t_link linked list.
**	@link: The link stored by this node.
**	@next: The next node.
*/
typedef struct s_link_lst
{
	t_link				link;
	struct s_link_lst	*next;
}	t_link_lst;

/*
**	t_ds - State of a deterministic finite automaton.
**	@is_final: 1 if the state is an accepting state, 0 otherwise.
**	@links: A linked list containing all links from one state to another.
**	@flag: A bit used to cross a complete DFA.
*/
typedef struct s_ds
{
	int			is_final;
	t_link_lst	*links;
	uint8_t		flag : 1;
}	t_ds;

/*
**	t_regex - Finite tate machine representation of a regular expression.
**	@entrypoint: A pointer to the DFA entry state.
**	@re_string: A string containing the literal regular expression.
*/
typedef struct s_regex
{
	t_ds	*entrypoint;
	char	*re_string;
}	t_regex;

/*
**	re_compile - Creates a t_regex structure from a literal regular expression.
**	@regex:	A pointer to an uninitialized t_regex structure.
**	@str: The literal regular expression you want to compile.
**	Return: 0 if successful, -1 on failure.
*/
int		re_compile(t_regex *regex, const char *str);

/*
**	TODO: Big function with flags
*/
int		re_execute(t_regex *regex, const char *str);

/*
**	re_full_match - Checks for a full match.
**	@regex: A compiled regex pointer.
**	@str: The string in which to search the match.
**	Return: 1 if str fully matches regex, 0 otherwise.
*/
int		re_full_match(t_regex *regex, const char *str);

/*
**	re_free - Frees a t_regex.
**	@regex: A compiled t_regex pointer.
*/
void	re_free(t_regex *regex);

/*
**	TODO: remove this function when re_execute will be improved.
*/
char	*re_bmatch(t_regex *regex, const char *str);

#endif
