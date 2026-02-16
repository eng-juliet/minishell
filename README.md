# Minishell

## 📚 Project Overview
**Minishell** is a small Unix shell created as part of the 42 curriculum. It replicates the behavior of a basic shell, supporting command execution, built-in commands, pipes, redirections, environment variables, and signal handling. This project strengthens understanding of process management, system calls, and C programming in a Unix environment.

---

## 📌 Requirements
- Must be written in C.
- Implement a shell loop with a prompt.
- Support built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
- Execute external programs using `fork()` and `execve()`.
- Handle input/output redirections (`<`, `>`, `>>`, `<<`) and pipes (`|`).
- Expand environment variables (`$VAR`) correctly.
- Proper memory management (no leaks) and robust error handling.
- Handle signals like `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`.

---

## ⚙️ Features
The shell can:  

- Execute commands with arguments.
- Run pipelines connecting multiple commands.
- Handle input and output redirections.
- Expand environment variables within commands.
- Execute built-in commands without spawning new processes.
- Respond appropriately to keyboard signals.
- Maintain command history and allow navigation using arrow keys.

---

## 🧠 Algorithm

The core of **Minishell** is structured around the typical shell workflow:

### 1. Input Loop
- Shell runs in a loop displaying a prompt and reading user input.
- Input is added to history if valid.

### 2. Lexical Analysis (Tokenization)
- Splits input into *tokens* (words, pipes, redirections, quoted strings).
- Recognizes special characters for parsing.

### 3. Parsing
- Analyzes tokens according to shell grammar.
- Builds a structure representing commands, arguments, pipes, and redirections.

### 4. Expansion
- Expands environment variables (`$VAR`, `$?`).
- Handles quotes correctly to control expansion behavior.

### 5. Execution
- Built-in commands are executed directly by the shell.
- External commands are executed via:
  - `fork()` to create a child process.
  - `execve()` to replace the child process with the command.
- Redirections are applied using file descriptor manipulation (`dup2`, `open`, `close`).
- Pipes are created with `pipe()` to connect command input/output.

### 6. Signal Handling
- Handles signals (`SIGINT`, `SIGQUIT`) to mimic bash behavior.
- Ensures the shell doesn’t exit unexpectedly and cleans up processes properly.

### 7. Loop Continuation
- After execution, resources are freed, and the shell waits for the next input.

---

## 🛠 Installation
1. Clone the repository:
```bash
git clone eng-juliet/minishell
cd minishell
```
2. Build the library using the Makefile:
```bash
make
```
3. Optional cleanup:
```bash
make clean   # Removes object files
make fclean  # Removes object files and libft.a
```
4. Run the shell with any commands:
```bash
./minishell
```
5. Type any commands supported by the shell.


## 📝 Author
**Juliet Haddadin** – 2025

