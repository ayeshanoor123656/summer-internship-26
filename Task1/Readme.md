# BLIS DGEMM Performance Benchmark

## Overview

This project benchmarks the performance of the BLIS library by measuring the floating-point operations per second (FLOPS) for double-precision matrix multiplication (DGEMM). The benchmark was performed using square matrices of different sizes to evaluate BLIS performance on the target hardware.

## Files

- `main.c` – C source code implementing the BLIS DGEMM benchmark.
- `results.csv` – Benchmark results containing the FLOPS measured for each run and matrix size.

## Implementation

The benchmark performs the following steps:

1. Allocates memory for matrices **A**, **B**, and **C**.
2. Initializes matrices **A** and **B** with constant values.
3. Resets matrix **C** before each benchmark run.
4. Executes matrix multiplication using the BLIS `bli_dgemm()` function.
5. Measures execution time using the C `clock()` function.
6. Computes the achieved FLOPS using:

```
FLOPS = (2 × M × N × K) / Execution Time
```

7. Repeats the benchmark for **100 runs** for each matrix size.
8. Stores the FLOPS results in a CSV file for analysis.

## Matrix Sizes Evaluated

- 2048 × 2048 (2K)
- 4096 × 4096 (4K)
- 8192 × 8192 (8K)

An attempt was made to benchmark 16384 × 16384 (16K), but it could not be completed due to the memory requirements of the test system.

## Hardware

- **Processor:** AMD Ryzen 5 5500U with Radeon Graphics
- **Physical Cores:** 6
- **Logical Threads:** 12
- **Maximum Frequency:** ~4.06 GHz

## Compilation

```bash
gcc main.c -o benchmark -lblis -lm
```

## Execution

```bash
./benchmark
```

The program generates FLOPS measurements for each run and saves the results in CSV format.

## Outcome

The benchmark demonstrates the performance of the BLIS DGEMM implementation across multiple matrix sizes. The collected FLOPS values can be used to compare performance, observe scalability, and analyze the computational efficiency of BLIS on the target hardware.
