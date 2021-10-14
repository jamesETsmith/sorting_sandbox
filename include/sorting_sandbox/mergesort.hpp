#include <vector>

void merge_sort(std::vector<int> x, size_t lb, size_t ub)
{
    if ((lb - ub) > 1){
    // Split
    size_t middle = (ub-1)/2 + 1;

    // Recurse
    merge_sort(x,lb,middle);
    merge_sort(x,middle+1, ub);

    // Merge

    }
}