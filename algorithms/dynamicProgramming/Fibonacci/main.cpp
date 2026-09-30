#include <iostream>
#include <cstring>  // memset

const int N = 10;
int memo[N + 1];


// Podejscie top-down => memoizacja
int FibonacciRecursive(unsigned n)
{
    // warunek bezpieczenstwa -> walidacja poprawnosci danych wejsciowych
    if (n > N) return -1;

    // 2 warunki wyjscia z rekurencji
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];  // już obliczone!

    memo[n] = FibonacciRecursive(n - 1) + FibonacciRecursive(n - 2);
    return memo[n];
}


// Podejscie bottom-up => tabulacja
int FibonacciIterative(unsigned n)
{
    int fib[N + 1];
    fib[0] = 0;
    fib[1] = 1;
    for (unsigned i = 2; i <= n; ++i)
    {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    return fib[n];
}

int main()
{
    //std::fill(memo, memo + N + 1, -1); // wypełnia CAŁĄ tablicę wartością -1 (nieobliczone)
    memset(memo, -1, sizeof(memo));  // wypełnia bajty wartością -1
    std::cout << "===== Dynamic Programming: Ciąg Fibonacci (z memoizacją) =====" << std::endl;
    std::cout << "Recursive top-down F(" << N << ") = " << FibonacciRecursive(N) << std::endl;
    std::cout << "Iterative bottom-up F(" << N << ") = " << FibonacciIterative(N) << std::endl;

    return 0;
}
