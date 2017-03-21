/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 17:12:33 by mseinic           #+#    #+#             */
/*   Updated: 2017/03/16 17:09:10 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include <unistd.h>
# include "libft.h"
# include <stdbool.h>
# include <limits.h>
# include "error_msg.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>

# define READ_BUFFER(X) (X->buffer)
# define READ_BUFFER_SIZE 6
# define STR_SIZE(X) (X->str.size)
# define STR(X) (char *)(X->str.data)
# define SIZE_PROMPT 3

typedef	struct				s_env_cell
{
	char					*key;
	char					*value;
}							t_env_cell;

typedef struct				s_env
{
	t_array					tab;
}							t_env;

typedef struct				s_line
{
	t_string				str;
	char					*strcpy;
	char					*sauv;
	char					buffer[7];
	size_t					cursor;
	size_t					sauv_cursor;
	int						largeur;
	int						hauteur;
	int						nbline;
}							t_line;

typedef struct				s_history
{
	t_array					tab_h;
	t_string				tmp_cmd;
	size_t					index;
	size_t					first_time;
}							t_history;

typedef struct				s_env_info
{
	bool					flags[256];
}							t_env_info;


int							bi_change_str(t_line *line, t_history *history, size_t new);
size_t						search_history(t_line *l, t_history *history, bool up_or_down);
void						check_index(t_line *l, t_history *history, bool up_or_down);

int							env_init(t_env *env, char **environ);
int							line_init(t_line *line);

void						bi_history_print(t_history *history);
int							bi_history_save(t_history *history, t_string *cmd);
int							bi_history_init(t_history *history);

int							ft_init_term(void);
int							ft_reset_term(void);
void						my_echo(t_env *env, char **cmd);
void						aux(t_env *env, char *buff, int *ex, int *ac);
int							check_set_name(t_env *env);
size_t						find_position(char **env, char *key);
void						print_env(t_env *env, char **cmd);
void						my_cd(t_env *env, char **cmd);
int							bin_execute(char **tab, char **env, char *bin_path);
void						print_array(char **tab);
void						env_preparation(char *str, t_env *env);
void						get_env(t_env *env, char **environ);
int							execute(char **exec_tab, char **env_tab);
void						error(char *str);
void						del_tab(char **env);
size_t						ft_size(char **tab);
void						set_value(t_env *env, char *key, char *value);
void						unset_env_fnct(t_env *env, char *key);
void						init(t_env *env, char **environ);
int							ret_access(char *path, char **bin_path);
void						get_path(t_env *env);

t_env_cell					*find_cell(t_env *env, char *key);
int							env_set(t_env *env, char *key, char *value);
int							bi_cd(t_env *env, char *path);

extern t_env				g_env;
extern t_line				g_line;
extern t_history			g_history;

#endif
