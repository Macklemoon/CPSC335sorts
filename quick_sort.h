#include "utils.h"
template <typename T>
class quick_sort {
public:
  // Public helper funct.
  static void sort(T* arr, size_t n, const comparator<T>& comp=fwd_comparator<T>()) {
    sort(arr, 0, n - 1, comp);
  }
private:
  static const int CUTOFF = 7;

  static void sort(T* arr, size_t low, size_t high, const comparator<T>& comp) {
    /*
    if(high <= low) {
      return;
    }
    */
    insertion_sort<T> insert;
    if(high <= (low + CUTOFF - 1)) {
        insert.sort(arr, low, high, comp);
        return;
    }
    size_t j = partition(arr, low, high, comp);

    if(j == 0) {
      sort(arr, low, 0, comp);
    } else {
      sort(arr, low, j - 1, comp);
    }

    sort(arr, j + 1, high, comp);
  }

  static size_t partition(T* arr, size_t low, size_t high, const comparator<T>& comp) {
    size_t i = low;
    size_t j = high + 1;

    while(true) {
      while(less(arr[++i], arr[low], comp)) {
        if(i == high) { break; }
      }

      while(less(arr[low], arr[--j], comp)) {
        if(j == low) { break; }
      }

      if(i >= j) { break; }
      exchange(arr, i, j);
    }

    exchange(arr, low, j);

    return j;
  }
};

template <typename T>
class quick_sort_3way {
public:
  // Public helper funct.
  static void sort(T* arr, size_t n, const comparator<T>& comp=fwd_comparator<T>()) {
    sort(arr, 0, n - 1, comp);
  }
private:
  static const int CUTOFF = 10;

  static void sort(T* arr, size_t low, size_t high, const comparator<T>& comp) {
    /* WORKS EVEN WITHOUT CUTOFF
    if(high <= low) {
      return;
    }
    */
    insertion_sort<T> insert;
    if(high <= (low + CUTOFF - 1)) {
        insert.sort(arr, low, high, comp);
        return;
    }

    size_t lt = low;
    size_t i = low + 1;
    size_t gt = high;

    // Main difference in original implementation; a flag checks if the case where a desync occurs.
    bool flag = false;
    // Indirect pointer allows for easier movement in the array.
    T* val;
    val = arr + low;
    
    // (val == arr[lt] && val > arr[i]), move the pointer to where arr[i] is post swap?
    //std::cout << "\n\n==========NEW LOOP=============\n\n" << low << " " << high << "\n\n";
    int cmp = 0;

    while(i <= gt) {
      cmp = compare(arr[i], *val, comp);
      //std::cout << "Value and cmp eval: " << arr[i] << " " << val << " " << cmp << "\n";

      // In the case that the value = current lowest bound AND clause 1
      // of if statement procs, a desync throughout this iteration occurs
      if(*val == arr[lt] && arr[i] < *val) {
        flag = true;
      }

      if(cmp < 0) {
        exchange(arr, lt++, i++);
      } else if(cmp > 0) {
        exchange(arr, i, gt);
        if(gt != 0) {
          --gt;
        }
      } else {
        ++i;
      }

      // Resets pointer if ever desynchronized from lt
      if(flag) {
        val = arr + i - 1;
        flag = false;
      }
    }

    if(lt == 0) {
      sort(arr, low, 0, comp);
    } else {
      sort(arr, low, lt - 1, comp);
    }

    // fancy: sort(arr, low, (lt == 0 ? 0 : lt - 1), comp);
    sort(arr, gt + 1, high, comp);
  }
};
