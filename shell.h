#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUFSIZE 600
#define FREE_ADDRESSES ((void *)3)
#define ARRAY_SIZE(ARRAY) (sizeof(ARRAY) / sizeof((ARRAY)[0]))
/**
 * struct buff_t - structure for controlling buff_t
 * @b_s: pointer the buff_t
 * @sz: size of the buff_t
 * @bl_s: current point in buff_t to check for multiple command passes
 */
typedef struct buff_t
{
	char *b_s;
	unsigned int sz;
	unsigned int bl_s;
} buff_t;
/**
 * struct builtin - lookup structure for builtin functions
 * @name: string name user types to call function
 * @func: function pointer to that function
 */
typedef struct builtin
{
	char *name;
	int (*func)();
} builtin;
/**
 * struct list_a - List for saving addresses for freeing on exit
 * @loc: an loc of any type
 * @nxt: the nxt node in the list
 */
typedef struct list_a
{
	void *loc;
	struct list_a *nxt;
} list_a;

/**
 * struct list_h - history linked list for saving commands
 * @cmd: command given as input
 * @next: pointer to next node on list
 */

typedef struct list_h
{
	char *in_p;
	struct list_h *next;
} list_h;

extern char **environ;
/**
 * struct list_e - structure for each environmental variable
 * @value: value of the environmental variable
 * @next: next environmental variable
 */

typedef struct list_e
{
	char *hold;
	struct list_e *next;
} list_e;
/**
 * struct list_al - structure for holding aliases
 * @key: key to search for when matching
 * @value: value to replace matched keys
 * @next: next node in the list
 */
typedef struct list_al
{
	char *unq;
	char *hold_s;
	struct list_al *next;
} list_al;
void print_int(int num);
void _puts(char *str);
int _putchar(char c);

int aliase(buff_t *b, list_e *env_p);

void _realloc(buff_t *str);
void *_malloc(size_t ptr_size);

void rem_str(buff_t *str, int n);
void add_str(buff_t *b, char *str, int position);
void _setfree(void *addr);
void _free(void *address);
void add_node(list_a *list, void *newnode);
void free_list(list_a *list);
int rem_node(list_a *list, void *addr);

int read_file(buff_t *b, list_e *envp);
int get_line(buff_t *b, int fd, list_e *envp);

char *_memcpy(char *dest, char *src, unsigned int n);
char *_memset(char *s, char b, unsigned int n);
char *_strcat(char *dest, char *src);
char *_strncat(char *dest, char *src, int n);
char *_strstr(char *haystack, char *needle);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);

char *_strchr(char *s, char c);
int _strlen(char *s);
int _atoi(char *s);
int matchStrings(const char *string1, const char *string2);
char *duplicate(char *str);

int strictStringMatch(const char *string1, const char *string2);
int findSubstringIndex(const char *text, const char *substring);
int findFirstCharacterIndex(const char *string, const char *characters);
int is_digit(int c);
int is_alpha(int c);

int matchStringsAndDelim(char *string1, char *string2, char *delimiter);
int characterMatch(char c, const char *needles);
int compareStrings(char *string1, char *string2);

void print_error(char *err);

char *_del_nm(list_e *environ, char *tb_rm, int size);
char *_rem_pth(char **arr, list_e *environ, char *pth, int size);
char *_ret_val(list_e *environ, char *key);
char *new_pth(char **pth, char *file, char *character, list_e *environ);
int get_content(list_e *environ, char **vari);

char **arr_init(list_e *environ);

void show_hist(list_h *main);
list_h *new_entry(list_h *first, char *input);
void new_hist(list_h *new, list_e *envp);
int get_content(list_e *environ, char **vari);
void add_to_list(list_h *list, char *input);
int add_to_file(list_e *environ, list_h *list);
void _checker(char *input, list_e *environ, char type);


int help_alias(void);
int help_cd(void);
int help_env(void);
int help_exit(void);
int help_help(void);
int help_hist(void);
int help_setenv(void);
int help_unsetenv(void);
int a_print(list_al *list, char **arr);
int a_operations(list_al *list, char **arr);
int a_complete(list_al *prop);
char *a_find(list_al *prop, char *arr);

char *func_cd(char **new_dir, list_e *environ, int size);
int cd_shell(char **arr, list_e *environ, int size);
int env_shell(char **arr, list_e *environ);
int help_shell(char **arr);
int exit_shell(char **arr, list_e *environ, int size);
int hist_shell(char **arr, list_e *environ, int type);
int setenv_shell(char **arr, list_e *environ, int size);
int unsetenv_shell(char **arr, list_e *environ);
int _a_shell(char **arr, list_e *environ, int type);


char *_itoa(int num, int mode);

list_e *mk_env(void);
void cng_env(list_e *environ, char *type, char *new_char, int size);
void env_del(list_e **main, int num);
void env_shw(list_e *main);
list_e *env_join(list_e **main, char *characters);

int _pth(char *locate, list_e *environ);
int mk_pth(char *input, char **find);
char **break_pth(char **find, char *locate, int size);
int execute2(char **arr, list_e *environ, int size_s);
int exec_part(char **arr, list_e *environ, int input_s);
int main_execute(char *input, char **array, list_e *environ);
void _sig(int s);

void end_inp(char *cont);
int input_finish(char c);
int is_w(char c);

void break_buffer(buff_t *cont, char ***array);
void size_x(char *cont, char ***arr);
char *find_elem(char *array, int index);
char *cur_pid(void);
void _to_buff(buff_t *base, list_e *environ, int rt);
int c_extra(buff_t *space, int rt);
void c_short(buff_t *space);



#endif