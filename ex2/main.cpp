#include <iostream>

#define NOT_FOUND -1
#define EMPTY_ARRAY -1

int binary_search(const int *arr, const int &beg_init, const int &end_init, const int &key) {
    if (end_init == 0) {
        return NOT_FOUND;
    }

    int beg = beg_init;
    int end = end_init;

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
        return NOT_FOUND;
    }
}

int exp_border(const int *arr, const int &beg, const int &size, const int &key) {
    if (size == 0) {
        return EMPTY_ARRAY;
    }

    if (size == beg) {
        return size;
    }

    int border = beg;
    if (arr[border] > key) {
        return border;
    }

    for ( ; border < size && arr[border] < key; border *= 2);
    return (border >= size ? size : border + 1);
}

int intersection(const int *arr1,
                 const int &size1,
                 const int *arr2,
                 const int &size2,
                 int *inter,
                 const int &size_inter) {
    if (size1 <= 0 || size2 <= 0 || size_inter < 0) {
        return NOT_FOUND;
    }

    int border = 1;
    int index_inter = 0;
    for (int i = 0; i < size2; ++i) {
        border = exp_border(arr1, border, size1, arr2[i]);
        int index_in_first_arr = binary_search(arr1, border / 2, border, arr2[i]);

        if (index_in_first_arr != NOT_FOUND) {
            inter[index_inter++] = arr2[i];
            if (index_inter == size_inter) {
                return index_inter;
            }
        }
    }

    return index_inter;
}

int main() {
    int size1;
    std::cin >> size1;
    int size2;
    std::cin >> size2;

    int *arr1 = new int[size1];
    for (int i = 0; i < size1; ++i) {
        std::cin >> arr1[i];
    }

    int *arr2 = new int[size2];
    for (int i = 0; i < size2; ++i) {
        std::cin >> arr2[i];
    }

    int *inter = new int[size2];

    int i = intersection(arr1, size1, arr2, size2, inter, size2);
    for (int j = 0; j < i; ++j) {
        std::cout << inter[j] << ' ';
    }
    std::cout << '\n';

    delete [] inter;
    delete [] arr2;
    delete [] arr1;
    return 0;
}

