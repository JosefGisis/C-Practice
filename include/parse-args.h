#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

#define EOA 0
#define ERROR (-1)
#define SUCCESS 1
#define MAX_ARG_KEY_LENGTH 256
#define MAX_ARG_VAL_LENGTH 1000
#define max(a, b) (a < b ? b : a)
#define min(a, b) (a < b ? a : b)
#define MAX_ARGS_LENGTH 100
#define TRUE 1
#define FALSE 0

int get_opt_arg(int argc, char *argv[], char * key, char * value);
void reset_opt_arg_parser(void);

int get_pos_arg(int argc, char *argv[], char * pattern, char ** results);

#endif
