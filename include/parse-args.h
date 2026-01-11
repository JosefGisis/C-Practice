#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

int get_opt_arg(int argc, char *argv[], char * key, char * value);

int get_pos_arg(int argc, char *argv[], char * pattern, char ** results);

#endif
