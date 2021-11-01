#include <algorithm>
#include <vector>

// size_t _partition(std::vector<int>& x, size_t left, size_t right) {
//   size_t size = right - left;
//   size_t p = size / 2;
//   return p;
// }

// void _quicksort(std::vector<int>& x, size_t left, size_t right) {
//   if (left < right) {
//     size_t p = _partition(x, left, right);

// #pragma omp task default(none) firstprivate(x, left, p)
//     { _quicksort(x, left, p); }
// #pragma omp task default(none) firstprivate(x, right, p)
//     { _quicksort(x, p, right); }
//   }
// }

// void quicksort_omp(std::vector<int>& x) {
// #pragma omp parallel default(none) shared(x)
//   {
// #pragma omp single nowait
//     { _quicksort(x, 0, x.size()); }
//   }
// }
