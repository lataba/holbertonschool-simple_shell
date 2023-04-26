### C - Simple Shell Proyect

![simple shell](https://d2uusema5elisf.cloudfront.net/courses/30-days-of-webdev/day-04/public/assets/pistachio.png)

## Learning Objectives :page_with_curl: :heavy_check_mark:


## File Structure :wrench:
This table give a description of the files used for the simple shell.

| File | Prototypes | Description |
| --- | --- | --- |
| <pre>[shell.h]()</pre> | <pre>Header of the project</pre> | <pre>Header file containing definitions and prototypes<br>for all types and functions written for the project.</pre> |
| <pre>[simple_shell.c]()</pre> | <pre>Main function of the project</pre> | <pre>Main recieve input from the Command Line Interface,<br>parse and execute it in a while loop.</pre> |
| <pre>[path_and_env.c]()</pre> | <pre>Functions prototypes</pre> | <pre>Description</pre> |
| <pre>[execute_functions.c]()</pre> | <pre>Functions prototypes</pre> | <pre>Description</pre> |

## How to Compile :electric_plug:
To use this implementation of a simple shell, follow these steps:

1 - Download and save the files given above, in a single directory or clone this repository.

2 - Compile the code, using:
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## How to use it

You can run the shell in interactive mode:

```
$ ./hsh
```

And you can run it in non-interactive mode:

```
$ echo "ls -la" | ./hsh
```
## Flowchart
![flow_img]()

# By [Laura Ballesté](https://github.com/lataba) and [Nicolás Fernández](https://github.com/Nicoou) as part of the [Holberton Uruguay](https://holbertonschool.uy/) study program.
