#include <iostream>
#include <iomanip>
#include <omp.h>

int main() {
    const long long N = 50000000LL;
    long long sum = 0;
    int threads = 1;

    double start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        threads = omp_get_num_threads();
    }

    #pragma omp parallel for reduction(+:sum)
    for (long long i = 1; i <= N; i++) {
        sum += i;
    }

    double elapsed = omp_get_wtime() - start;
    const long long expected = N * (N + 1) / 2;

    std::cout << "Threads used: " << threads << "\n";
    std::cout << "Parallel sum of 1.." << N << " = " << sum << "\n";
    std::cout << "Expected value        = " << expected << "\n";
    std::cout << std::fixed << std::setprecision(4)
              << "Time: " << elapsed << " s\n";

    if (sum == expected) {
        std::cout << "TEST PASSED\n";
        return 0;
    }
    std::cout << "TEST FAILED\n";
    return 1;
}
