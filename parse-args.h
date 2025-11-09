#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

int get_opt_args(int argc, char *argv[], char * key, char * value);

int get_pos_args(int argc, char *argv[], char * pattern, char ** results);

#endif
