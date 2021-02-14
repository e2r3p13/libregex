/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.nfa.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:40:58 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/14 09:47:42 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGEX_NFA_H
# define REGEX_NFA_H

# include <libft.h>
# include <regex.fa.h>

typedef struct s_nfa_state	t_ns;
typedef struct s_nfa_state	t_nfa_state;
typedef struct s_vec		t_vec;

/*
**	t_ns represents a state of an automaton.
**	It keeps two links which can lead to its two children (at most).
**	t_ns nodes are used to construct our nfa / dfa.
*/
struct				s_nfa_state
{
	t_bool			is_final;
	t_link			left;
	t_link			right;
	unsigned int	flag : 1;
};

/*
**	A simple vector structure used to store nfa states addresses.
*/
struct				s_vec
{
	size_t			size;
	void			**addr;
};

t_ns				*nfa_new_state(void);
void				link_init(t_link *ln);
void				link_add(t_ns *st, t_pattern pattern, t_ns *next);
void				links_destroy(t_ns *st);
void				links_cpy(t_ns *dst, t_ns *src);
t_ns				*str_to_nfa(const char *str, t_alphabet **a);
void				nfa_free(t_ns *nfa);
t_ns				*nfa_create(t_ns *b, t_alphabet **a, const char **p, t_bool n);
t_ns				*nfa_build_or(t_ns *b, t_alphabet **a, t_ns *e, const char **p, t_bool n);
t_ns				*nfa_add_pattern(t_ns *beg, t_alphabet **a, const char **p);
t_ns				*nfa_build_quantifier(t_ns *b, t_ns *e, const char **p);
int					nfa_surruond(t_ns *b, t_ns *e, t_ns **nb, t_ns **ne);
void				nfa_print(t_ns *nfa);
t_bool				nfa_has_link(t_pattern *p, t_ns *state);

#endif
