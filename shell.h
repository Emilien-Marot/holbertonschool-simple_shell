#ifndef MYHEADER_H
#define MYHEADER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

void l_free(char **list_words);
int string_to_list(char *string, char **list);
int prompt(char **list_words);
int main(int ac __attribute__((unused)), char **av);

#endif
