#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <algorithm>
#include <sorting_sandbox/mergesort.hpp>
#include <sorting_sandbox/random_helper.hpp>
#include <vector>

#include "doctest.h"

TEST_CASE("Test MergeSort Int") {
  std::vector<int> s_std(100000);
  std::ranges::generate(s_std, randomNumberBetween(-100., 100.));
  std::ranges::sort(s_std);
  auto s_ss = s_std;

  merge_sort(s_ss, "serial");

  // Checking
  bool matching = std::ranges::equal(s_std, s_ss);
  CHECK(matching);
}

TEST_CASE("Test MergeSort Serial") {
  std::vector<double> s_std(100000);
  std::ranges::generate(s_std, randomNumberBetween(-1., 1.));
  std::ranges::sort(s_std);
  auto s_ss = s_std;

  merge_sort(s_ss, "serial");

  // Checking
  bool matching = std::ranges::equal(s_std, s_ss);
  CHECK(matching);
}

TEST_CASE("Test MergeSort taskgroup") {
  std::vector<double> s_std(100000);
  std::ranges::generate(s_std, randomNumberBetween(-1., 1.));
  std::ranges::sort(s_std);
  auto s_ss = s_std;

  merge_sort(s_ss, "taskgroup");

  // Checking
  bool matching = std::ranges::equal(s_std, s_ss);
  CHECK(matching);
}

TEST_CASE("Test MergeSort untied") {
  std::vector<double> s_std(100000);
  std::ranges::generate(s_std, randomNumberBetween(-1., 1.));
  std::ranges::sort(s_std);
  auto s_ss = s_std;

  merge_sort(s_ss, "untied");

  // Checking
  bool matching = std::ranges::equal(s_std, s_ss);
  CHECK(matching);
}

TEST_CASE("Test MergeSort taskyield") {
  std::vector<double> s_std(100000);
  std::ranges::generate(s_std, randomNumberBetween(-1., 1.));
  std::ranges::sort(s_std);
  auto s_ss = s_std;

  merge_sort(s_ss, "taskyield");

  // Checking
  bool matching = std::ranges::equal(s_std, s_ss);
  CHECK(matching);
}

TEST_CASE("Test MergeSort argsort") {
  // Set up
  const int n_elements = 100000;
  std::vector<std::pair<size_t, double>> s_std(n_elements);
  auto _f = randomNumberBetween(-1, 2.);
  for (int i = 0; i < n_elements; i++) {
    s_std[i] = std::make_pair(i, _f());
  }

  std::vector<std::pair<size_t, double>> s_ss = s_std;
  std::ranges::sort(s_std, [](const auto &left, const auto &right) {
    return abs(left.second) > abs(right.second);
  });

  // Sorting
  merge_sort(s_ss, "taskyield", [](const auto &left, const auto &right) {
    return abs(left.second) > abs(right.second);
  });

  for (int i = 0; i < 10; i++) {
    std::cout << i << " " << s_ss[i].second << " " << s_std[i].second
              << std::endl;
  }

  // Checking
  bool matching = std::ranges::equal(s_std, s_ss);
  CHECK(matching);
}

TEST_CASE("Test MergeSort argsort default") {
  // Set up
  const int n_elements = 100000;
  std::vector<std::pair<double, size_t>> s_std(n_elements);
  auto _f = randomNumberBetween(0, 2.);

#pragma omp parallel for schedule(static, 16)
  for (int i = 0; i < n_elements; i++) {
    s_std[i] = std::make_pair(_f(), i);
  }

  std::vector<std::pair<double, size_t>> s_ss = s_std;
  std::ranges::sort(s_std);

  // Sorting
  merge_sort(s_ss, "taskyield");

  for (int i = 0; i < 10; i++) {
    std::cout << i << " " << s_ss[i].first << " " << s_std[i].first
              << std::endl;
  }

  // Checking
  bool matching = std::ranges::equal(s_std, s_ss);
  CHECK(matching);
}