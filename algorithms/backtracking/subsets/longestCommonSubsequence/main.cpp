#include <iostream>
#include <string>

const std::string a = "ABCBDAB";
const int N = a.size();
const std::string b = "BDCABA";
std::string current;
std::string best;

bool isSubsequence(const std::string & s, const std::string & t)
{
    size_t k = 0;
    for (char c : t)
    {
        if (k < s.size() && c == s[k])
        {
            k++;
        }
    }
    return k == s.size();
}

void genSubset(int index)
{
    if (index == N)
    {
        if (true == isSubsequence(current, b) && current.size() > best.size())
        {
            best = current;
        }
        return;
    }

    current.push_back(a[index]);
    genSubset(index + 1);
    current.pop_back();

    genSubset(index + 1);
}

void printSubset(const std::string & s, std::string label)
{
    std::cout << label << "[" << s << "]\n";
}

int main()
{
    std::cout << "===== Generating subsets: Longest Common Subsequence (LCS) =====" << std::endl;
    printSubset(a, "a=");
    printSubset(b, "b=");
    genSubset(0);
    if (true == best.empty())
        std::cout << "Nie znaleziono żadnego wspólnego podciągu dla obu ciągów\n";
    else
    {
        std::cout << "Najwiekszy wspolny podciag: [" << best << "]\n";
    }

    return 0;
}
