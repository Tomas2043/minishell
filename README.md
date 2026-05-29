_This project has been created as part of the 42 curriculum by darafael, toandrad._

# Minishell

## Description

Minishell is a simple Unix shell implemented in C, developed as part of the 42 curriculum. The goal is to recreate a functional shell inspired by Bash, handling command execution, pipes, redirections, environment variables, signals, and a set of built-in commands.

The project covers core concepts such as process creation with `fork`/`execve`, file descriptor management (`dup2`, `pipe`, `open`/`close`), signal handling, and command-line parsing including quoting rules and variable expansion.

## Instructions

#### Built-in commands
echo - Shows input as text that was passed as argument;
cd - Move between folders;
pwd - Shows you the folder you are using;
export
unset
env
exit

#### Commands
ls - Shows files;
cat
wc

# Running it (temporary)


### Requirements

- `cc` compiler
- GNU `readline` library (`libreadline-dev` on Debian/Ubuntu)
- `make`

### Compilation

```bash
make
```

This builds `libft` first, then compiles all source files into the `minishell` binary.

### Running

```bash
./minishell
```

The shell displays a prompt and accepts interactive commands. To exit, type `exit` or press `ctrl-D`.

### Cleanup

```bash
make clean    # remove object files
make fclean   # remove object files and binary
make re       # fclean + all
```

## Features

- Interactive prompt with command history (arrow keys)
- Executable search via `PATH`, relative path, or absolute path
- Pipes: `cmd1 | cmd2 | cmd3`
- Redirections: `<`, `>`, `>>`, `<<` (heredoc)
- Environment variable expansion (`$VAR`, `$?`)
- Single quotes (`'`) — no interpretation of metacharacters
- Double quotes (`"`) — metacharacters suppressed except `$`
- Signal handling: `ctrl-C` (new prompt), `ctrl-D` (exit), `ctrl-\` (ignored)
- Built-in commands:
  - `echo [-n]`
  - `cd <path>`
  - `pwd`
  - `export [name=value]`
  - `unset <name>`
  - `env`
  - `exit [status]`

## Resources

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [The Linux Programming Interface — Michael Kerrisk](https://man7.org/tlpi/)
- [Advanced Programming in the UNIX Environment — W. Richard Stevens](https://www.apuebook.com/)
- [Shell Command](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html)
- [Error codes](https://www.chromium.org/chromium-os/developer-library/reference/linux-constants/errnos/)
- `man` pages: `fork`, `execve`, `pipe`, `dup2`, `waitpid`, `signal`, `sigaction`, `readline`

## Use of AI

GitHub Copilot (Claude Sonnet 4.6) was used during this project for the following tasks:

- Answering questions about POSIX signal handling and `sigaction` semantics.
- Clarifying edge cases in Bash quoting and variable expansion behavior.
- Suggesting approaches for heredoc implementation and pipe chaining.

All AI-generated content was reviewed, tested, and validated by the authors before being included in the project.
