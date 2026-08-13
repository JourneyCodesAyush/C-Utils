#!/usr/bin/env bash

set -uo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
FIXTURES="$ROOT_DIR/tests/fixtures"

if [[ -f "$ROOT_DIR/cutils.exe" ]]; then
    CUTILS="$ROOT_DIR/cutils.exe"
elif [[ -f "$ROOT_DIR/cutils" ]]; then
    CUTILS="$ROOT_DIR/cutils"
else
    echo "ERROR: cutils executable not found"
    echo "Expected: $ROOT_DIR/cutils or $ROOT_DIR/cutils.exe"
    exit 1
fi

passed=0
failed=0

pass() {
    echo "PASS: $1"
    passed=$((passed + 1))
}

fail() {
    echo "FAIL: $1"
    failed=$((failed + 1))
}

assert_success() {
    local name="$1"
    shift

    if "$@" >/dev/null 2>&1; then
        pass "$name"
    else
        fail "$name"
    fi
}

assert_failure() {
    local name="$1"
    shift

    if "$@" >/dev/null 2>&1; then
        fail "$name"
    else
        pass "$name"
    fi
}

assert_output_contains() {
    local name="$1"
    local expected="$2"
    shift 2

    local output

    if output=$("$@" 2>&1) && [[ "$output" == *"$expected"* ]]; then
        pass "$name"
    else
        fail "$name"
        echo "  expected output to contain: $expected"
        echo "  actual output:"
        echo "$output"
    fi
}

echo "Running C Utilities tests..."
echo

# --------------------------------------------------
# Help / version
# --------------------------------------------------

assert_success \
    "help command" \
    "$CUTILS" --help

assert_success \
    "short help command" \
    "$CUTILS" -h

assert_success \
    "version command" \
    "$CUTILS" --version

assert_success \
    "short version command" \
    "$CUTILS" -v

# --------------------------------------------------
# pwd / whoami
# --------------------------------------------------

assert_success \
    "pwd command" \
    "$CUTILS" pwd

assert_success \
    "whoami command" \
    "$CUTILS" whoami

# --------------------------------------------------
# head
# --------------------------------------------------

assert_success \
    "head with default line count" \
    "$CUTILS" head "$FIXTURES/sample.txt"

assert_success \
    "head with explicit line count" \
    "$CUTILS" head -2 "$FIXTURES/sample.txt"

assert_success \
    "head with empty file" \
    "$CUTILS" head "$FIXTURES/empty.txt"

assert_success \
    "head with long line" \
    "$CUTILS" head "$FIXTURES/long_line.txt"

# --------------------------------------------------
# tail
# --------------------------------------------------

assert_success \
    "tail with default line count" \
    "$CUTILS" tail "$FIXTURES/sample.txt"

assert_success \
    "tail with explicit line count" \
    "$CUTILS" tail -2 "$FIXTURES/sample.txt"

assert_success \
    "tail with empty file" \
    "$CUTILS" tail "$FIXTURES/empty.txt"

assert_success \
    "tail with long line" \
    "$CUTILS" tail "$FIXTURES/long_line.txt"

# --------------------------------------------------
# wc
# --------------------------------------------------

assert_success \
    "wc lines" \
    "$CUTILS" wc -l "$FIXTURES/sample.txt"

assert_success \
    "wc words" \
    "$CUTILS" wc -w "$FIXTURES/sample.txt"

assert_success \
    "wc characters" \
    "$CUTILS" wc -c "$FIXTURES/sample.txt"

assert_success \
    "wc combined flags" \
    "$CUTILS" wc -lwc "$FIXTURES/sample.txt"

assert_success \
    "wc empty file" \
    "$CUTILS" wc -lwc "$FIXTURES/empty.txt"

# --------------------------------------------------
# Error handling
# --------------------------------------------------

assert_failure \
    "missing command" \
    "$CUTILS"

assert_failure \
    "unknown command" \
    "$CUTILS" does-not-exist

assert_failure \
    "missing input file" \
    "$CUTILS" head "$FIXTURES/does-not-exist.txt"

assert_failure \
    "missing input file for tail" \
    "$CUTILS" tail "$FIXTURES/does-not-exist.txt"

assert_failure \
    "missing input file for wc" \
    "$CUTILS" wc -l "$FIXTURES/does-not-exist.txt"

echo
echo "----------------------------------------"
echo "Tests passed: $passed"
echo "Tests failed: $failed"
echo "----------------------------------------"

if [[ "$failed" -ne 0 ]]; then
    exit 1
fi

echo "All tests passed."
