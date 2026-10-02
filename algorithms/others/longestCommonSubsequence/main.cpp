#include <iostream>
#include <string>

// Przykład dla a = "ABC", b = "AC":
// lcs(0, 0) to LCS napisów "ABC" i "AC"
// lcs(1, 1) to LCS napisów "BC" i "C"
// lcs(3, 2) to LCS napisów "" i ""

// !!! Odpowiedź na całe zadanie to lcs(0, 0) !!!

//  3 przypadki :
//  -> Jeden z napisów się skończył (jest pusty), więc wynik to 0, bo nie ma żadnego wspólnego znaku.
//          i == a.size() || j == b.size()
//
//  -> znaki rowne: a[i] == b[j] : znak na pewno możemy wziąć do wspólnego podciągu, więc wynik to 1 + lcs(i + 1, j + 1).
//          Twierdzenie: zawsze opłaca się sparować te dwa znaki ze sobą. Wtedy wynik to 1 + lcs(i+1, j+1).
//           
//  -> znaki są różne : przynajmniej jeden z nich nie należy do rozwiązania,
//     więc próbujemy obu opcji(pomiń znak z a albo pomiń znak z b) i bierzemy lepszą.
//     Skoro co najmniej jeden z nich jest zbędny, możemy go wyrzucić bez straty. 
//     Problem w tym, że nie wiemy, który. Dlatego sprawdzamy obie opcje i bierzemy lepszą
//          wyrzucamy a[i]: lcs(i+1, j), w przykładzie LCS("AB", "ABY") = 2
//          wyrzucamy b[j]: lcs(i, j + 1), w przykładzie LCS("XAB", "BY") = 1
//          Wynik: max(2, 1) = 2
//          std::max(lcs(a, b, i + 1, j),   // pomijamy a[i]
//          lcs(a, b, i, j + 1));           // pomijamy b[j]

// Przykład krok po kroku a = "ABC", b = "AC"
    //lcs("ABC", "AC")          A == A  →  1 + lcs("BC", "C")
    //  lcs("BC", "C")          B != C  →  max(lcs("C", "C"), lcs("BC", ""))
    //    lcs("C", "C")         C == C  →  1 + lcs("", "")
    //      lcs("", "")         pusty   →  0
    //    = 1
    //    lcs("BC", "")         pusty   →  0
    //  = max(1, 0) = 1
    //= 1 + 1 = 2


int lcs_count(const std::string & a, const std::string & b, size_t i, size_t j)
{
    if (a.size() == i || b.size() == j)     // pusty sufiks
        return 0;
    if (a[i] == b[j])
        return 1 + lcs_count(a, b, i + 1, j + 1);   // równe, bierzemy parę
    return std::max(lcs_count(a, b, i + 1, j), lcs_count(a, b, i, j + 1));  // różne, jeden z nich jest zbędny,
                                                                            // sprawdzamy oba i bierzemy lepszy
}


std::string lcs_string(const std::string & a, const std::string & b, size_t i, size_t j)
{
    if (a.size() == i || b.size() == j)
        return "";
    if (a[i] == b[j])
        return (a[i] + lcs_string(a, b, i + 1, j + 1));

    std::string x = lcs_string(a, b, i + 1, j);
    std::string y = lcs_string(a, b, i, j + 1);
    return x.size() >= y.size() ? x : y;
}


int lcs_invoke_print_with_indent(const std::string & a, const std::string & b,
                                 size_t i, size_t j, int depth = 0)
{
    std::string pad(depth * 2, ' ');
    std::cout << pad << "lcs(\"" << a.substr(i) << "\", \"" << b.substr(j) << "\")\n";

    int result;
    if (i == a.size() || j == b.size())
        result = 0;
    else if (a[i] == b[j])
        result = 1 + lcs_invoke_print_with_indent(a, b, i + 1, j + 1, depth + 1);
    else
        result = std::max(lcs_invoke_print_with_indent(a, b, i + 1, j, depth + 1),
                          lcs_invoke_print_with_indent(a, b, i, j + 1, depth + 1));

    std::cout << pad << "= " << result << '\n';
    return result;
}


int main()
{
    std::string a = "ABCBDAB", b = "BDCABA";
    std::cout << "===== Longest Common Subsequence (Recursion) various versions =====" << std::endl;
    std::cout << "a=[" << a << "], b=[" << b << "]" << std::endl;
    std::cout << "Longest Common Subsequence count for a and b = " << lcs_count(a, b, 0, 0) << '\n';  // 4

    std::cout << "Longest Common Subsequence string for a and b = [" << lcs_string(a, b, 0, 0) << "]\n\n";

    lcs_invoke_print_with_indent("ABC", "AC", 0, 0);

    return 0;
}
