/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeorge <tgeorge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:52:58 by tgeorge           #+#    #+#             */
/*   Updated: 2023/10/20 15:52:59 by tgeorge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_garbage
{
	char				*str;
	char				**tab_str;
	int					*tab;
	int					**big_tab;
	struct s_garbage	*next;
}						t_garbage;

typedef struct s_redir
{
	char				*filename;
	int					redir_type;
	struct s_redir		*next;
}						t_redir;

typedef struct s_expand
{
	char				*result;
	int					**tab_dollar;
	char				**splitted;
	int					*space_expand;
	char				*new_str;
	int					*tab_doll;
	char				*value;
}						t_expand;

typedef struct s_block
{
	struct s_expand		*expand;
	struct s_expand		*exp_redir;
	char				*block_line;
	char				**cmd_block;
	struct s_list		*cmd_list;
	struct s_list		*cmd_expand;
	struct s_redir		*redir_list;
	char				**cmd_args;
	int					launch_exec;
	int					fd_input;
	int					fd_output;
	int					fd_here;
	int					cmd_number;
	int					fail_malloc;
	struct s_context	*context;
	struct s_block		*next;
}						t_block;

typedef struct s_elist
{
	char				**content;
	struct s_elist		*next;
}						t_elist;

typedef struct s_context
{
	struct s_block		*block;
	struct s_list		*path_list;
	struct s_elist		*env;
	struct s_elist		*hide_env;
	struct s_garbage	*garbage;
	char				**env_tab;
	char				**my_path;
	int					fd_temp;
	char				*input_line;
	char				*clean_line;
	char				**tab_block;
	char				**mycmdargs;
	int					nb_command;
	int					pipe_cmd[2];
	int					heredoc_pipe[2];
	int					heredoc_nb;
	int					exit_code;
	int					is_created;
	pid_t				*tab_pid;
}						t_context;

//Exec
void					launch_exec(t_context *context);
//Single_command
void					single_parent_process(t_context *context);
void					single_child_process(t_context *context,
							t_block *block);
int						single_command(t_context *context);
int						get_single_exit(t_context *context, int status);
void					single_child_process(t_context *context,
							t_block *block);
void					no_single_args(t_context *context, t_block *block);
void					abs_single_path(t_context *context, t_block *block);
void					ft_close_single(int fd_in, int fd_out);
//Multiple_command
void					multiple_command(t_context *context);
void					multiple_parent_process(t_context *context,
							t_block *block, pid_t *parent);
void					multiple_child_process(t_context *context,
							t_block *block);
void					redirect(t_context *context, t_block *block);
void					ft_close_multiple(int f1, int f2, int fd_in,
							int fd_out);
void					end_multiple(t_context *context, int *status);
void					get_multiple_exit(t_context *context, int *status);
void					init_multiple_command(t_context *context);
void					abs_mult_path(t_context *context, t_block *block);
void					no_mult_args(t_context *context, t_block *block);
void					init_tab_pid(t_context *context);

//Builtins
int						is_builtin(t_context *context, t_block *block);
void					ft_echo(t_context *context, t_block *block);
int						ft_cd(t_context *context, t_block *block);
int						ft_pwd(t_context *context);
void					ft_export(t_context *context, t_block *block);
void					ft_unset(t_context *context, t_block *block);
void					ft_env(t_context *context, t_block *block);
void					exit_process(t_context *context, t_block *block);
void					init(t_context *context, char **envp);
void					ft_init_loop(t_context *context);

void					ft_free_tab(char **tab);
void					ft_free_all(t_context *context);
void					ft_free_loop(t_context *context);
void					ft_free_list(t_list *list);
void					ft_free_elist(t_elist *list);
void					ft_free_elist_content(t_elist *list);
void					ft_free_list_content(t_list *list);
void					ft_free_redirlist(t_redir *list);
void					ft_free_redirlist_content(t_redir *list);
void					ft_free_fail_expand(t_context *context);

void					suppr_heredocs(t_context *context);

void					ft_lstadd_backblock(t_block **lst, t_block *new);
t_block					*ft_lstnewblock(t_context *context, void *content);
int						ft_lstsizeblock(t_block *lst);
t_block					*ft_lstlastblock(t_block *lst);

//decoupage + parsing :
// int					decoupage(t_context *context);
// void				traitement(t_context *context);
// void				decoupage_block(t_context *context, t_block *block, int nb);
// void				create_args(t_context *context);
// int					repere_type(t_context *context, t_block *block, int i);

// new parsing
int						init_values_parsing(int *i, int *j, int *quote,
							int *redir_type);
void					cmd_or_redir(t_block *block, int *i, int *j,
							int *redir_type);
void					char_is_a_chevron(t_block *block, int *i, int *j,
							int *redir_type);
int						word_is_created(t_block *block, int *i, int *j,
							int *redir_type);
int						separe_args_redir(t_context *context);
void					if_is_quoted(char c, int *single, int *double_q);
int						is_quoted(char c, int reset);
void					create_args(t_context *context);
void					decoupage_utils(t_context *context, int *i);
int						decoupage(t_context *context);
void					ft_addback_redir(t_block *block, int i, int k,
							int redir_type);
void					ft_addback_cmd(t_context *context, t_block *block,
							int i, int k);
int						is_redir(char c, char d);
void					ft_nb_command(t_context *context);
int						mf(t_context *context, t_block *block, int *i, int *j);
int						end_parsing(t_context *context);
int						ced(t_context *context);
int						end_d(t_context *context);

// void				move_forward_in_block_line(t_context *context,
// 						t_block *block, int *i, int *j);

//gestion des espaces (terrifiant)
int						count_spaces(char *str);
char					*gestion_des_espaces(char *str);

//gestion des erreurs
int						check_error(char *str);
int						check_closed_quotes(char *str);
void					check_char_if_is_quote(char c, int *single,
							int *double_q);
int						check_closed_quotes(char *str);
int						is_3_left_chevron(char *str, int i);
int						is_3_right_chevron(char *str, int i);
int						is_2_different_chevrons(char *str, int i);
int						is_2_different_chevrons_bis(char *str, int i);
void					utils_quoted(char c, int *i);
int						is_spaces_between_left_chevrons(char *str, int i);
int						is_spaces_between_right_chevrons(char *str, int i);

// split quote
char					**ft_split_quote(char const *s, char c);

//env
char					**split_key_value(t_context *context, char *str);
void					affiche_env(t_context *context);
void					ft_envlist_to_tab(t_context *context);
void					get_path(t_context *context);
char					*strcpy_whithout_quote(char *src, char *dest);
void					init_hide_env(t_context *context);
void					print_hide_env(t_context *context);
int						ft_strcmp(char *s1, char *s2);
void					ft_modify_value_export_hide_env(t_context *context,
							char *new_kv);
int						ft_strcmp(char *s1, char *s2);
char					*ft_strcpy(char *dest, char *src);
char					**ft_strdup_tab(t_context *context, char **s);
void					tout_pour_la_norm(t_context *context, t_elist *copy);

//export
int						is_in_env(t_context *context, char *new_kv);
int						is_in_hide_env(t_context *context, char *new_kv);
void					strcpy_after_equal(t_context *context,
							char *new_kv, t_elist *temp);
void					ft_modify_value_export(t_context *context,
							char *new_kv);
void					insert_hide_key(t_context *context, char *str);
char					*ft_strcpy(char *dest, char *src);
void					if_export(t_context *context, char *new_kv);

// listes pour env
t_elist					*ft_elstnew(t_context *context, char **content);
int						ft_elstsize(t_elist *lst);
t_elist					*ft_elstlast(t_elist *lst);
void					ft_elstadd_back(t_elist **lst, t_elist *new);
void					ft_elstadd_front(t_elist **lst, t_elist *new);

t_redir					*ft_lstnewredir(t_context *context,
							char *content, int redir_type);
int						ft_lstsizeredir(t_redir *redir);
t_redir					*ft_lstlastredir(t_redir *lst);
void					ft_lstadd_backredir(t_redir **lst, t_redir *new);

int						ft_lstsizegarbage(t_garbage *garbage);
t_garbage				*ft_lstlastgarbage(t_garbage *lst);
void					ft_lstadd_backgarbage(t_garbage **lst, t_garbage *new);
t_garbage				*ft_glstnewbigtab(t_context *context, int **content);
t_garbage				*ft_glstnewtab(t_context *context, int *content);
t_garbage				*ft_glstnewtabchar(t_context *context, char **content);
t_garbage				*ft_glstnewchar(t_context *context, char *content);
void					ft_free_garbage(t_context *context, int fmal);

int						ft_open_single_redir(t_context *context,
							t_block *block);
void					ft_open_multiple_redir(t_context *context,
							t_block *block);
void					ft_close_here(t_context *context, t_block *block);
int						ft_open_heredocs(t_context *context);
int						ft_wr_heredoc(t_context *context, t_block *block,
							t_redir *redir);
void					heredoc_num(t_context *context, t_redir *redir);
void					init_heredoc(t_context *context, pid_t *parent);

void					signal_cmd(int sig);
void					signal_cmd_child(int sig);
// expand
int						expand(t_context *context);
void					insert_list(t_context *context, t_block *block,
							t_list *cmd, char *value);
void					expand_in_cmd(t_context *context, t_block *block);
void					expand_in_redir(t_context *context, t_block *block);
void					insert_redir_list(t_block *block, t_redir *redir,
							char *value);
void					boucle_redir(t_redir *temp, t_redir *redir,
							t_block *block);
void					free_in_insert_redir(t_redir *redir);
void					expand_total(t_context *context, t_block *block,
							char *str);
void					expand_total_redir(t_context *context, t_block *block,
							char *str);
int						is_ambiguous(t_redir *redir, char **splitted,
							t_block *block);
int						is_next_ambiguous(t_redir *redir, char **splitted,
							t_block *block);

void					ft_affiche_block_content(t_context *context);
char					*get_value(t_context *context, char *str, int size);
void					split_expand_redir(t_block *block, int tot_spaces,
							int max_spaces);

void					insert_redir_list(t_block *block, t_redir *redir,
							char *value);
void					boucle_redir(t_redir *temp, t_redir *redir,
							t_block *block);
void					free_in_insert_redir(t_redir *redir);
void					expand_total(t_context *context, t_block *block,
							char *str);
void					expand_total_redir(t_context *context, t_block *block,
							char *str);
// int			is_ambiguous(t_redir *redir, char **splitted,t_block *block);
int						a(t_redir *redir, char **splitted, t_block *block);
int						is_next_ambiguous(t_redir *redir, char **splitted,
							t_block *block);

//expand utils
int						value_existe(t_context *context, char *str, int i,
							int j);
int						count_dollar(char *str);
int						nb_quotes(char *str);
int						value_size(t_context *context, char *str, int i, int j);
int						nb_char_interr(t_context *context);
int						compte_taille_redir(t_context *context, t_block *block,
							char *str);
int						compte_taille(t_context *context, t_block *block,
							char *str);
char					*replace_value(t_context *context, t_block *block,
							char *str, char *result);
t_redir					*insert_first_redir(t_redir *redir, t_block *block,
							int *i, int *j);
t_redir					*insert_redir(t_redir *redir, t_block *block, int *i,
							int *j);
void					insert_command(t_block *block, char **splitted, int *i,
							int *j);
int						*is_expendable(t_context *context, t_block *block,
							char *str, int nb_dollar);
int						calcul_len(t_context *context, int *tab_dollar,
							char *str);
char					*enleve_quotes(t_block *block, char *str);
char					*enleve_quotes_redir(t_block *block, char *str);
char					*enleve_dollar_redir(t_context *context, t_block *block,
							int taille);
char					*enleve_dollar(t_context *context, t_block *block,
							int taille);
void					free_valid_expand(t_expand *expand);
int						init_exp(int *i, int *j, int *quote);
void					expand_or_not(t_block *block, int nb_dollar, int **i);
char					*enleve_dollar(t_context *context, t_block *block,
							int taille);
void					expredir_or_not_end(t_block *block, int nb_dollar,
							int **i);
void					expredir_or_not_suite(t_block *block, int nb_dollar,
							int **i);
void					expredir_or_not(t_block *block, int nb_dollar, int **i);
int						util_eq(t_block *block, char **res, char *str);
char					*enleve_quotes(t_block *block, char *str);
int						init_enleve_dollar(t_block *block, char **res, int **i,
							int taille);
void					expand_or_not_end(t_block *block, int nb_dollar,
							int **i);
void					expand_or_not_suite(t_block *block, int nb_dollar,
							int **i);
int						v(t_context *context, char *str, int i, int j);
int						util_is_expendable(t_block *block, int **td,
							int *nb_dollar);
int						init_exp(int *i, int *j, int *quote);
int						*is_expendable(t_context *context, t_block *block,
							char *str, int nb_dollar);
int						calcul_len(t_context *context, int *tab_dollar,
							char *str);
void					is_interr(char *str, int *i);
int						*size_key_redir(t_block *block, char *str,
							int nb_dollar);
int						util_size_key_redir(t_block *block, int nb_dollar);
int						*size_key(t_block *block, char *str, int nb_dollar);
int						nooorm(char *str, int *i);
int						util_size_key(t_block *block, int nb_dollar);
int						is_separator(char c);

void					ft_affiche_block_content(t_context *context);
char					*get_value(t_context *context, char *str, int size);
void					split_expand(t_block *block, int tot_spaces,
							int max_spaces);
int						value_existe(t_context *context, char *str, int i,
							int j);
int						count_dollar(char *str);
int						nb_quotes(char *str);
int						value_size(t_context *context, char *str, int i, int j);
int						nb_char_interr(t_context *context);
int						compte_taille_redir(t_context *context, t_block *block,
							char *str);
int						compte_taille(t_context *context, t_block *block,
							char *str);
char					*replace_value_redir(t_context *context, t_block *block,
							char *str, char *result);
char					*replace_value(t_context *context, t_block *block,
							char *str, char *result);
t_redir					*insert_first_redir(t_redir *redir, t_block *block,
							int *i, int *j);
t_redir					*insert_redir(t_redir *redir, t_block *block, int *i,
							int *j);
void					insert_command(t_block *block, char **splitted, int *i,
							int *j);
int						*is_expendable(t_context *context, t_block *block,
							char *str, int nb_dollar);
int						calcul_len(t_context *context, int *tab_dollar,
							char *str);
char					*enleve_quotes(t_block *block, char *str);
char					*enleve_dollar_redir(t_context *context, t_block *block,
							int taille);
char					*enleve_dollar(t_context *context, t_block *block,
							int taille);
void					free_valid_expand(t_expand *expand);
int						init_exp(int *i, int *j, int *quote);
int						*fill_space_expand_redir(t_context *context,
							t_block *block, char *str,
							int **tab_dollar);

void					ft_affiche_block_content(t_context *context);
char					*get_value(t_context *context, char *str, int size);
void					split_expand(t_block *block, int tot_spaces,
							int max_spaces);
// void				split_expand(t_block *block, int *space_expand,
// 						int tot_spaces, int max_spaces);
// void				split_expand_redir(t_block *block, int *space_expand,
// 						int tot_spaces, int max_spaces);
int						nb_space(t_context *context, char *str,
							int **tab_dollar);
int						nb_space_split(t_context *context, char *str,
							int **tab_dollar);
int						*fill_space_expand(t_context *context, t_block *block,
							char *str, int **tab_dollar);
int						init_fser(t_block *block, char *str, int **tab_dollar);
void					char_is_space(t_block *block, char *str, int i,
							int *nb_spaces);
int						*fill_space_expand_redir(t_context *context,
							t_block *block, char *str,
							int **tab_dollar);
char					*create_word(t_block *block, char *str, int i, int j);
int						ise(t_block *block, t_expand *expand, int tot_spaces);
int						ise_r(t_block *block, t_expand *expand, int tot_spaces);
int						ft_nbstring_expand(char const *s, char c);
int						little_nb_space(char *str);
int						nb_space(t_context *context, char *str,
							int **tab_dollar);
int						nb_space_split(t_context *context, char *str,
							int **tab_dollar);
int						init_fse(t_block *block, char *str, int **tab_dollar);

// cd et pwd
char					*copy_pwd(t_context *context, char *pwd);
char					*copy_oldpwd(t_context *context, char *pwd);
int						update_pwd(t_context *context, char *pwd);

// utils
int						is_only_digits(char *str);
char					**ft_malloc_double(t_context *context, int i);
char					*ft_malloc(t_context *context, int i);
char					**malloc_empty_value(t_context *context, char **kv,
							char *str);
char					*ft_ministrjoin(t_context *context, char const *s1,
							char const *s2);
char					*ft_ministrdup(t_context *context, const char *s);
char					*ft_minisubstr(t_context *context, char const *s,
							unsigned int start, size_t len);
t_list					*fm(t_context *context, void *content);
char					**ft_minisplit(t_context *context,
							char const *s, char c);
void					reset_signals(t_context *context);

// export utils
int						is_in_env(t_context *context, char *new_kv);
int						is_in_hide_env(t_context *context, char *new_kv);
int						contain_an_equal(char *str);
int						is_valid_name(char *str);

#endif