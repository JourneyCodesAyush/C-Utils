# C Utilities

This repository is an **educational project** demonstrating applied C programming.
It implements a small set of Unix-style commands (`head`, `tail`, `pwd`, `wc`, `help`) using streaming I/O, proper argument handling, and explicit memory and resource management.

The focus is on **correctness, memory safety, and clarity**, not full coreutils coverage.
This project was created voluntarily for learning purposes, not as part of any academic requirement.

---

## Overview

Key design principles:

- **Streaming I/O** for low memory usage.
- **Dispatcher-based CLI** to route commands cleanly.
- **Explicit error handling** with `EXIT_SUCCESS` / `EXIT_FAILURE`.
- **Minimal memory overhead**, fixed buffers, and careful EOF handling.
- **Educational focus**, demonstrating applied C concepts.

---

## Commands

### head

Prints the first N lines of a file.
**Options:**

- `-n` – number of lines to print (default: 10)

### tail

Prints the last N lines of a file.
**Options:**

- `-n` – number of lines to print (default: 10)

### pwd

Prints the current working directory.
**Options:** None

### whoami

Prints the current user name.
**Options:** None

### wc

Counts lines, words, and characters in a file.
**Options:**

- `-l` – count lines
- `-w` – count words
- `-c` – count characters

> _Flags can be combined, e.g., `-lw`_

### -h / --help

Prints usage information.
**Options:** None

### -v / --version

Prints version information.
**Options:** None

---

## Notes / Limitations

- `head` and `tail` use fixed-size buffers; extremely long lines may be truncated.
- `wc` counts lines, words, and characters in a streaming fashion; multi-byte or special encodings may not be fully supported.
- This project is **educational** and does not aim to fully replicate Unix coreutils.
- Error messages are printed to `stderr`, and commands exit with `EXIT_FAILURE` on errors.

---

## Installation

```bash
git clone https://github.com/journeycodesayush/c-utils.git
cd c-utils
make
./cutils <command> [options]
```

---

## Usage Examples

```bash
./cutils head -10 file.txt
./cutils tail -5 file.txt
./cutils wc -lw file.txt
./cutils pwd
./cutils whoami
./cutils -h
./cutils --help
```

---

## Project Structure

```bash
c-utils/
├── src/
│   ├── main.c
│   ├── dispatcher.c
│   ├── head.c
│   ├── tail.c
│   ├── pwd.c
│   ├── wc.c
│   ├── whoami.c
│   └── help.c
├── include/  # Header files that are included in src/
│
├── Makefile
└── README.md
```

---

## Contributing

Contributions are welcome to improve the code, add commands, or fix bugs.

- Fork the repository and create a branch for your changes:
  `git checkout -b feat/new-command` or `git checkout -b fix/bug`
- Implement your changes and test locally.
- Commit with a clear message, using one of these scopes: `command`, `src`, `build`

```bash
feat(command): add new command
fix(command): correct line counting in wc implementation
docs(readme): update usage section
```

- Submit a pull request with a brief description of your changes.

---

## License

MIT License. See [LICENSE](LICENSE) for details.
