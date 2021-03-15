#include <iostream>
#include <unistd.h>

#define SEARCH_ERROR -1
#define INTERSECTION_ERROR -1

int binary_search(const int *arr, const int &beg_init, const int &size, const int &key) {
    if (size == 0) {
        return -1;
    }

    int beg = beg_init;
    int end = size;

    while (end - beg != 1) {
        int mid = (beg + end) / 2;
        if (arr[mid] > key) {
            end = mid;
        } else {
            beg = mid;
        }
    }

    if (arr[beg] == key) {
        return beg;
    } else {
        return -1;
    }
}

int exp_border(const int *arr, int beg, int size, int key) {
    if (size == 0) {
        return -1;
    }

    int border = beg;
    if (arr[border] > key) {
        return border;
    }

    for ( ; border < size && arr[border] < key; border *= 2);

    return (border > size ? size : border + 1);
}

int intersection(const int *arr1,
                 const int &size1,
                 const int *arr2,
                 const int &size2,
                 int *inter,
                 const int &size_inter) {
    if (size1 < 0 || size2 < 0 || size_inter < 0) {
        return -1;
    }

    int inter_index = 0;
    int border = 1;
    for (int i = 0; i < size2; ++i) {
        int elem_index_in_1_border = exp_border(arr1, border, size1, arr2[i]);
        int elem_index_in_1 = binary_search(arr1,
                                            elem_index_in_1_border / 2,
                                            elem_index_in_1_border,
                                            arr2[i]);
        if (elem_index_in_1 != -1) {
            inter[inter_index] = arr2[i];
            ++inter_index;
            if (inter_index > size_inter) {
                return inter_index;
            }
        }

        border = elem_index_in_1_border;
    }

    return inter_index;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5, 9, 12};
    int size1 = 7;
    int arr2[] = {1, 3, 5, 12};
    int size2 = 4;
    int inter[size2];

    int i = intersection(arr1, size1, arr2, size2, inter, size2);
    for (int j = 0; j < i; ++j) {
        std::cout << inter[j] << std::endl;
    }

    return 0;
}

