*This project has been created as part of the 42 curriculum by aantela-, pgois-wa.*

# push_swap

42 school project (42 Porto) that consists of sorting a stack of integers using **two stacks** (`a` and `b`) and a restricted set of operations, using the smallest possible number of operations.

This implementation goes beyond the minimum requirements: it includes **multiple sorting strategies** (for small, medium, and large stacks), a **benchmark mode** with operation counting and stack-disorder calculation, and an **adaptive mode** that automatically picks the best strategy based on the size/disorder of the input.

## Table of contents

- [Description](#description)
- [Instructions](#instructions)
- [Allowed operations](#allowed-operations)
- [Sorting strategies and justification](#sorting-strategies-and-justification)
- [Bench mode](#bench-mode)
- [Code structure](#code-structure)
- [Testing / Checker](#testing--checker)
- [Contributions](#contributions)
- [Resources](#resources)

## Description

The program receives a list of integers as arguments (all distinct, no duplicates), places them on stack `a`, and prints to standard output the sequence of instructions needed to sort stack `a` in ascending order, using stack `b` only as auxiliary space.

The goal of the project is to explore algorithmic complexity in a concrete way: implement four distinct strategies (`Simple` O(n²), `Medium` O(n√n), `Complex` O(n log n) and `Adaptive`), measure the **disorder** of each input (via inversion counting) and automatically pick the most efficient strategy based on that value.

General rules:
- No duplicate numbers allowed.
- Only valid integers are accepted (within `int` range).
- If the stack is already sorted, the program prints nothing.
- On error (invalid input, duplicate, overflow, etc.) the program prints `Error` to `stderr` and exits with code `1`.

## Instructions

### Build

```bash
make        # builds push_swap (and the internal ft_printf library)
make clean  # removes .o files
make fclean # removes .o files and the binary
make re     # fclean + all
```

The `Makefile` compiles with `-Wall -Wextra -Werror` and internally depends on `ft_printf` (included in this repository under `ft_printf/`), automatically built as a static library before linking the executable.

### Usage

```bash
./push_swap [flags] arg1 arg2 arg3 ...
./push_swap arg1 arg2 arg3 ... [flags] 
```

Arguments can be passed either as several space-separated arguments or as a single string of space-separated numbers (both formats are supported, thanks to parsing with `ft_split`):

```bash
./push_swap 2 1 3 6 5 8
./push_swap "2 1 3 6 5 8"
```

### Optional flags

| Flag         | Effect                                                                 |
|--------------|-------------------------------------------------------------------------|
| `--bench`    | Enables benchmark mode: prints statistics to `stderr` at the end        |
| `--simple`   | Forces the "Simple" strategy (best for small stacks)                    |
| `--medium`   | Forces the "Medium" strategy                                            |
| `--complex`  | Forces the "Complex" strategy                                           |
| `--adaptive` | Forces adaptive mode (default behavior)                                 |

Flags can be placed before or after the numbers, and only one strategy can be selected per run.

Example:

```bash
./push_swap --bench --complex 5 4 3 2 1
./push_swap 5 4 3 2 1 --bench --complex
```

## Allowed operations

| Operation | Description                                              |
|-----------|-------------------------------------------------------------|
| `sa`      | Swaps the top 2 elements of `a`                              |
| `sb`      | Swaps the top 2 elements of `b`                              |
| `ss`      | `sa` and `sb` at the same time                                |
| `pa`      | Pops the top of `b` and pushes it onto the top of `a`         |
| `pb`      | Pops the top of `a` and pushes it onto the top of `b`         |
| `ra`      | Rotates `a` upward (the first element becomes the last)       |
| `rb`      | Rotates `b` upward                                            |
| `rr`      | `ra` and `rb` at the same time                                |
| `rra`     | Rotates `a` downward (the last element becomes the first)     |
| `rrb`     | Rotates `b` downward                                          |
| `rrr`     | `rra` and `rrb` at the same time                              |

## Sorting strategies and justification

The program automatically picks the most suitable strategy (`adaptive` mode, by default), based on the stack size and a **disorder** index computed via inversion counting (merge sort), measured **before** any operation is performed, as required by the subject.

| Strategy | Complexity   | When it's used (adaptive mode)              |
|----------|--------------|----------------------------------------------|
| Simple   | O(n²)        | Small stacks / low disorder (< 19%)           |
| Medium   | O(n·√n)      | Medium disorder (20% – 49%)                   |
| Complex  | O(n log n)   | High disorder (≥ 50%) or large stacks         |

For stacks with fewer than 6 elements, a dedicated algorithm (`sort_five`) is always used, optimized for the 3- and 5-element cases.

Any of these strategies can be forced manually with the `--simple`, `--medium`, or `--complex` flags, which is useful for comparing performance in bench mode.

### Technical justification of the thresholds

The 20% and 50% disorder thresholds were chosen because they reflect the point at which the cost of "placing" each element on the auxiliary stack `b` stops paying off compared to strategies with higher structural overhead (partitioning/merging) but lower asymptotic cost per element. With low disorder, most elements are already close to their final position, so a simple cost-based insertion (O(n²) worst case) has low overhead in practice. With medium disorder, splitting the stack into ⌈√n⌉ value-range chunks reduces the average number of rotations needed per element. With high disorder, the cost of keeping the stack "nearly sorted" during insertion stops being worthwhile, and a recursive partition-style approach (similar to quicksort/mergesort adapted to stacks) dominates in operation count.

#### Simple — O(n²)

**Authorship: `simple_sort.c` developed collaboratively — pgois-wa (base implementation) + aantela- (review/integration).**

Pushes all elements from `a` to `b`, computing for each one the rotation cost needed to insert it at the correct position relative to the elements already on `b` (`calculate_insertion_plan` + `plan_executor`), then brings everything back to `a` already sorted. Each insertion costs O(n) in the worst case (finding the position + rotating), for n elements → O(n²) operations worst case. Space: O(n) for both stacks.

#### Medium — O(n·√n)

**Authorship: `medium_sort.c` developed collaboratively — pgois-wa (base implementation) + aantela- (review/integration).**

Splits the stack's values into ⌈√n⌉ value-range "chunks" (`push_chunks_b`) and pushes them onto `b` while keeping each chunk partially ordered (`push_and_sort_b`, which does `sb` whenever local order is reversed). During the drain phase, it repeatedly selects the maximum value on `b` (`max_selector_b`), rotates it to the top via the shortest path (`rotate_to_top_b`), and pushes it onto `a`. Each selection/rotation costs O(√n) on average (thanks to the chunk structure), repeated n times → O(n·√n). Space: O(n).

#### Complex — O(n log n)

**Authorship: developed by aantela- (main implementation of `complex_sort.c`, `push_swap_utils.c`, cost logic, and rotation).**

Pushes all elements except the last 3 onto `b` (`push_all_to_b`), sorts the remaining 3 on `a` using a dedicated case (`sort_three`), then brings each element from `b` back to `a` via the lowest combined-cost position (`move_cheapest`, which computes rotation cost on both `a` and `b` simultaneously and picks the cheaper one). Finally, it aligns the minimum of `a` to the top (`rotate_min_to_top`). Using combined cost (the cheaper of rotating `a` or `b`, including `rr`/`rrr`) is what brings the operation count close to O(n log n) — analogous to the efficient partitioning idea used in quicksort/mergesort adapted to two stacks. Space: O(n).

#### Adaptive (custom, learner's design)

**Authorship: selection logic (disorder calculation + strategy choice) developed collaboratively by aantela-, pgois-wa integrating the three strategies above.**

Measures the disorder of the input stack via inversion counting with merge sort (O(n log n), measured before any operation), then selects the strategy whose complexity regime matches the observed disorder level, per the table above. This ensures the number of generated operations meets the targets required by the subject (< 0.2 → O(n²); 0.2–0.5 → O(n√n); ≥ 0.5 → O(n log n)).

## Bench mode

When `--bench` is enabled, the program runs the sort normally (printing the operations to `stdout`, as usual) and additionally writes a summary to `stderr` containing:

- **disorder**: percentage of disorder in the input stack (based on inversion counting via merge sort);
- **strategy**: the strategy used (and, in adaptive mode, the strategy actually chosen) along with its complexity class;
- **total_ops**: total number of operations executed;
- Individual count for each operation (`sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`).

Example output (`stderr`) for 500 random numbers:

```
[bench] disorder:  49.93%
[bench] strategy:  Adaptive / O(n√n)
[bench] total_ops: 7997
[bench] sa: 0 sb: 0 ss: 0 pa: 500 pb: 500
[bench] ra: 4840 rb: 1098 rr: 0 rra: 0 rrb: 1059 rrr: 0
```

## Code structure

```
.
├── main_novo.c                # entry point, argument parsing and overall flow
├── parse_args.c               # integer validation, duplicate checks, is_sorted
├── parse_args_utils.c         # flag parsing (--bench, --simple, --medium, ...)
├── push_swap_utils.c          # stack creation/manipulation (t_list / t_node)
├── push_swap_utils_medium.c   # helpers for the medium strategy
├── push.c / swap.c / rotate.c / reverse_rotate.c
│                               # implementation of the 11 operations (pa, pb, sa, sb, ss, ra, rb, rr, rra, rrb, rrr)
├── simple_sort*.c              # Simple strategy + sort_three
├── sort_five*.c                 # dedicated algorithm for stacks < 6 elements
├── medium_sort*.c              # Medium strategy (O(n·√n))
├── complex_sort*.c              # Complex strategy (O(n log n))
├── bench*.c                     # disorder calculation (merge sort) and bench report printing
├── erro_handler.c              # error handling and memory cleanup
├── utils*.c                     # ft_strcmp, ft_split, rotate_to_top, ft_sqrt, etc.
├── push_swap.h                  # structs (t_node, t_list, t_program, t_bench...) and prototypes
└── ft_printf/                    # custom printf implementation, used internally

```

Main data structures (`push_swap.h`):

- `t_node` / `t_list`: doubly linked list representing each stack;
- `t_program`: aggregates both stacks (`a`, `b`), the chosen strategy, bench state, and the computed disorder;
- `t_bench`: counter for each operation, passed explicitly through the call chain (no global variables);
- `t_move_plan` / `t_range`: helper structures for planning insertion costs in the Simple/Medium algorithms.

The code follows 42's **norminette** (functions with at most 25 lines, at most 4 parameters, no `for` loops, among other rules), so logic is frequently split into small helper functions and uses `while` instead of `for`.

## Testing / Checker

The  `checker_linux` binary (provided by 42) that takes the same list of numbers and the instructions generated by `push_swap` via `stdin`, and confirms whether the stack ends up correctly sorted:

```bash
ARGS="2 1 3 6 5 8"
./push_swap $ARGS | ./checker_linux $ARGS
# OK  -> stack was correctly sorted with the operations used
# KO  -> sorting error or invalid operation
```

It's also possible to generate large random inputs to test performance and correctness:

```bash
ARGS=$(python3 -c "import random; a=list(range(500)); random.shuffle(a); print(' '.join(map(str,a)))")
./push_swap $ARGS | ./checker_linux $ARGS
./push_swap --bench $ARGS > /dev/null   # see statistics on stderr
```

## Contributions

This project was developed as a pair, as required by the subject (group of exactly 2 learners). Both authors understand the entire codebase and are able to explain/defend it fully.

- **[aantela-](https://github.com/ArturVazOsorio)** (42 Porto):
  - Argument and flag parsing (`parse_args.c`, `parse_args_utils.c`), error handling (`erro_handler.c`).
  - Main implementation of the **Complex** strategy (O(n log n)): `complex_sort.c`, combined-cost logic (`move_cheapest`), `sort_three`, final alignment (`rotate_min_to_top`).
  - Adaptive selection logic (disorder calculation via merge sort and strategy choice by threshold).
  - Benchmark system (`t_bench`, operation counting, `print_bench`).
  - Norminette compliance (struct extraction such as `t_range`,file splitting).

- **[pgois-wa](https://github.com/PedroRamo-s)** (42 Porto):
  - Implementation of (`push`, `swap`, `rotate`, `reverse rotate`) operations.
  - Implementation of main (`t_node`) struct logic.
  - Adaptive selection logic (disorder calculation via merge sort and strategy choice by threshold).
  - Base implementation of the **Simple** (O(n²)) and **Medium** (O(n·√n)) strategies: `simple_sort.c`, `medium_sort.c`, insertion cost planning (`t_move_plan`), value-based chunking logic.
  - Joint review and final adjustments to both files together with aantela-.

## Resources

### References

- [42's push_swap subject (official project documentation)](https://github.com/42School)
- Cormen, Leiserson, Rivest, Stein — *Introduction to Algorithms* (sections on merge sort, inversions, and amortized complexity analysis)
- [Big-O Cheat Sheet](https://www.bigocheatsheet.com/) — used to validate the claimed complexity classes
- 42's norminette documentation (formatting rules and function limits)
- [geekforgeeks](https://www.geeksforgeeks.org/) - Used mainly for explanations and visual examples of different sorting algorithms.

### AI usage

AI (Claude, Anthropic, gemini) was used as occasional support for the following tasks, always reviewed and fully understood by both authors before integration:

- **Debugging**: identifying bugs related to incorrect assumptions between circular vs. linear rotation logic in push cost calculations.
- **Norminette compliance**: suggestions for file splitting, helper extraction, and refactoring to reduce the number of parameters per function (e.g. introducing the `t_range` struct).
- **README generation**: structuring and writing this file based on the repository and the subject, including the formatting required by Chapter VII.

No core sorting logic (Simple, Medium, Complex algorithms) was generated directly by AI without the authors' own implementation and understanding — AI served as a review tool, not as an author.
