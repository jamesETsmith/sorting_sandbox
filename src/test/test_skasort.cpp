#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <algorithm>
#include <sorting_sandbox/ska_sort.hpp>
#include <vector>

#include "doctest.h"

TEST_CASE("Test Ska Sort Int") {
  // Setup
  std::vector<int> s_std = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
  std::vector<int> s_ska = s_std;

  // Sorting
  std::ranges::sort(s_std);
  ska_sort(s_ska.begin(), s_ska.end());

  // Checking
  bool matching = std::ranges::equal(s_std, s_ska);
  CHECK(matching);
}

TEST_CASE("Test Ska Sort Double") {
  // Setup
  std::vector<double> s_std = {
      0.24465606,  -0.33445588, -0.18817667, -0.03407485, -0.20146299,
      -0.25219877, 0.27672818,  0.42435399,  0.02566315,  -0.43084893};
  std::vector<double> s_ska = s_std;

  // Sorting
  std::ranges::sort(s_std);
  ska_sort(s_ska.begin(), s_ska.end());

  // Checking
  bool matching = std::ranges::equal(s_std, s_ska);
  CHECK(matching);
}