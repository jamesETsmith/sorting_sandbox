#include <random>

/**
 * @brief From
 * https://www.fluentcpp.com/2019/05/24/how-to-fill-a-cpp-collection-with-random-values/
 *
 * @example
 * std::vector<int> numbers(n_elements);
 * std::ranges::generate(numbers, randomNumberBetween(-1., 5.));
 */
auto randomNumberBetween = [](double low, double high) {
  auto randomFunc =
      [distribution_ = std::uniform_real_distribution<>(low, high),
       random_engine_ = std::mt19937{std::random_device{}()}]() mutable {
        return distribution_(random_engine_);
      };
  return randomFunc;
};