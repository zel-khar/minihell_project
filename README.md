Minishell - 42 Project
Overview

Minishell is a simplified Unix shell created as a project at 42 school. It replicates basic shell functionalities such as command parsing, execution, environment variable management, redirections, and built-in commands.

Features

Execute simple commands with arguments

Support for built-in commands:

cd

echo

pwd

export

unset

env

exit

Handle environment variables

Support for input/output redirections (>, <, >>)

Support for pipes (|)

Signal handling (e.g., Ctrl+C)

Quoting and escaping rules

Installation

Clone the repository and compile the project:

git clone https://github.com/zel-khar/minihell_project.git minishell
cd minishell
make

Usage

Run the minishell executable:

./minishell


You can then enter commands just like in a normal shell.

Project Structure

src/ - Source code files

includes/ - Header files

Makefile - Compilation rules

README.md - Project documentation

How It Works

Parsing: User input is parsed into commands and tokens, respecting quotes and escapes.

Execution: Built-in commands are executed internally; others use execve to run programs.

Redirection: Input/output redirections are handled via file descriptors.

Pipes: Commands separated by pipes are connected using pipe system calls.

Environment: Maintains a list of environment variables for execution context.

Known Limitations

No support for advanced shell features like job control or scripting

Limited error handling in some edge cases

Does not support all shell built-ins from bash or zsh

Resources

42 School Minishell Subject

POSIX Shell Command Language

Author

zel-khar
