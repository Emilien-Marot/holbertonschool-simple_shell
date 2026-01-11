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

#define BUF_SIZE 1024

extern char **environ;

char *_getenv(const char *name);
void print_env(void);
char *get_path(char *name);
void l_free(char **list_words);
int string_to_list(char *string, char **list);
int prompt(const char *shell_name);
int main(int ac __attribute__((unused)), char **av);

#endif
