*This project has been created as part of the 42 curriculum by <yyuskiv>, <masolet->.*

# Minishell

## Description
Minishell is a project from 42 that challenges you to build a simple but functional UNIX shell from scratch. The main goal is to understand how a shell operates, including process creation, execution, synchronization, and the parsing of complex command lines.

In this project, we implemented a custom shell that supports basic features found in bash, such as executing commands, handling arguments, managing environment variables, pipes (`|`), redirections (`<`, `>`, `<<`, `>>`), and several built-in commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`).

## Instructions

### Prerequisites
- A UNIX-like operating system (Linux)
- GCC or Clang compiler
- `make` utility
- `readline` library installed on your system

### Compilation

```bash
git clone <url> minishell
cd minishell
make
```

This will create an executable file named `minishell`.
Additional Makefile rules available:
- `make clean`: Removes object files.
- `make fclean`: Removes object files and the executable.
- `make re`: Recompiles the entire project.

### Execution
Run the compiled executable to start minishell:

```bash
./minishell
```

You will be greeted with a custom prompt, and you can start typing commands just like in bash.

### Tests

#### 1. Simple Commands

| # | Test | Expected result |
|---|---|---|
| 1.1 | `/bin/ls` | Executes via the absolute path. |
| 1.2 | `ls` | Executes normally without options. |
| 1.3 | `   ` (spaces only) + Enter | Nothing executes, new command prompt. |
| 1.4 | Leading/trailing spaces: `   ls   ` | Executes normally, spaces ignored. |

---

#### 2. Arguments

| # | Test | Expected result |
|---|---|---|
| 2.1 | `/bin/ls -l -a` | Works with multiple arguments. |
| 2.2 | `echo a b c` | Arguments correctly split and printed. |
| 2.3 | Multiple spaces: `ls   -l    -a` | Works like bash, extra spaces ignored. |
| 2.4 | Command + invalid args: `ls --xyz` | Error handled cleanly (no crash). |

---

#### 3. Builtin: echo

| # | Test | Expected result |
|---|---|---|
| 3.1 | `echo` | Prints an empty line. |
| 3.2 | `echo hello world` | Prints `hello world`. |
| 3.3 | `echo -n hello` | Prints `hello` without a newline (`\n`). |
| 3.4 | `echo -n` | Prints nothing, no newline. |
| 3.5 | `echo -x hello` | `-x` is treated as a plain argument (prints `-x hello`). |

---

#### 4. Builtin: exit

| # | Test | Expected result |
|---|---|---|
| 4.1 | `exit` | Exits shell with the current error code (`$?`). |
| 4.2 | `exit 0` | Exits with code 0. |
| 4.3 | `exit 42` | Exits with code 42. |
| 4.4 | `exit abc` | Error `numeric argument required`, exits the shell. |
| 4.5 | `exit 1 2` | Error `too many arguments`, **does not exit** the shell. |

---

#### 5. Return Value ($?)

| # | Test | Expected result |
|---|---|---|
| 5.1 | `/bin/ls; echo $?` | Prints `0`. |
| 5.2 | `/bin/ls nonexistent_file; echo $?` | Prints a non-zero code (e.g., 2). |
| 5.3 | `/nonexistent_command; echo $?` | Prints `127` (command not found). |
| 5.4 | `/etc/passwd; echo $?` | Prints `126` (permission denied). |

---

#### 6. Signals

| # | Test | Expected result |
|---|---|---|
| 6.1 | `Ctrl-C` on empty prompt | Prints a newline, new prompt, nothing executes. |
| 6.2 | `Ctrl-\` on empty prompt | Does nothing. |
| 6.3 | `Ctrl-D` on empty prompt | Exits minishell (EOF). |
| 6.4 | `Ctrl-C` after typing text | Newline, empty prompt, buffer cleared. |
| 6.5 | `Ctrl-C` during `cat` command | Interrupts `cat`, back to prompt, `echo $?` gives `130`. |
| 6.6 | `Ctrl-D` during `cat` command | Sends EOF to `cat`, command terminates normally. |

---

#### 7. Quotes (Single & Double)

| # | Test | Expected result |
|---|---|---|
| 7.1 | `echo "hello   world"` | Multiple spaces preserved. |
| 7.2 | `echo "test $HOME"` | Variable `$HOME` is expanded (replaced by its value). |
| 7.3 | `echo "it's a test"` | Single quote inside is preserved. |
| 7.4 | `echo 'hello'` | Prints `hello`. |
| 7.5 | `echo '$USER'` | Prints `$USER` literally (no expansion). |
| 7.6 | `echo 'a | b > c'` | No pipe or redirection is interpreted. |

---

#### 8. Builtins: env, export, unset

| # | Test | Expected result |
|---|---|---|
| 8.1 | `env` | Lists all environment variables. |
| 8.2 | `export FOO=bar` then `env` | `FOO=bar` is present in the list. |
| 8.3 | `export FOO=baz` then `env` | `FOO` value is updated to `baz`. |
| 8.4 | `export` alone | Lists exported variables. |
| 8.5 | `export 1INVALID=x` | Error `not a valid identifier`, no crash. |
| 8.6 | `unset FOO` then `env` | `FOO` is no longer in the list. |
| 8.7 | `unset NONEXISTENT_VAR` | No error, no crash. |

---

#### 9. Builtins: cd and pwd

| # | Test | Expected result |
|---|---|---|
| 9.1 | `pwd` | Prints the current directory. |
| 9.2 | `cd /tmp` then `pwd` | Prints `/tmp`. |
| 9.3 | `cd nonexistent_dir` | Error `No such file or directory`, no crash. |
| 9.4 | `cd ..` | Goes up one parent directory. |
| 9.5 | `cd` without arguments | Returns to the `$HOME` directory. |

---

#### 10. Paths (Absolute & Relative)

| # | Test | Expected result |
|---|---|---|
| 10.1 | `./minishell` (from root folder) | Launches a sub-shell. |
| 10.2 | `./nonexistent_file` | Error `No such file or directory`. |
| 10.3 | `ls` (no absolute path) | Works via the `$PATH` variable. |
| 10.4 | `unset PATH` then `ls` | Error `command not found`. |
| 10.5 | `/bin/ls` after `unset PATH` | Continues to work via the absolute path. |

---

#### 11. Redirections

| # | Test | Expected result |
|---|---|---|
| 11.1 | `echo hi > file.txt` then `cat file.txt` | Creates file containing `hi`. |
| 11.2 | `echo hello >> file.txt` | Appends to the end of file (contains `hi` then `hello`). |
| 11.3 | `cat < file.txt` | Prints the file's content. |
| 11.4 | `cat < nonexistent.txt` | Error `No such file or directory`. |
| 11.5 | `cat << EOF`, type text, then `EOF` | Heredoc reads data until keyword and sends to `cat`. |
| 11.6 | `ls > /protected_dir/file` | Error `Permission denied`. |

---

#### 12. Pipes

| # | Test | Expected result |
|---|---|---|
| 12.1 | `cat file.txt | grep hi` | The output of `cat` is filtered by `grep`. |
| 12.2 | `ls nonexistent | grep bla` | Error message from `ls` printed, pipeline continues without crashing. |
| 12.3 | `ls | cat > out.txt` | `out.txt` contains the output of `ls`. |
| 12.4 | `echo a | echo b` | Prints `b` (the 2nd echo ignores standard input). |

---

#### 13. Environment Variables

| # | Test | Expected result |
|---|---|---|
| 13.1 | `export VAR=test` then `echo $VAR` | Prints `test`. |
| 13.2 | `echo "$VAR"` | Variable is expanded inside double quotes. |
| 13.3 | `echo $NONEXISTENT_VAR` | Prints an empty line (does not crash). |
| 13.4 | `echo $` | Prints `$` literally. |

## Resources

### Classic References
- **GNU Bash Reference Manual**: Essential for understanding shell behavior and POSIX standards.
- **Linux man pages**: Essential reading for functions like `fork()`, `execve()`, `pipe()`, `dup2()`, `waitpid()`, etc.
- **Understanding AST (Abstract Syntax Trees)**: Helpful for building the parser and executing commands structurally.

### Use of AI
- **Debugging**: Assisting in tracking down memory leaks (using valgrind output) and resolving edge cases in string parsing.
- **Refactoring**: Providing suggestions on structuring the Abstract Syntax Tree (AST) logic and organizing the codebase to adhere to norminette.
- **README**: Assisting to write and translate this file.

