# C - Simple shell

A shell is a Commanand Language Interpreter, an interface between the kernel and the user. It allows the user to execute programs (called commands) and read the computer's answers.

This project is a simple partial recreation of the Linux shell. This project was made with a limited list of functions ans syscalls as per the re Holberton School.

## File Descriptions

* **AUTHORS** : List of contributors to the project
* **man_1_simple_shell** : The manual for the simple shell
* **shell.h** : the project's header file

## Requirements
### General
 - Allowed editors: `vi`, `vim`, `emacs`
 - All your files will be compiled on Ubuntu 20.04 LTS using `gcc`, using the options `-Wall -Werror -Wextra -pedantic -std=gnu89`
 - All your files should end with a new line
 - A `README.md` file, at the root of the folder of the project is mandatory
 - Your code should use the Betty style. It will be checked using `betty-style.pl` and `betty-doc.pl`
 - Your shell should not have any memory leaks
 - No more than 5 functions per file
 - All your header files should be include guarded

## More Info
### Output
 - Unless specified otherwise, your program **must have the exact same output** as `sh` (`/bin/sh`) as well as the exact same error output.
 - The only difference is when you print an error, the name of the program must be equivalent to your `argv[0]`

Example of error with sh:

```
julien@ubuntu:/# echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
julien@ubuntu:/# echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
```

Same error with your program hsh:

```
julien@ubuntu:/# echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
julien@ubuntu:/# echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
```
### Compilation
Your shell will be compiled this way:

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

### Testing
Your shell should work like this in interactive mode:

```
julien@ubuntu:/# ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
julien@ubuntu:/#
```
But also in non-interactive mode:

```
julien@ubuntu:/# echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
julien@ubuntu:/# cat test_ls_2
/bin/ls
/bin/ls
julien@ubuntu:/# cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
julien@ubuntu:/#
```

### Checks
The Checker will be released at the end of the project (1-2 days before the deadline). We **strongly** encourage the entire class to work together to create a suite of checks covering both regular tests and edge cases for each task. See task `8. Test suite`.

After the deadline, you will need to fork the repository if it’s not on your Github account to be able to be corrected by the checker.

## Tasks
### Mandatory
0. [x] README, man, AUTHORS
1. [x] Betty would be proud
2. [x] Simple shell 0.1
3. [x] Simple shell 0.2
4. [ ] Simple shell 0.3
5. [ ] Simple shell 0.4
6. [x] Simple shell 1.0
### Advanced
7. [ ] What happens when you type `ls -l \*.c` in the shell
8. [ ] Test suite
9. [ ] Simple shell 0.1.1
10. [ ] Simple shell 0.2.1
11. [ ] Simple shell 0.4.1
12. [ ] Simple shell 0.4.2
13. [ ] setenv, unsetenv
14. [ ] cd
15. [ ] ;
16. [ ] && and ||
17. [ ] alias
18. [ ] Variables
19. [ ] Comments
20. [ ] help
21. [ ] history
22. [ ] File as input

## Author
Emilien Marot - <12394@holbertonstudents.com>
