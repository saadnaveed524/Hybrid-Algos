# Hybrid Sorting Algorithm: Merge-Quick Sort

This repository contains the implementation and performance analysis of a hybrid sorting algorithm that combines **Merge Sort** and **Quick Sort** using C++. The goal of this hybrid algorithm is to optimize sorting performance by switching between the two algorithms based on the characteristics of the data.

## Overview

The hybrid Merge-Quick Sort algorithm adapts between Quick Sort and Merge Sort as follows:
- **Quick Sort** is used for partitioning sections when they are relatively small and can benefit from in-place sorting.
- **Merge Sort** is used for larger sections where stable and predictable O(n log n) performance is required, especially in cases of large or nearly sorted data.

## Problem Definition

Sorting large datasets efficiently is crucial in many applications. Pure Quick Sort or Merge Sort may not always yield optimal performance due to:
- Data size and distribution (e.g., nearly sorted data or highly skewed data)
- Memory constraints

This hybrid algorithm provides a balance, dynamically choosing the optimal approach to improve overall efficiency.

## Algorithm Analysis

### Merge Sort
- **Strengths**: Stable and provides consistent O(n log n) time complexity.
- **Weaknesses**: Requires extra memory, which may be limiting in certain environments.

### Quick Sort
- **Strengths**: Fast in-place sorting with an average time complexity of O(n log n).
- **Weaknesses**: Has a worst-case complexity of O(n²), especially with already sorted or highly skewed data.

### Hybrid Approach

The hybrid algorithm uses:
- **Adaptive Switching**: Based on data size, switching between Merge Sort and Quick Sort.
- **Efficient Partitioning**: Small segments are sorted in-place using Quick Sort, while large segments utilize Merge Sort for consistency.

## Code Implementation

```cpp
#include <iostream>
#include <vector>

const int THRESHOLD = 10;

// Insertion Sort for small segments
void insertionSort(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Partition function for Quick Sort
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Hybrid Sort function
void hybridSort(std::vector<int>& arr, int low, int high) {
    if (high - low + 1 <= THRESHOLD) {
        // Use insertion sort for small segments
        insertionSort(arr, low, high);
    } else {
        // Use Quick Sort partitioning
        int pivot = partition(arr, low, high);
        hybridSort(arr, low, pivot - 1);
        hybridSort(arr, pivot + 1, high);

        // Merge step similar to Merge Sort for larger segments
        std::vector<int> left(arr.begin() + low, arr.begin() + pivot + 1);
        std::vector<int> right(arr.begin() + pivot + 1, arr.begin() + high + 1);

        int i = 0, j = 0, k = low;
        while (i < left.size() && j < right.size()) {
            if (left[i] < right[j]) {
                arr[k++] = left[i++];
            } else {
                arr[k++] = right[j++];
            }
        }
        while (i < left.size()) arr[k++] = left[i++];
        while (j < right.size()) arr[k++] = right[j++];
    }
}

int main() {
    std::vector<int> arr = {24, 97, 40, 67, 88, 85, 15, 92, 20, 65};

    hybridSort(arr, 0, arr.size() - 1);

    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
