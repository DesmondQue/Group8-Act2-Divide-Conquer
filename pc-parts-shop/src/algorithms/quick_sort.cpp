#include "quick_sort.h"
#include "merge_sort.h"  // For SortKey enum

void swap(Product* a, Product* b) {
    Product temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Product arr[], int low, int high, SortKey key) {
    Product pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        bool compareResult;
        if (key == SortKey::PRICE) {
            compareResult = arr[j].price <= pivot.price;
        } else { // SortKey::QUANTITY
            compareResult = arr[j].quantity <= pivot.quantity;
        }

        if (compareResult) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(Product arr[], int low, int high, SortKey key) {
    if (low < high) {
        int pi = partition(arr, low, high, key);
        quickSort(arr, low, pi - 1, key);
        quickSort(arr, pi + 1, high, key);
    }
}