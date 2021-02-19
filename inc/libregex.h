/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libregex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bccyv <bccyv@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:40:30 by bccyv             #+#    #+#             */
/*   Updated: 2021/02/19 14:19:19 by lfalkau          ###   ########.fr       */
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
**	t_alphabet is a linked list containing all accepted patterns.
**
**	pattern: The pattern stored by this node.
**	next: A pointer to the next node.
*/
typedef struct s_alphabet
{
	t_pattern			pattern;
	struct s_alphabet	*next;
}	t_alphabet;

/*
**	t_link represents a link from one state to another.
**
**	match: A function that returns 1 if the input character c can cross the link
**	with the pattern s.
**	pattern: The pattern that must be matched to take the link.
**	next: The nfa or dfa state the link points to.
*/
typedef struct s_link
{
	int			(*match)(t_pattern s, int c);
	t_pattern	pattern;
	void		*next;
}	t_link;

/*
**	s_link_lst is a linked list of t_link.
*/
typedef struct s_link_lst
{
	t_link				link;
	struct s_link_lst	*next;
}	t_link_lst;

/*
**	t_ds represents a state of a deterministic finite automaton.
**
**	is_final: 1 if the state is an accepting state, 0 otherwise.
**	links: A linked list containing all links from one state to another.
**	flag: A bit used to cross a hole NFA (set of nfa states).
*/
typedef struct s_dfa_state
{
	int			is_final;
	t_link_lst	*links;
	uint8_t		flag : 1;
}	t_ds;

/*
**	t_regex stores a dfa and its related regular expresion.
**
**	entrypoint: A pointer to the first dfa entry state.
**	re_string: A string containing the literal regular expression.
**
*/
typedef struct s_regex
{
	t_ds	*entrypoint;
	char	*re_string;
}	t_regex;

/* ************************************************************************** */
/*	Public API functions                                                      */
/* ************************************************************************** */

/*
**	Create a t_regex structure from a literal regex expression.
**	Returns 0 on success, -1 on failure.
*/
int		re_compile(t_regex *regex, const char *str);

/*
**	TODO: Big function with flags
*/
int		re_execute(t_regex *regex, const char *str);

/*
**	Returns 1 if the hole string str match the given regex struct, 0 otherwise.
*/
int		re_match(t_regex *regex, const char *str);

/*
**	Free the regex struct. Needs to be called after each re_compile call, on its
**	return value.
*/
void	re_free(t_regex *regex);

/*
**	Bastard function, waiting for re_execute to be improved to be deleted.
*/
char	*re_bmatch(t_regex *regex, const char *str);

#endif
