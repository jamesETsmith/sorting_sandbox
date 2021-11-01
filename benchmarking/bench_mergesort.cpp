#include <benchmark/benchmark.h>

#include <random>
#include <sorting_sandbox/mergesort.hpp>

#define N_ELEMENTS 100000000

/**
 * @brief A helper class for some of the sorting utilities to reduce cache
 * misses and keep the indices and values closer to eachother.
 *
 */
class valuePair {
public:
  size_t idx;
  double value;
  // Default construction necessary to use with stl containers
  valuePair() {
    idx = 0;
    value = 0.0;
  }
  /**
   * @brief Construct a new value Pair object
   *
   * @param idx The index to store.
   * @param value The value hold onto for later comparison.
   */
  valuePair(const size_t idx, const double value) : idx(idx), value(value) {}
};

/**
 * @brief From
 * https://www.fluentcpp.com/2019/05/24/how-to-fill-a-cpp-collection-with-random-values/
 *
 */
auto randomNumberBetween = [](int low, int high) {
  auto randomFunc =
      [distribution_ = std::uniform_int_distribution<int>(low, high),
       random_engine_ = std::mt19937{std::random_device{}()}]() mutable {
        return distribution_(random_engine_);
      };
  return randomFunc;
};

//
//
//
static void BM_std_sort(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();

    // Generate random vector
    std::vector<int> numbers(N_ELEMENTS);
    std::ranges::generate(numbers, randomNumberBetween(1, 100));
    state.ResumeTiming();

    // Sort
    std::ranges::sort(numbers.begin(), numbers.end());
  }
}
BENCHMARK(BM_std_sort)->Unit(benchmark::kMillisecond)->MinTime(2);

//
//
//
static void BM_ss_sort_serial(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();

    // Generate random vector
    std::vector<int> numbers(N_ELEMENTS);
    std::ranges::generate(numbers, randomNumberBetween(1, 100));
    state.ResumeTiming();

    // Sort
    merge_sort(numbers, "serial");
  }
}
BENCHMARK(BM_ss_sort_serial)->Unit(benchmark::kMillisecond)->MinTime(2);

//
//
//
static void BM_ss_sort_taskgroup(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();

    // Generate random vector
    std::vector<int> numbers(N_ELEMENTS);
    std::ranges::generate(numbers, randomNumberBetween(1, 100));
    state.ResumeTiming();

    // Sort
    merge_sort(numbers, "taskgroup");
  }
}
BENCHMARK(BM_ss_sort_taskgroup)->Unit(benchmark::kMillisecond)->MinTime(2);

//
//
//
static void BM_ss_sort_untied(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();

    // Generate random vector
    std::vector<int> numbers(N_ELEMENTS);
    std::ranges::generate(numbers, randomNumberBetween(1, 100));
    state.ResumeTiming();

    // Sort
    merge_sort(numbers, "untied");
  }
}
BENCHMARK(BM_ss_sort_untied)->Unit(benchmark::kMillisecond)->MinTime(2);

//
//
//
static void BM_ss_sort_taskyield(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();

    // Generate random vector
    std::vector<int> numbers(N_ELEMENTS);
    std::ranges::generate(numbers, randomNumberBetween(1, 100));
    state.ResumeTiming();

    // Sort
    merge_sort(numbers, "taskyield");
  }
}
BENCHMARK(BM_ss_sort_taskyield)->Unit(benchmark::kMillisecond)->MinTime(2);

//
// Main
//
BENCHMARK_MAIN();
