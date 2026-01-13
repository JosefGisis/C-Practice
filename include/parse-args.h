#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

#define EOA (-1)
#define ERROR 1
#define SUCCESS 0
#define MAX_ARG_KEY_LENGTH 256
#define MAX_ARG_VAL_LENGTH 1000
#define max(a, b) (a < b ? b : a)
#define min(a, b) (a < b ? a : b)
#define MAX_ARGS_LENGTH 100
#define TRUE 1
#define FALSE 0

int get_opt_arg(int argc, char *argv[], char * key, char * value);
void reset_opt_arg_parser(void);

int get_pos_arg(int argc, char *argv[],  char * value);
void reset_pos_arg_parser(void);

int get_all_pos_args(int argc, char *argv[], const char * pattern, char * value[]);

#endif
