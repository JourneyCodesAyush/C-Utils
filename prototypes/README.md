# C-Utils Prototype (Python)

This is a **Python prototype** of the `c-utils` project, implementing a small set of Unix-style commands (`head`, `tail`, `pwd`, `wc`) for **educational purposes**.
It allows experimentation with file I/O and command logic before translating concepts into C.

---

## Purpose

- Explore and prototype Unix-style utilities in Python.
- Test file reading, line/word/character counting, and argument parsing.
- Serve as a reference for the eventual C implementation.

---

## Supported Commands

### head

Prints the first N lines of a file.

- **Options:**
  - `-n` - number of lines to print (default: 10)
  - `-f` - filename

### tail

Prints the last N lines of a file.

- **Options:**
  - `-n` - number of lines to print (default: 10)
  - `-f` - filename

### pwd

Prints the current working directory.

- **Options:** None

### wc

Counts lines, words, and characters in a file.

- **Options:**
  - `-l` - count lines
  - `-w` - count words
  - `-c` - count characters
  - `-f` - filename

- Flags can be combined (e.g., `-lw`).

---

## Notes / Limitations

- This is a **single-file prototype** (`cutils.py`).
- `tail` reads the whole file into memory; large files may be slow.
- `wc` may miscount words for non-ASCII or multi-byte encodings.
- Designed for **learning and experimentation**, not production use.

---

## Installation

Requires **Python 3.10+**.

```bash
git clone https://github.com/journeycodesayush/c-utils.git
cd c-utils
python prototypes/cutils.py <command> [options]
```

---

## Usage Examples

```bash
# Print first 10 lines
python cutils.py head -f file.txt -n 10

# Print last 5 lines
python cutils.py tail -f file.txt -n 5

# Count lines and words
python cutils.py wc -f file.txt -lw

# Print working directory
python cutils.py pwd
```

---

## License

MIT License. See [LICENSE](LICENSE) for details.
