#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include <vector>
#include <algorithm>

TEST_CASE("Test MergeSort")
{
    // std::
    std::vector<int> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
    std::ranges::sort(s);
    CHECK(true);
}