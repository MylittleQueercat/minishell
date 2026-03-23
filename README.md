# 🐚 Minishell

![Score](https://img.shields.io/badge/Score-125%2F125-brightgreen)
![Language](https://img.shields.io/badge/Language-C-blue)
![42](https://img.shields.io/badge/42-Project-black)
![Team](https://img.shields.io/badge/Team-2_people-orange)

## 📌 Project Goal

**Minishell** is one of the most ambitious projects in the 42 curriculum. The goal is to build a **fully functional Unix shell** from scratch in C, closely mimicking the behavior of **bash**.

The shell must handle user input in a loop, parse it into commands, execute them with proper process management, and handle redirections, pipes, environment variables, signals, and a set of built-in commands — all while replicating bash's exact behavior down to edge cases.

Bonus adds support for **logical operators** (`&&`, `||`), **wildcards** (`*`), and **parentheses** for grouping.

---

## 🧠 Key Concepts

### The Read-Eval-Print Loop (REPL)
The shell runs in an infinite loop:
1. **Read** — display a prompt and read user input (via `readline`)
2. **Lex** — tokenize the raw input into meaningful units
3. **Parse** — build an Abstract Syntax Tree (AST) representing the command structure
4. **Execute** — walk the AST and run commands
5. **Repeat**

### Lexing & Tokenization
Raw input is split into **tokens**: words, operators (`|`, `<`, `>`, `>>`, `<<`, `&&`, `||`), and parentheses. Quoting rules must be applied at this stage:
- **Single quotes** `'...'`: preserve everything literally, no expansion
- **Double quotes** `"..."`: allow `$VAR` and `$?` expansion, suppress everything else

### Parsing & AST
Tokens are parsed into a tree structure that reflects precedence:
```
cmd1 && cmd2 | cmd3 || cmd4
```
becomes a tree where `||` is the root, `&&` is a child, and `|` is lower — execution follows the tree recursively.

For the mandatory part, a simple left-to-right **pipeline list** is sufficient. The bonus requires a proper recursive descent parser that handles `&&`, `||`, and `()`.

### Process Management
Commands are executed in **child processes** via `fork()` + `execve()`. The parent waits with `waitpid()`. For pipelines, each command runs in its own child with pipes connecting `stdout` → `stdin` between them.

| Function | Description |
|---|---|
| `fork` | Create a child process |
| `execve` | Replace the process image with a new program |
| `waitpid` | Wait for a specific child to finish |
| `pipe` | Create a unidirectional channel between processes |
| `dup2` | Redirect a file descriptor to another |

### Redirections
| Operator | Behavior |
|---|---|
| `< file` | Redirect stdin from file |
| `> file` | Redirect stdout to file (truncate) |
| `>> file` | Redirect stdout to file (append) |
| `<< DELIM` | Heredoc: read stdin until `DELIM` is encountered |

All redirections are set up with `open()` + `dup2()` before `execve()`.

### Environment Variables
The shell maintains its own copy of the environment as a linked list or array. `$VAR` is expanded during parsing/execution. `$?` holds the exit status of the last command.

### Signals
| Signal | Default shell behavior |
|---|---|
| `Ctrl+C` (`SIGINT`) | In prompt: print new line. In child: kill child |
| `Ctrl+\` (`SIGQUIT`) | Ignored in prompt, terminates child with core dump message |
| `Ctrl+D` (EOF) | Exit the shell |

Signal behavior changes depending on context (interactive prompt vs. running command vs. heredoc), which requires careful use of `signal()` or `sigaction()`.

### Built-in Commands
Built-ins are executed **directly in the parent process** (or current process), not via `execve`, because they must be able to affect the shell's own state (e.g. `cd` changes the shell's working directory, `export` modifies its environment).

| Built-in | Behavior |
|---|---|
| `echo [-n]` | Print arguments, `-n` suppresses trailing newline |
| `cd [path]` | Change working directory, update `PWD`/`OLDPWD` |
| `pwd` | Print current working directory |
| `export [name=value]` | Add/update environment variable |
| `unset [name]` | Remove environment variable |
| `env` | Print all exported environment variables |
| `exit [code]` | Exit the shell with optional status code |

### Bonus — Logical Operators & Wildcards
- `&&` / `||`: execute next command conditionally based on exit status of previous
- `()`: group commands, executing them in a **subshell** (child process)
- `*`: wildcard expansion — match files in the current directory using `opendir`/`readdir`

---

## 🚀 Usage

### Compilation
```bash
make        # mandatory
make bonus  # with && || () and wildcards
```

### Running
```bash
./minishell
```
The shell starts in interactive mode with a prompt. It also reads from a pipe (non-interactive mode):
```bash
echo "ls -la" | ./minishell
```

### Example Interactions
```bash
# Pipes
ls -la | grep ".c" | wc -l

# Redirections
cat < input.txt > output.txt
cat << EOF
hello
EOF

# Environment
export MY_VAR=hello
echo $MY_VAR
echo $?

# Built-ins
cd ..
pwd
unset MY_VAR
env | grep PATH

# Bonus: logical operators
make && echo "success" || echo "failed"

# Bonus: wildcards
echo *.c

# Bonus: subshell
(cd /tmp && ls)
```

---

## 🏗️ Implementation Logic

### Overall Architecture
```
readline()
    └── Lexer        → token list
         └── Parser  → AST
              └── Executor
                   ├── Built-ins (in current process)
                   ├── Simple commands (fork + execve)
                   ├── Pipelines (N forks + N-1 pipes)
                   ├── Redirections (open + dup2)
                   └── Bonus: &&, ||, (), *
```

### Execution Flow for a Pipeline
```
cmd1 | cmd2 | cmd3
 ├── pipe(fd1)
 ├── fork → child1: dup2(fd1[1], STDOUT), execve(cmd1)
 ├── pipe(fd2)
 ├── fork → child2: dup2(fd1[0], STDIN), dup2(fd2[1], STDOUT), execve(cmd2)
 ├── fork → child3: dup2(fd2[0], STDIN), execve(cmd3)
 └── parent: close all fds, waitpid all children
```

### Heredoc (`<<`)
The heredoc reads lines from the terminal (or input) into a **temporary pipe or file** before execution begins. All heredocs in a command line are processed **before any command is run**. Signals during heredoc input must also be handled correctly (`Ctrl+C` cancels the heredoc).

### Variable Expansion
Expansion happens after lexing, before execution. Walk each token and replace `$VAR` with its value from the environment, and `$?` with the last exit status. Respect quoting: no expansion inside single quotes.

### Bonus — AST with Operator Precedence
```
Precedence (low → high):
  ||
  &&
  |
  simple_command + redirections
```
A recursive descent parser builds the tree naturally. At execution time, walk the tree:
- `AND_NODE`: run left; if exit 0, run right
- `OR_NODE`: run left; if exit ≠ 0, run right
- `PIPE_NODE`: run both in subprocesses connected by a pipe
- `SUBSHELL_NODE`: fork, execute the child tree in the subprocess

---

## ⚠️ Common Mistakes & Tricky Points

- **Quoting edge cases**: `echo "'hello'"`, `echo ""`, `"$VAR"` with spaces — bash behavior here is very specific. Test exhaustively against real bash.
- **Built-ins in pipelines**: `echo hi | cd /tmp` — `cd` is in a child, so it must NOT affect the parent's directory. Only run built-ins in the parent when they are **not** part of a pipeline.
- **Closing all pipe fds**: Forgetting to close unused pipe ends causes commands to hang forever waiting for EOF that never comes.
- **Signal handling in child vs. parent**: Children should restore default signal handlers (`SIG_DFL`) before `execve`. The parent must not be killed by `SIGINT` when a child is running.
- **Heredoc + signals**: `Ctrl+C` during a heredoc must cancel it and show a new prompt — not exit the shell.
- **`$?` after built-ins**: Built-in commands must also set the exit status correctly (e.g. `cd nonexistent` → exit 1).
- **Memory management**: Every `readline` result, every token, every AST node must be freed. Run with `valgrind` regularly.
- **`execve` PATH resolution**: When the command has no `/`, search for it in every directory listed in `PATH`. Replicate bash's exact error messages (`command not found`, `Permission denied`).

---

## ✅ Evaluation Checklist

- [ ] Prompt displays and `readline` history works
- [ ] Single and double quotes handled correctly
- [ ] All redirections work (`<`, `>`, `>>`, `<<`)
- [ ] Pipelines with N commands work
- [ ] All 7 built-ins behave like bash
- [ ] `$VAR` and `$?` expand correctly
- [ ] `Ctrl+C`, `Ctrl+\`, `Ctrl+D` behave like bash
- [ ] Exit status (`$?`) is accurate after every command
- [ ] No zombie processes (all children waited on)
- [ ] No memory leaks (except `readline` internals)
- [ ] **Bonus**: `&&` and `||` with correct short-circuit logic
- [ ] **Bonus**: `()` subshells execute in a child process
- [ ] **Bonus**: `*` expands correctly in the current directory

---

## 🛠️ Useful Debug Commands

```bash
# Compare your shell vs bash behavior
bash -c 'echo $?'
./minishell -c 'echo $?'   # if you implemented -c flag

# Memory leaks
valgrind --leak-check=full --suppressions=readline.supp ./minishell

# Test signal behavior
./minishell
# then press Ctrl+C, Ctrl+\, Ctrl+D in various contexts

# Stress test pipes
cat /dev/urandom | head -c 1000 | xxd | head
```
