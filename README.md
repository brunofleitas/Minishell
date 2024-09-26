# Minishell

This project, developed at 42 School, involves creating a minimalist command-line interpreter based on Bash, known as Minishell. The goal is to replicate essential functionalities found in Bash and other Unix shells, such as executing commands, handling redirections, managing environment variables, and more.

In the mandatory part, we focused on implementing the core functionalities of a basic Unix shell:

Command Execution: Minishell can execute external commands, much like Bash. The shell searches for commands in the directories listed in the PATH environment variable and runs them in child processes.

Built-in Commands: We implemented several built-in commands such as cd, echo, pwd, export, unset, env, and exit. These commands are handled directly within the shell, without needing external binaries.

Environment Variable Expansion: Minishell supports environment variable expansion, allowing users to use variables such as $HOME and $USER in commands. These are dynamically expanded at runtime.

Redirections: Minishell handles input/output redirection. It supports basic redirections like >, <, and >>, allowing users to redirect output to files, input from files, and append to files, respectively.

Signals Handling: Basic signal management is in place, where the shell correctly handles signals like Ctrl+C (which stops the current command but doesn’t exit the shell) and Ctrl+D (which simulates the exit command).

Command Parsing: The shell parses and processes simple commands, handling arguments and passing them to the appropriate functions or binaries for execution.

These essential features form the core of a basic shell and provide users with a minimal, yet functional, command-line environment to interact with the system.

With the bonus, we extended the basic functionalities of Minishell to include more advanced features, similar to those found in full-fledged Unix shells. These features include:

Command Pipelines: Minishell can handle pipelines (|) that pass the output of one command as the input to another, enabling complex chains of command execution.

Wildcards Expansion: We implemented wildcard expansion (e.g., *.c) that allows users to run commands on multiple files by matching patterns, just like in Bash.

These features extend the basic functionality of a minimal shell, bringing it closer to a fully functional shell environment.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Implemented Functionalities](#implemented-functionalities)

## Installation

### Prerequisites

- **GNU Make**
- **GCC** or any compatible C compiler
- **GNU Readline** (optional, for enhanced interactive input experience)

### Installation Steps

1. Clone the repository to your local machine:
    ```bash
    git clone https://github.com/brunofleitas/Minishell.git
    ```

2. Navigate to the project directory:
    ```bash
    cd minishell
    ```

3. Compile the project:
    ```bash
    make
    ```

4. Run the minishell:
    ```bash
    ./minishell
    ```

## Usage

Minishell can be used like any other Unix shell. Simply type your commands after the prompt and press enter to execute them.

### Example:

```bash
$ ls -l
total 64
-rwxr-xr-x 1 user user 18305 Sep 26 10:23 minishell
