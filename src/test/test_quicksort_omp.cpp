#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <algorithm>
#include <sorting_sandbox/quicksort_omp.hpp>
#include <vector>

#include "doctest.h"

// TEST_CASE("Test Ska Sort Int") {
//   // Setup
//   std::vector<int> s_std = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
//   std::vector<int> s_qs = s_std;

//   // Sorting
//   std::ranges::sort(s_std);
//   quicksort_omp(s_qs);

//   // Checking
//   bool matching = std::ranges::equal(s_std, s_qs);
//   CHECK(matching);
// }
