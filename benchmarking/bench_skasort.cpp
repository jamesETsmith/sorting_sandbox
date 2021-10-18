#include <benchmark/benchmark.h>

#include <random>
#include <sorting_sandbox/ska_sort.hpp>

#define N_ELEMENTS 10000000

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
static void BM_std_sort_int(benchmark::State& state) {
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
BENCHMARK(BM_std_sort_int)->Unit(benchmark::kMillisecond);
;

//
//
//
static void BM_ska_sort_int(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();

    // Generate random vector
    std::vector<int> numbers(N_ELEMENTS);
    std::ranges::generate(numbers, randomNumberBetween(1, 100));
    state.ResumeTiming();

    // Sort
    ska_sort(numbers.begin(), numbers.end());
  }
}
BENCHMARK(BM_ska_sort_int)->Unit(benchmark::kMillisecond);
;

//
//
//
static void BM_std_sort_double(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();

    // Generate random vector
    std::vector<double> numbers(N_ELEMENTS);
    std::ranges::generate(numbers, randomNumberBetween(1, 100));
    state.ResumeTiming();

    // Sort
    std::ranges::sort(numbers.begin(), numbers.end());
  }
}
BENCHMARK(BM_std_sort_double)->Unit(benchmark::kMillisecond);
;

//
//
//
static void BM_ska_sort_double(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();

    // Generate random vector
    std::vector<double> numbers(N_ELEMENTS);
    std::ranges::generate(numbers, randomNumberBetween(1, 100));
    state.ResumeTiming();

    // Sort
    ska_sort(numbers.begin(), numbers.end());
  }
}
BENCHMARK(BM_ska_sort_double)->Unit(benchmark::kMillisecond);
;

//
//
//
static void BM_std_sort_argsort(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();

    // Generate random vector
    std::vector<double> numbers(N_ELEMENTS);
    std::ranges::generate(numbers, randomNumberBetween(1, 100));

    std::vector<valuePair> pairs_full(numbers.size());
#pragma omp parallel for
    for (size_t i = 0; i < pairs_full.size(); i++) {
      pairs_full[i] = valuePair(i, abs(numbers[i]));
    }

    state.ResumeTiming();
    // Sort
    std::ranges::sort(
        pairs_full.begin(), pairs_full.end(),
        [](const valuePair& left, const valuePair& right) -> bool {
          return left.value > right.value;
        });
  }
}
BENCHMARK(BM_std_sort_argsort)->Unit(benchmark::kMillisecond)->MinTime(5);

//
//
//
static void BM_ska_sort_argsort(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    // Generate random vector
    std::vector<double> numbers(N_ELEMENTS);
    std::ranges::generate(numbers, randomNumberBetween(1, 100));

    std::vector<valuePair> pairs_full(numbers.size());
#pragma omp parallel for
    for (size_t i = 0; i < pairs_full.size(); i++) {
      pairs_full[i] = valuePair(i, abs(numbers[i]));
    }

    state.ResumeTiming();
    // Sort
    ska_sort(pairs_full.begin(), pairs_full.end(),
             [](auto&& a) -> decltype(auto) { return a.value; });
  }
}
BENCHMARK(BM_ska_sort_argsort)->Unit(benchmark::kMillisecond)->MinTime(5);
;

//
// Main
//
BENCHMARK_MAIN();
