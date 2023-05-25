#ifndef _SHELL_H_
#define _SHELL_H_
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **environ;
/* Global program name */
char *name;
/* Global history counter */
int hist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;
char **al_rep(char **arr);
void shw_al(alias_t *list);
void prep_al(char *av, char *vl);
int alias_sh(char **arr, char __attribute__((__unused__)) **ace);

int (*built_main(char *command))(char **args, char **front);
int cd_sh(char **arr, char __attribute__((__unused__)) **ace);
int help_sh(char **arr, char __attribute__((__unused__)) **ace);
int exit_sh(char **arr, char **ace);
int env_sh(char **arr, char __attribute__((__unused__)) **ace);
int unsetenv_sh(char **arr, char __attribute__((__unused__)) **ace);

void clear_pth(void);
char **env_brn(const char *var);
char **pth_cp(void);

char *pth_err(char **arr);
char *exit_err(char **arr);
char *main_err(char **arr);
char *cd_err(char **strs);
char *type_err(char **arr);
char *unq_err(char **mss);
char *unq2_err(char **dsa);

int dig_ct(int dig);
int mk_err(char **conts, int trash);
char *_itoa(int num);


void *_realloc(void *pt, unsigned int pre_sp, unsigned int post_cp);
void buf_hand(char **pt, size_t *n, char *space, size_t b);

ssize_t _getline(char **llp, size_t *n, FILE *inr);
void del_s(char **s_ts, char **in);
char *ret_env(char *st, int l);
char *get_pid(void);

void c_cng(char **ar_r, int *inl);
void rework(char *lnt, ssize_t *wl);
void p_input(char **ms, ssize_t see);
ssize_t new_sz(char *writ_e);
int exec_p(char **arr, char **face, int *tr);
char *new_inp(char *ll, int *et);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

#endif /* _SHELL_H_ */
