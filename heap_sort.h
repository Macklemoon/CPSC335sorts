#ifndef heap_sort_h
#define heap_sort_h

#include "utils.h"
#include "array.h"

template <typename T>
class heap {
public:
  static void sort(T* pq, size_t l, const comparator<T>& comp=fwd_comparator<T>()) {
    for(size_t k = l / 2; k >= 1; --k) {
      sink(pq, k, l, comp);
    }

    size_t n = l;
    while(n > 1) {
      exchange(pq, 1, n--);
      sink(pq, 1, n, comp);
    }
  }

  static void sink(T* pq, size_t k, size_t l, const comparator<T>& comp) {
    while(2 * k <= l) {
      size_t j = 2 * k;
      if(j < l && less(pq, j, j + 1, comp)) {
        ++j;
      }
      if(!less(pq, k, j, comp)) {
        break;
      }

      exchange(pq, k, j);
      k = j;
    }
  }
private:
  // Via professor's code. . .
  static bool less(T* pq, size_t i, size_t j, const comparator<T>& comp) {
    return ::less(pq[i - 1], pq[j - 1], comp);
  }

  static void exchange(T* pq, size_t i, size_t j) {
    T temp = std::move(pq[i - 1]);
    pq[i - 1] = std::move(pq[j - 1]);
    pq[j - 1] = std::move(temp);
  }
};

//===============================================================


template <typename T>
class max_pq_heap {
public:
  max_pq_heap() : max_pq_heap(MIN_CAPACITY) {}
  max_pq_heap(size_t cap) : pq_(cap) {
    pq_.push_back(NULL);
  }

  void printPQ() {
    size_t n = size();
    for(size_t i = 0; i < n; ++i) {
      std::cout << pq_[i] << " ";
    }
    std::cout << '\n';
  }



  bool isEmpty() { return pq_.empty(); }
  size_t size() { return pq_.size(); }

  void insert(T val) {
    pq_.push_back(val);
    swim(size() - 1);

    assert(isMaxHeap());
  }

  T delMax() {
    // if empty throw assertion.
    assert(size() != 0);

    T maximum = pq_[1];
    size_t n = size();

    exchange(1, n - 1);
    //printPQ();

    pq_[n - 1] = T();
    pq_.pop_back();

    //printPQ();

    sink(1);
    // printPQ();
    assert(isMaxHeap());

    return maximum;
  }

private:
  array_<T> pq_;
  static const size_t MIN_CAPACITY = 10;

  void swim(size_t k) {
    while(k > 1 && less(k / 2, k)) {
      exchange(k, k / 2);
      k = k / 2;
    }
  }

  void sink(size_t k) {
    size_t n = size();
    while(2 * k <= n) {
      size_t j = 2 * k;

      if(j < n && less(j, j + 1)) { ++j; }
      if(!less(k, j)) { break; }

      exchange(k, j);
      k = j;
    }
  }

/*
  // Basic overloaded less function.
  bool less(size_t i, size_t j, const comparator<T>& comp) {
    return ::less(pq_[i], pq_[j], comp);
  }
*/
  // Basic overloaded less function.
  bool less(size_t i, size_t j) {
    return ::less(pq_[i], pq_[j]);
  }
  // Basic exchange function.
  void exchange(size_t i, size_t j) {
    T temp = pq_[i];
    pq_[i] = pq_[j];
    pq_[j] = temp;
  }

  // assertions.
  bool isMaxHeap() {
    for (int i = 1; i < size(); ++i) {
        if (pq_[i] == NULL) {
          return false;
        }
    }

    if (pq_[0] != NULL) {
      return false;
    }
    return isMaxHeapOrdered(1);
  }

  bool isMaxHeapOrdered(int k) {
      if (k > size() - 1) {
        return true;
      }

      int left = 2 * k;
      int right = (2 * k) + 1;
      if (left  <= size() - 1 && less(k, left)) { return false; }
      if (right <= size() - 1 && less(k, right)) { return false; }
      return isMaxHeapOrdered(left) && isMaxHeapOrdered(right);
  }
};

#endif /* selection_sort_h */
