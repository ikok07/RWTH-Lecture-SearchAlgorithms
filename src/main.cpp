#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "bintree.hpp"
#include "student.hpp"

#define RANDOM_SEED 10

static std::mt19937 rng(RANDOM_SEED); // seeded once
std::uniform_int_distribution<int> dist(50, 200);

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

template <typename T> void print_vect(std::vector<T> &vect) {
  for (auto el : vect) {
    std::cout << el;
  }
  std::cout << std::endl << std::endl;
}

std::vector<int> gen_vector(int n) {
  std::vector<int> items(n);
  std::generate(items.begin(), items.end(), [&] { return dist(rng); });

  return items;
}

template <typename T, typename Compare, std::input_iterator It>
void insertion_sort(std::vector<T> &input, It start, It end, Compare compare) {
  int l = std::distance(input.begin(), start);
  int r = std::distance(input.begin(), end) - 1;

  for (int i = l + 1; i <= r; i++) {
    T curr = input[i];
    int j;
    for (j = i - 1; j >= l; j--) {
      int compare_result = compare(curr, input[j]);
      if (compare_result < 0) {
        input[j + 1] = input[j];
      } else {
        break;
      }
    }

    input[j + 1] = curr;
  }
}

template <typename T, typename Compare, std::input_iterator It>
int search(std::vector<T> &input, It start, It end, Compare compare) {
  int l = std::distance(input.begin(), start);
  int r = std::distance(input.begin() + 1, end);

  while (l <= r) {
    int key = (l + r) / 2;
    int compare_result = compare(input[key]);
    if (compare_result == 0) {
      return key;
    }

    if (compare_result < 0) {
      r = key - 1;
    } else if (compare_result > 0) {
      l = key + 1;
    }
  }

  return -1;
}

int main(void) {
  auto items = std::vector<Student>(5);
  std::generate(items.begin(), items.end(), []() -> Student {
    auto student = Student(dist(rng), "TEST");
    return student;
  });

  insertion_sort(items, items.begin(), items.end(), [](Student a, Student b)
  {
    if (a.id == b.id) {
      return 0;
    }
    if (a.id < b.id) {
      return -1;
    }
    return 1;
  });

  BTree<Student> *tree = nullptr;
  for (size_t i = 0; i < items.size(); i++) {
    if (!tree) {
      tree = new BTree<Student>(&(items[i]));
    } else {
      tree->insert(&(items[i]));
    }
  }

  // print_vect(items);

  int search_value = 64;
  // int result_idx = search(items, items.begin(), items.end(),
  //                     [search_value](Student object) -> int {
  //                       if (object.id == search_value) {
  //                         return 0;
  //                       } else if (object.id > search_value) {
  //                         return -1;
  //                       }
  //                       return 1;
  //                     });
  // std::cout << items[result_idx].id << std::endl;

  Student *result = tree->search([search_value](auto student) {
      if (search_value == student->id) return 0;
      if (search_value < student->id) return -1;
      return 1;
  });
  if (result) std::cout << result->id << std::endl;

  return 0;
}