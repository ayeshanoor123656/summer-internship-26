#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <blis.h>

int main()
{
    const dim_t N = 2048;
    const int RUNS = 100;

    double alpha = 1.0;
    double beta = 0.0;

    size_t elements = (size_t)N * (size_t)N;

    double *A = (double *)malloc(elements * sizeof(double));
    double *B = (double *)malloc(elements * sizeof(double));
    double *C = (double *)malloc(elements * sizeof(double));

    if (A == NULL || B == NULL || C == NULL)
    {
        printf("Memory allocation failed.\n");
        free(A);
        free(B);
        free(C);
        return 1;
    }

    // Initialize matrices
    for (size_t i = 0; i < elements; i++)
    {
        A[i] = 1.0;
        B[i] = 1.0;
        C[i] = 0.0;
    }

    FILE *fp = fopen("flops_results.txt", "w");
    if (fp == NULL)
    {
        printf("Cannot create output file.\n");
        free(A);
        free(B);
        free(C);
        return 1;
    }

    fprintf(fp, "Run,Time(s),GFLOPS\n");

    struct timespec start, end;

    for (int run = 1; run <= RUNS; run++)
    {
        printf("Starting Run %d...\n", run);
        fflush(stdout);

        // Reset C
        for (size_t i = 0; i < elements; i++)
            C[i] = 0.0;

        clock_gettime(CLOCK_MONOTONIC, &start);

        bli_dgemm(
            BLIS_NO_TRANSPOSE,
            BLIS_NO_TRANSPOSE,
            N, N, N,
            &alpha,
            A, N, 1,
            B, N, 1,
            &beta,
            C, N, 1
        );

        clock_gettime(CLOCK_MONOTONIC, &end);

        double elapsed =
            (end.tv_sec - start.tv_sec) +
            (end.tv_nsec - start.tv_nsec) * 1e-9;

        double operations = 2.0 * (double)N * (double)N * (double)N;
        double gflops = operations / (elapsed * 1e9);

        fprintf(fp, "%d,%.6f,%.2f\n", run, elapsed, gflops);

        printf("Run %d completed | Time = %.4f s | GFLOPS = %.2f\n",
               run, elapsed, gflops);
    }

    fclose(fp);

    free(A);
    free(B);
    free(C);

    printf("\nResults saved to flops_results.txt\n");

    return 0;
}