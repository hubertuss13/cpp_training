#include <iostream>
#include <vector>
#include <string>
#include <numeric>      // std::accumulate

namespace coin_change
{
    struct Result
    {
        int count;                  // minimalna liczba monet albo -1
        std::vector<int> used;      // użyte monety (puste, gdy count <= 0)
    };

    Result solve(const std::vector<int>& coins, int amount)
    {
        const int INF = amount + 1;
        std::vector<int> dp(amount + 1, INF);
        std::vector<int> lastCoin(amount + 1, -1);
        dp[0] = 0;

        for (int a = 1; a <= amount; ++a)
        {
            for (int coin : coins)
            {
                if (coin <= a && dp[a - coin] + 1 < dp[a])
                {
                    dp[a] = dp[a - coin] + 1;
                    lastCoin[a] = coin;
                }
            }
        }

        if (dp[amount] == INF)
            return { -1, {} };

        Result result{ dp[amount], {} };
        for (int a = amount; a > 0; a -= lastCoin[a])
            result.used.push_back(lastCoin[a]);

        return result;
    }
}

struct TestCase
{
    std::vector<int> coins;
    int amount;
    int expected;
};

std::string toString(const std::vector<int>& v, const std::string& separator)
{
    std::string out;
    for (std::size_t i = 0; i < v.size(); ++i)
    {
        if (i > 0) out += separator;
        out += std::to_string(v[i]);
    }
    return out;
}

int main()
{
    std::cout << "===== Dynamic Programming: Coin Change =====\n\n";

    const std::vector<TestCase> tests = {
        { {1, 3, 4},  6,  2 },
        { {1, 2, 5}, 11,  3 },
        { {2},        3, -1 },
        { {1},        0,  0 },
    };

    int passed = 0;
    for (std::size_t i = 0; i < tests.size(); ++i)
    {
        const TestCase& t = tests[i];
        const coin_change::Result r = coin_change::solve(t.coins, t.amount);

        // Wynik jest poprawny, gdy liczba się zgadza ORAZ użyte monety
        // faktycznie sumują się do kwoty (sprawdza też odtwarzanie).
        const int sum = std::accumulate(r.used.begin(), r.used.end(), 0);
        const bool ok = r.count == t.expected
                     && (r.count == -1 || sum == t.amount);
        if (ok) ++passed;

        std::cout << "Test " << i + 1
                  << ": monety {" << toString(t.coins, ", ") << "}"
                  << ", kwota " << t.amount
                  << " -> " << r.count;
        if (!r.used.empty())
            std::cout << " (" << toString(r.used, " + ") << ")";
        std::cout << "  [" << (ok ? "OK" : "FAIL, oczekiwano " + std::to_string(t.expected)) << "]\n";
    }

    std::cout << "\nZaliczone: " << passed << "/" << tests.size() << "\n";
    return passed == static_cast<int>(tests.size()) ? 0 : 1;
}
