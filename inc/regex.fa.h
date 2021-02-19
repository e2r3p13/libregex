/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.fa.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:27:43 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/20 00:56:04 by bccyv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGEX_FA_H
# define REGEX_FA_H

# include <libregex.h>
# include <stddef.h>

/*
** First allocation size for t_set dynamic arrays.
*/
# define SET_DFL_SIZE 8

/*
**	t_ds - State of a non deterministic finite automaton.
**	@is_final: 1 if the state is an accepting state, 0 otherwise.
**	@left: First link of a NFA state.
**	@right: Second link of a NFA state.
**	@flag: A bit used to cross a complete NFA.
*/
typedef struct s_ns
{
	int			is_final;
	t_link		left;
	t_link		right;
	uint8_t		flag : 1;
}	t_ns;

/*
**	t_vec - Array of FA states.
**	@size: Size of the array.
**	@addr: The FA state addresses array.
**
**	Used to cross a FA, in order to print or free it.
*/
typedef struct s_vec
{
	size_t	size;
	void	**addr;
}	t_vec;

/*
**	t_set - Dynamic array of NFA states addresses.
**	@size: Size of the array.
**	@capacity: The current allocated size of the array.
**	@addr: The NFA state addresses array.
**
**	Only used to generate an DFA from a NFA.
*/
typedef struct s_set
{
	size_t	size;
	size_t	capacity;
	t_ns	**addr;
}	t_set;

/*
**	t_map - Linked list of t_set and t_ds binded pairs.
**	@state: The binded DFA state.
**	@set: The binded t_set.
**	@next: The next t_map node.
**
**	Only used to generate a DFA from a NFA.
*/
typedef struct s_map
{
	t_ds			*state;
	t_set			*set;
	struct s_map	*next;
}	t_map;

/*
**	t_alphabet - Linked list of accepted patterns.
**	@pattern: The pattern stored by this node.
**	@next: A pointer to the next node.
**
**	Only used to generate a DFA from a NFA.
*/
typedef struct s_alphabet
{
	t_pattern			pattern;
	struct s_alphabet	*next;
}	t_alphabet;

/* ************************************************************************** */
/*	NFA related functions                                                     */
/* ************************************************************************** */

/*
**	nfa_generate - Generates a NFA from a regular expression string.
**	@str: The literal regular expression.
**	@a: The set of non epsilon transitions the NFA will contain.
**	Return: A pointer to the entrypoint of the generated NFA.
*/
t_ns	*nfa_generate(const char *str, t_alphabet **a);

/*
**	nfa_free - Frees a complete NFA.
**	@entrypoint: NFA to be freed.
*/
void	nfa_free(t_ns *entrypoint);

/*
**	nfa_get_size - Gets the number of states of a NFA.
**	@st: Entrypoint of the NFA.
**	Return: Size of the NFA.
**
**	nfa_get_addresses has to be called after nfa_get_size.
*/
size_t	nfa_get_size(t_ns *st);

/*
**	nfa_get_addresses - Fills a vector with all state addresses of a NFA.
**	@st: Entrypoint of the NFA.
**	@vec: The vector to be filled with addresses.
**
**	Has to be called after a nfa_get_size call.
*/
void	nfa_get_addresses(t_ns *st, t_vec *vec);

/*
**	nfa_link_init - Initializes a link.
**	@ln: The link to be initialized.
*/
void	nfa_link_init(t_link *ln);

/*
**	nfa_link_add - Links two NFA states.
**	@src: The "from" state.
**	@dst: The "to" state.
**	@p: The pattern to go from src to dst.
*/
void	nfa_link_add(t_ns *dst, t_ns *src, t_pattern p);

/*
**	nfa_links_destroy - Destroys links of a NFA state.
**	@st: The state to destroy links.
*/
void	nfa_links_destroy(t_ns *st);

/*
**	nfa_links_cpy - Copies links from a NFA state to another.
**	@dst: The NFA state that receives links.
**	@src: The NFA state that sends links.
*/
void	nfa_links_cpy(t_ns *dst, t_ns *src);

/* ************************************************************************** */
/*	DFA related functions                                                     */
/* ************************************************************************** */

/*
**	dfa_generate - Generates a DFA from a regular expression string.
**	@str: The literal regular expression.
**	Return: A pointer to the entrypoint of the generated DFA.
*/
t_ds	*dfa_generate(const char *str);

/*
**	dfa_free - Frees a complete DFA.
**	@entrypoint: The NFA to be freed.
*/
void	dfa_free(t_ds *entrypoint);

/*
**	dfa_get_size - Gets the number of states of an DFA.
**	@st: The entrypoint of the NFA.
**	Return: The size of the NFA.
**
**	dfa_get_addresses has to be called after dfa_get_size.
*/
size_t	dfa_get_size(t_ds *st);

/*
**	dfa_get_addresses - Fill a vector with all state addresses of a DFA.
**	@st: The entrypoint of the DFA.
**	@vec: The vector to be filled with addresses.
**
**	Has to be called after a dfa_get_size call.
*/
void	dfa_get_addresses(t_ds *st, t_vec *v);

/*
**	dfa_link_add - Links two DFA states.
**	@src: The "from" state.
**	@dst: The "to" state.
**	@p: The pattern to go from src to dst.
**	Return: 0 if successful, -1 on error.
*/
int		dfa_link_add(t_ds *dst, t_ds *src, t_pattern *p);

t_set	*set_new(void);
int		set_push(t_ns *state, t_set *set);
void	set_free(t_set *set);
int		is_state_in_set(t_ns *state, t_set *set);
int		set_cmp(t_set *a, t_set *b);
int		set_contains_final_state(t_set *set);
int		e_closure(t_ns *state, t_set *dst);
int		e_move_closure(t_set *src, t_pattern *p, t_set *dst);

t_map	*map_new(t_ds *state, t_set *set);
void	map_push(t_map *dst, t_map *src);
void	map_free(t_map *map);
t_ds	*state_in_map(t_map *map, t_set *set);

/* ************************************************************************** */
/*	Pattern related functions                                                 */
/* ************************************************************************** */

int			pattern_add_char(t_pattern *p, int c);
int			pattern_add_range(t_pattern *p, int s, int e);
int			pattern_add_pattern(t_pattern *dest, char *src);
int			pattern_parse(t_pattern *p, const char **ptr);
int			pattern_escape(t_pattern *p, const char **ptr);
void		pattern_epsilon(t_pattern *p);
int			is_epsilon(t_pattern p);
int			pattern_match(t_pattern p, int c);
int			pattern_copy(t_pattern dst, t_pattern src);
int			pattern_cmp(t_pattern a, t_pattern b);
int			alphabet_add_pattern(t_alphabet **head, t_pattern pattern);
void		alphabet_free(t_alphabet *a);

/* ************************************************************************** */
/*	Debug functions                                                           */
/* ************************************************************************** */

void		pattern_print(t_pattern pattern);
void		nfa_print(t_ns *nfa);
void		dfa_print(t_ds *entrypoint);

#endif
