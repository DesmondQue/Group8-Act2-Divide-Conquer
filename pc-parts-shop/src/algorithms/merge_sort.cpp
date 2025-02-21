#include "merge_sort.h"

void merge(Product arr[], int left, int mid, int right, SortKey key) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Product* L = new Product[n1];
    Product* R = new Product[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        bool compareResult;
        if (key == SortKey::PRICE) {
            compareResult = L[i].price <= R[j].price;
        } else { // SortKey::QUANTITY
            compareResult = L[i].quantity <= R[j].quantity;
        }

        if (compareResult) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(Product arr[], int left, int right, SortKey key) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, key);
        mergeSort(arr, mid + 1, right, key);
        merge(arr, left, mid, right, key);
    }
}