*This project has been created as part of the 42 curriculum by achancha, ysabraou.*

# push_swap

## Description

`push_swap` sorts distinct integers using two stacks (`a`, `b`) and the push_swap
operations, and prints the operations one per line. It only emits `sa`, `pa`,
`pb`, `ra`, `rb`, `rra`, `rrb`. Invalid input prints `Error` on `stderr`.
Bonus: `checker` reads operations (all 11) on `stdin` and prints `OK` or `KO`.

## Instructions

```sh
make            # builds ./push_swap
make bonus      # builds ./checker
make clean | fclean | re
```

```sh
./push_swap [--simple|--medium|--complex|--adaptive] [--bench] 3 2 1
ARG="3 1 2 5 4"; ./push_swap $ARG | ./checker $ARG
```

Flags go before the numbers. `--bench` prints stats on `stderr`.

## Algorithms

Values are replaced by their rank (0 to n-1). Disorder = inverted pairs /
(n*(n-1)/2), computed before any move.

- **Simple, selection sort, O(n²):** rotate the smallest value to the top, `pb`,
  repeat, then `pa` everything back. At most about n²/4 + 2n operations.
- **Medium, chunk sort, O(n√n):** push values to `b` by rank chunks of size
  about √(2n), then `pa` the maximum of `b` each time. Each pass over `a`
  pushes at least one chunk, so there are at most n/chunk passes of n moves.
- **Complex, quicksort, O(n log n):** split a chunk of ranks into low, middle and
  high parts, and send each part to the top or bottom of `a` or `b`. Repeat on
  every part until chunks have at most 3 values, which are sorted by hand.
- **Adaptive (default):** picks one of the above before any move.

| Disorder       | Strategy | Time         |
|----------------|----------|--------------|
| `< 0.2`        | Simple   | O(n²)        |
| `0.2 to < 0.5` | Medium   | O(n√n)       |
| `>= 0.5`       | Complex  | O(n log n)   |

Thresholds come from the subject. A random input has disorder around 0.5, so
below 0.2 the input is mostly sorted and a simple method is enough.
Extra space is O(1) for every strategy (only the two stacks, a few counters and,
for Complex, a fixed list of 64 pending chunks).

## Contributions

We worked mostly by pair programming and both reviewed and understand all the
code. Each of us led on some parts:
- achancha: disorder metric, Makefile, norm compliance
- ysabraou: argument parsing and validation, flag handling, `--bench`

## Resources

- https://en.wikipedia.org/wiki/Selection_sort
- https://en.wikipedia.org/wiki/Quicksort
- https://en.wikipedia.org/wiki/Big_O_notation
- https://42-cursus.gitbook.io/guide/2-rank-02/push_swap

AI was used to correct typos in README.md.
