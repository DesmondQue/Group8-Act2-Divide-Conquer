#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "../models/product.h"

enum class SortKey {
    PRICE,
    QUANTITY
};

void merge(Product arr[], int left, int mid, int right, SortKey key);
void mergeSort(Product arr[], int left, int right, SortKey key);

#endif 