#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "../models/product.h"

enum class SortKey;  // forward declaration since it's defined in merge_sort.h

void quickSort(Product arr[], int low, int high, SortKey key);
int partition(Product arr[], int low, int high, SortKey key);
void swap(Product* a, Product* b);

#endif