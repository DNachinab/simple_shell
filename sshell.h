#ifndef _SSHELL_H_
#define _SSHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* read and write of buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* command chain */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - single linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - pseudo-arguments to pass into a function,
 *for uniform prototype function pointer structure
 *@arg: string from getline containing argument
 *@argv: an array of pointers to array of char
 *@path: a string path
 *@argc: argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: line of input of count
 *@fname: the filename
 *@env: linked list of environ
 *@environ: modified environ copy
 *@history: history node
 *@alias: alias node
 *@env_changed: changed environ
 *@status: status of the last command executed
 *@cmd_buf: address of pointer to cmd_buf
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: read line input of fd
 *@histcount: line of history count
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - has the builtin string
 *@type: builtin command flag
 *@func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
int _iscmd(info_t *, char *);
char *reprint_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
void in_str(char *);
int in_char(char);
int put_fd(char c, int fd);
int putfd_str(char *str, int fd);
int len_str(char *);
int comp_str(char *, char *);
char *start_hay(const char *, const char *);
char *concat_str(char *, char *);
char *_copystr(char *, char *);
char *_dupstr(const char *);
void _inputstr(char *);
int _putchar(char);
char *_cpystrn(char *, char *, int);
char *_catstr(char *, char *, int);
char *_locchar(char *, char);
char **splitstr(char *, char *);
char **splitstr2(char *, char);
char *_locmem(char *, char, unsigned int);
void _ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int _free(void **);
int interact(info_t *);
int _delim(char, char *);
int _alpha(int);
int _atoi(char *);
int err_atoi(char *);
void _printerror(info_t *, char *);
int _printd(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int my_exit(info_t *);
int my_ch(info_t *);
int my_help(info_t *);
int my_history(info_t *);
int my_alias(info_t *);
ssize_t _getinput(info_t *);
int _getline(info_t *, char **, size_t *);
void signal_handler(int);
void _clearinfo(info_t *);
void _setinfo(info_t *, char **);
void _freeinfo(info_t *, int);
char *get_env(info_t *, const char *);
int my_env(info_t *);
int myset_env(info_t *);
int myunset_env(info_t *);
int populate_env_list(info_t *);
char **get_environ(info_t *);
int unset_env(info_t *, char *);
int set_env(info_t *, char *, char *);
char *get_history_file(info_t *info);
int _writehist(info_t *info);
int _readhist(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int _renumhistory(info_t *info);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
size_t length_l(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_start_hay(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
int is_chain(info_t *, char *, size_t *);
void ch_chain(info_t *, char *, size_t *, size_t, size_t);
int rep_alias(info_t *);
int rep_vars(info_t *);
int rep_str(char **, char *);

#endif