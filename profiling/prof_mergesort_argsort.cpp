
#include <chrono>
#include <iostream>
#include <sorting_sandbox/mergesort.hpp>
#include <sorting_sandbox/random_helper.hpp>

void prof_mergesort(const std::string method, const uint64_t n_elements,
                    const int n_repetitions = 10) {

  // Sort
  double total_time = 0.0;
  for (int i = 0; i < n_repetitions; i++) {

    // SETUP
    std::vector<std::pair<size_t, double>> number_pairs(n_elements);
    auto _f = randomNumberBetween(-5, 5);
#pragma omp parallel for simd schedule(static, 16)
    for (int i = 0; i < n_elements; i++) {
      number_pairs[i] = std::make_pair(i, _f());
    }

    // prof
    auto _t0 = std::chrono::steady_clock::now();

    merge_sort<std::pair<size_t, double>>(number_pairs, method, [](const auto &left, const auto &right) {
      return abs(left.second) > abs(right.second);
    });

    double t_sort =
        std::chrono::duration<double>(std::chrono::steady_clock::now() - _t0)
            .count();
    total_time += t_sort;
  }

  // Accumulate data
  double t_avg = total_time / n_repetitions;
  std::cout << "Time to sort " << n_elements << " using " << method << " "
            << t_avg << std::endl;

  return;
}

int main(int argc, char **argv) {
  // Read in CLIs
  uint64_t n_elements;
  std::string method;
  int n_repetitions;

  if (argc != 4) {
    std::cout << "USING defaults!" << std::endl;
    n_elements = 1 << 25;
    std::cout << "n_elements = " << n_elements << std::endl;
    method = "serial";
    n_repetitions = 1;
  } else {
    n_elements = std::atoi(argv[1]);
    method = argv[2];
    n_repetitions = std::atoi(argv[3]);
  }

  // Run Kernel
  prof_mergesort(method, n_elements, n_repetitions);

  return 0;
}