# Math Expression Compiler

A C++ compiler that parses infix expressions into a linear intermediate representation (IR), with constant folding optimisation.

## What it does

**Stage 1 — IR Generation:**
Parses infix expressions token-by-token using two stacks (operand and operator). Respects operator precedence (`/` > `*` > `+/-`) and decomposes each binary operation into a numbered temporary variable (`t1`, `t2`, ...).

**Stage 2 — Constant Folding:**
Traverses the generated IR and pre-computes any expression where both operands are known constants at compile time. Eliminates redundant temporary variables from output, reducing IR size.

## Example

**Input:**
```
a = 3 + 4 * 2
print a
```

**Output I (IR):**
```
t1 = 4 * 2
t2 = 3 + t1
a = t2
print a
```

**Output II (after constant folding):**
```
a = 11
11
```

## Build and Run

```bash
g++ -std=c++17 cpp_dc_project_2.cpp -o compiler
./compiler
```

Enter expressions line by line. Press `Ctrl+D` (EOF) when done.

## Supported Operations

| Operator | Precedence |
|----------|------------|
| `/`      | 3 (highest)|
| `*`      | 2          |
| `+`, `-` | 1          |
| `=`      | 0 (assignment)|

Special keyword: `print <variable>` — prints the value of a variable.

## Implementation Details

- **Dual stack parsing** — one stack for operands, one for operators; operator stack is flushed when incoming operator has lower precedence
- **IR storage** — `map<string, string>` for O(1) variable lookup, `vector<pair>` to preserve evaluation order
- **Constant folding** — single-pass traversal resolving all-constant sub-expressions; constants set tracks eliminated temporaries to suppress output
