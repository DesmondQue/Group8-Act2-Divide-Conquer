#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <vector>
#include "product.h"

// Function to perform Quick Sort on a vector of products
void quickSort(std::vector<Product>& products, int low, int high);

// Function to partition the vector for Quick Sort
int partition(std::vector<Product>& products, int low, int high);

#endif // QUICK_SORT_H