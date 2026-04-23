#ifndef GEN_PERM_GLOBAL_CONTEXT_H
#define GEN_PERM_GLOBAL_CONTEXT_H

#include <iostream>
#include <vector>

class PermutationGlobalContext
{
public:
    PermutationGlobalContext(std::vector<int> collection);
    void generatePerm(int depth);
    int getResultCnt();

private:
    const std::vector<int> Collection;
    const int N;
    std::vector<bool> used;        // used[i] = true, jeśli Collection[i] jest już w current
    std::vector<int> current;      // permutacja, którą aktualnie budujemy
    int resultCnt;
};

#endif
