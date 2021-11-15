#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <span>

template <typename T, class _Compare>
void _mergesort_recursive_serial(std::span<T> &x, size_t left, size_t right,
                                 _Compare __compare) {
  if (left < right) {
    if ((right - left) >= 32) {
      size_t mid = (left + right) / 2;
      _mergesort_recursive_serial(x, left, mid, __compare);
      _mergesort_recursive_serial(x, mid + 1, right, __compare);
      std::inplace_merge(x.begin() + left, x.begin() + mid + 1,
                         x.begin() + right + 1, __compare);
    } else {
      std::sort(x.begin() + left, x.begin() + right + 1, __compare);
    }
  }
}

template <typename T, class _Compare>
void _mergesort_recursive_taskgroup(std::span<T> &x, size_t left,
                                    size_t right, _Compare __compare) {
  if (left < right) {
    if ((right - left) >= 32) {
      size_t mid = (left + right) / 2;

#pragma omp taskgroup
      {
#pragma omp task shared(x)
        _mergesort_recursive_taskgroup(x, left, mid, __compare);
        _mergesort_recursive_taskgroup(x, mid + 1, right, __compare);
      }
      std::inplace_merge(x.begin() + left, x.begin() + mid + 1,
                         x.begin() + right + 1, __compare);
    } else {
      std::sort(x.begin() + left, x.begin() + right + 1, __compare);
    }
  }
}

template <typename T, class _Compare>
void _mergesort_recursive_untied(std::span<T> &x, size_t left, size_t right,
                                 _Compare __compare) {
  if (left < right) {
    if ((right - left) >= 32) {
      size_t mid = (left + right) / 2;

#pragma omp taskgroup
      {
#pragma omp task shared(x) untied if (right - left >= (1 << 14))
        _mergesort_recursive_untied(x, left, mid, __compare);
        _mergesort_recursive_untied(x, mid + 1, right, __compare);
      }
      std::inplace_merge(x.begin() + left, x.begin() + mid + 1,
                         x.begin() + right + 1, __compare);
    } else {
      std::sort(x.begin() + left, x.begin() + right + 1, __compare);
    }
  }
}

template <typename T, class _Compare>
void _mergesort_recursive_taskyield(std::span<T> x, size_t left,
                                    size_t right, _Compare __compare) {
  if (left < right) {
    if ((right - left) >= 32) {
      size_t mid = (left + right) / 2;

#pragma omp taskgroup
      {
#pragma omp task shared(x) untied if (right - left >= (1 << 14))
        _mergesort_recursive_taskyield(x, left, mid, __compare);
#pragma omp task shared(x) untied if (right - left >= (1 << 14))
        _mergesort_recursive_taskyield(x, mid + 1, right, __compare);
#pragma omp taskyield
      }
      std::inplace_merge(x.begin() + left, x.begin() + mid + 1,
                         x.begin() + right + 1, __compare);
    } else {
      std::sort(x.begin() + left, x.begin() + right + 1, __compare);
    }
  }
}

template <typename T, class _Compare = std::less<T>>
void merge_sort(std::span<T> x, std::string method,
                _Compare __compare = _Compare()) {

  if (method.compare("taskgroup") == 0) {
#pragma omp parallel
    {
#pragma omp single
      { _mergesort_recursive_taskgroup(x, 0, x.size() - 1, __compare); }
    }
  }

  else if (method.compare("untied") == 0) {
#pragma omp parallel
    {
#pragma omp single
      { _mergesort_recursive_untied(x, 0, x.size() - 1, __compare); }
    }
  }

  else if (method.compare("taskyield") == 0) {
#pragma omp parallel
    {
#pragma omp single
      { _mergesort_recursive_taskyield(x, 0, x.size() - 1, __compare); }
    }
  }

  else if (method.compare("serial") == 0) {
    _mergesort_recursive_serial(x, 0, x.size() - 1, __compare);
  }

  // Bad method specified by user
  else {
    std::cerr << "Mergesort varient requested by the user (" << method
              << ") wasn't found!" << std::endl;
    exit(EXIT_FAILURE);
  }
}