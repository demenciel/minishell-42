# Minishell-42

## Overview

Minishell-42 is a minimalistic shell implementation, designed as part of the 42 school curriculum. It aims to replicate some of the functionalities of a Unix shell, providing a lightweight environment for command execution.

## Features

- **Command Parsing**: The shell includes a robust command parsing mechanism, allowing for the interpretation of various shell commands and their arguments.
- **Built-in Commands**: Minishell-42 offers a set of built-in commands, providing essential functionalities without relying on external binaries.
- **Executable Handling**: The project includes mechanisms for executing external programs, allowing users to run various applications directly from the shell.

## Structure

The project is organized into several key components:

- **Main**: The entry point of the application, responsible for initializing the shell and handling user input.
- **Parsing**: This component is responsible for interpreting user commands and translating them into a format that can be executed by the shell.
- **Execution**: This part of the project includes both built-in command handling and external executable management.

## Building and Running

You can build the project using the provided Makefile:

```bash
make
```

After building, you can run the shell by executing the compiled binary.

## Contributing

Please refer to the project's guidelines and the codebase to understand how to contribute to Minishell-42.