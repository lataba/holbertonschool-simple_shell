# C - Simple Shell in C

<img src="https://d2uusema5elisf.cloudfront.net/courses/30-days-of-webdev/day-04/public/assets/pistachio.png" alt="shell_pistacho" width="90%" height="90%">

## What is a SHELL? :shell:

A shell is a program that provides a command-line interface for interacting with an operating system. It acts as a command interpreter between the user and the system kernel. A shell reads input from the user, interprets it, and executes the requested commands or programs.
In other words, a shell is a user interface that allows users to interact with the operating system using a command-line interface. The shell provides a prompt, where users can enter commands and run various tasks such as navigating the file system, managing processes, and executing programs.

## What is this simple shell implementation? :question::grey_question:

This is a simple shell implementation in C that can work in both interactive and non-interactive mode. The shell can run commands and support basic shell functionalities.

<img src="https://github.com/lataba/holbertonschool-simple_shell/blob/41d998864024a2684f2186605ca5d085f1d8ceaf/SHELL.jpeg" alt="shell" width="70%" height="75%">

## How does this Shell work? 
This is a flowchart that contains the working flow of the code of this simple shell.

## File Structure :file_folder: 
This table provides a detailed description of the files used for this shell implementation. In these files are the functions that constitute the program.

| File | Prototypes | Description |
| --- | --- | --- |
| <pre>[shell.h](https://github.com/lataba/holbertonschool-simple_shell/blob/9d1d850bb9c2a9f0fe40057e5fee6954465fc387/shell.h)</pre> | <pre>Header of the project</pre> | <pre>Header file containing definitions and prototypes<br>for all types and functions written for the project.</pre> |
| <pre>[simple_shell.c](https://github.com/lataba/holbertonschool-simple_shell/blob/9d1d850bb9c2a9f0fe40057e5fee6954465fc387/simple_shell.c)</pre> | <pre>Main function of the project</pre> | <pre>Main recieve input from the Command Line Interface,<br>parse and execute it in a while loop.</pre> |
| <pre>[path_and_env_functions.c](https://github.com/lataba/holbertonschool-simple_shell/blob/9d1d850bb9c2a9f0fe40057e5fee6954465fc387/path_and_env_fuctions.c)</pre> | <pre>char \*store_tokens(char \*line)<br>int str_count(char \*str)<br>char \*get_env(char \*var_name)<br>int path_match(char \*\*array_tok)<br>char \*fullpath_func(char \*array_tok, char \*path_value)</pre> | <pre>Function that separates the user command line<br>Function that counts the number of words in a string<br>Function that gets the value of enviroment variable<br>Searchs for the command in the path<br>Function that concatenates the fullpath</pre> |
| <pre>[execute_functions.c](https://github.com/lataba/holbertonschool-simple_shell/blob/9d1d850bb9c2a9f0fe40057e5fee6954465fc387/execute_functions.c)</pre> | <pre>int fork_child(char \*\*array_tok)<br>void free_arr(char \*\*array)</pre>| <pre>Function that creats a child process<br>Frees an array of char pointers</pre> |
| <pre>[builtin_functions.c](https://github.com/lataba/holbertonschool-simple_shell/blob/9d1d850bb9c2a9f0fe40057e5fee6954465fc387/buil_functions.c)</pre> | <pre>int shell_exit(void)<br>int shell_env(void)<br>int builtin_execute(char \*\*tokens)<br>int shell_num_builtins(built_s builtin[])</pre> | <pre>Exits the shell<br>Function that prints environment variables<br>Executes the builtin functions<br>Function that checks the num built-ins</pre>|

## Getting Started
### Requirements :heavy_check_mark:
To run this shell, you need to have a C compiler installed on your system. This implementation has been tested on Unix-based system.

## Building the Shell :electric_plug::wrench:

### How to Compile

To use this implementation of a simple shell, follow these steps:

1 - Download and save the files given above, in a single directory or clone this repository in a directory of your computer.

2 - To build the shell, navigate to the directory where you have downloaded the source code and run the following command:

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

This will create an executable file named "hsh" in the same directory.

## Running the Shell :computer:
To start the shell in interactive mode, simply run the hsh command. This will start the shell and you can start typing commands.

```
$ ./hsh
```

And you can run it in non-interactive mode:

```
$ echo "ls -la" | ./hsh
```

## Functionalities
The shell is capable of executing commands, searching paths in the system, and managing processes. Some of the available commands are:

* env: Displays environment variables.
* exit: Exits the shell.
* echo: Displays a message on the standard output.
* pwd: Prints the working directory.

## Limitations
This is a simple shell implementation and it has some limitations compared to a full, advanced shell, so there may be some tasks that cannot be performed.

To mention some limitations:
This shell does not support background processes.
This shell does not handle all possible error conditions.
This shell implementation does not support running pipes or standard input/output redirection.

### By [Laura Ballesté](https://github.com/lataba) and [Nicolás Fernández](https://github.com/Nicoou) as part of the [Holberton Uruguay](https://holbertonschool.uy/) study program.
