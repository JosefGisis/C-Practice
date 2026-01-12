### This project is a simple argument parser for C programs.

To compile:
Go to root of project and run
```bash
cmake ./Cmake-build-debug   
```
to run:
```bash
cd ./Cmake-build-debug
./arg-parser --optarg=blank
```

#### TODO
- [] Update README for latest version of get_opt_arg
- [] Update malloc size allocation
- [] Update header file to include all functions and move all symbolic constants into headers file
- [] Create get_pos_arg
- [] Create get_all_pos_args

#### Usage guidelines for optional arguments and flags
- Optional arguments can be preceded by either a single or double dash.
- Optional argument values are provided right after the key and seperated by an equal sign (e.q. --key=value).
- Values for optional arguments are always optional.
- Single dashes are flags and can include multiple flags for a single argument (e.g. -gbr).
- A value cannot be provided where multiple flags are provided in a single argument.
- Optional arguments can include dashes (e.g. --hello-world, ---helloworld), but flags cannot.
- The equal sign indicates the start of an arguments value. Subsequent equal signs within the value will be returned as is.
- Values with whitespaces need to be enclosed with quotation marks, or it will be parsed as a positional argument.

#### Usage guidelines for positional arguments
- Positional arguments can be parsed one at a time or in bulk.
- Getting arguments one at a time is just a simple iteration over all arguments that are not preceded by a dash.
- Bulk positional arguments require providing a syntax like --*-.
- Dashes indicate a required positional argument and an asterisk indicates an open-ended number of arguments.
- The bulk position syntax does not allow for more than one asterisk, as that would create an ambiguous pattern (e.g. -, -*, *-, -*- are fine, but -*-*- would not be).
- You can provide * to indicate that any number of arguments are permissible.