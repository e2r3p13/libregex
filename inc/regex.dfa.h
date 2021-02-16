/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.dfa.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:41:09 by lfalkau           #+#    #+#             */
/*   Updated: 2021/02/16 16:44:50 by glafond-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGEX_DFA_H
# define REGEX_DFA_H

# include <regex.nfa.h>
# include <libft.h>

# define SET_DFL_SIZE 8

typedef struct s_link_lst	t_link_lst;
typedef struct s_dfa_state	t_ds;
typedef struct s_set		t_set;
typedef struct s_map		t_map;

struct s_link_lst
{
	t_link		link;
	t_link_lst	*next;
};

/*
**	t_ns represents a state of an automaton.
**	It keeps two links which can lead to its two children (at most).
**	t_ns nodes are used to construct our nfa / dfa.
*/
struct s_dfa_state
{
	t_bool		is_final;
	t_link_lst	*links;
	uint8_t		flag : 1;
};

struct s_set
{
	t_ns	**addr;
	size_t	size;
	size_t	capacity;
};

struct s_map
{
	t_ds	*state;
	t_set	*set;
	t_map	*next;
};

t_ds		*dfa_state_new(void);
int			dfa_create_connection(t_ds *f, t_pattern *p, t_ds *l);
t_set		*set_new(void);
int			set_push(t_ns *state, t_set *set);
t_bool		is_state_in_set(t_ns *state, t_set *set);
void		set_free(t_set *set);
t_bool		set_cmp(t_set *a, t_set *b);
t_ds		*state_in_map(t_map *map, t_set *set);
void		dfa_links_free(t_link_lst *links);
t_map		*map_new(t_ds *state, t_set *set);
void		map_push(t_map *dst, t_map *src);
void		dfa_state_free(t_ds *state);
void		map_free(t_map *map);
void		map_print(t_map *map);
void		set_print(t_set *set);
t_bool		set_contains_final_state(t_set *set);
void		dfa_free(t_ds *dfa);
t_ds		*dfa_generate(const char *str);
int			dfa_build(t_map *st_map, t_map *hole_map, t_alphabet *a);
int			e_closure(t_ns *state, t_set *dst);
int			e_move_closure(t_set *src, t_pattern *p, t_set *dst);

void		dfa_print(t_ds *entrypoint);

#endif
