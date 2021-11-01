
#include <chrono>
#include <iostream>
#include <random>
#include <sorting_sandbox/mergesort.hpp>

#define N_ELEMENTS 100000000

/**
 * @brief From
 * https://www.fluentcpp.com/2019/05/24/how-to-fill-a-cpp-collection-with-random-values/
 *
 */
auto randomNumberBetween = [](double low, double high) {
  auto randomFunc =
      [distribution_ = std::uniform_real_distribution<>(low, high),
       random_engine_ = std::mt19937{std::random_device{}()}]() mutable {
        return distribution_(random_engine_);
      };
  return randomFunc;
};

void bench_mergesort(std::string method, int n_repetitions = 10) {

  // Sort
  double total_time = 0.0;
  for (int i = 0; i < n_repetitions; i++) {

    // SETUP
    std::vector<int> numbers(N_ELEMENTS);
    std::ranges::generate(numbers, randomNumberBetween(1., 5.));

    // BENCH
    auto _t0 = std::chrono::steady_clock::now();

    merge_sort(numbers, method);
    double t_sort =
        std::chrono::duration<double>(std::chrono::steady_clock::now() - _t0)
            .count();
    total_time += t_sort;
  }

  // Accumulate data
  double t_avg = total_time / n_repetitions;
  std::cout << "Time to sort " << N_ELEMENTS << " using " << method << " "
            << t_avg << std::endl;

  return;
}

int main() {
  bench_mergesort("serial");
  bench_mergesort("taskgroup");
  bench_mergesort("untied");
  bench_mergesort("taskyield");

  return 0;
}