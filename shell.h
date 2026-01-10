#ifndef MYHEADER_H
#define MYHEADER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <linux/limits.h>

extern char **environ;

char *_getenv(const char *name);
void print_env();
void get_path_loop(char *name, char *paths, char *full);
char *get_path(char *name);
void l_free(char **list_words);
int string_to_list(char *string, char **list);
int prompt_init(char *buffer, char **list_words);
int exec_prompt(char *shell_name, char *buffer, char **list_words);
int prompt(const char *shell_name);

#endif
