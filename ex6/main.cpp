#include <iostream>

template<class T>
bool isLessDefault(const T& l, const T &r) {
    return l < r;
}

template<class T>
int FindPivotPos(const T *a, int n, bool (*isLess)(const T &l, const T &r)) {
    T beg = a[0];
    T mid = a[n / 2];
    T end = a[n - 1];

    if (isLess(beg, end)) {
        if (isLess(mid, end)) {
            return (isLess(beg, mid) ? n / 2 : 0);
        }
        return n - 1;
    }

    if (!isLess(mid, end)) {
        return (isLess(mid, beg) ? n / 2: 0);
    }
    return n - 1;
}

template<class T>
int Partition(T *a, int n, bool (*isLess)(const T &l, const T &r)) {
    if (n <= 1) {
        return 0;
    }

    int pivotPos = FindPivotPos(a, n, isLess);
    std::swap(a[n - 1], a[pivotPos]);
    T pivot = a[n - 1];
    int i = 0;
    int j = 0;
    int k = 0;
    while (k < n - 1) {
        if (!isLess(a[k], pivot)) {
            ++j;
        } else {
            std::swap(a[i], a[k]);
            ++i;
        }
        ++k;
    }
    std::swap(a[i], a[n - 1]);
    return i;
}

template<class T>
T FindKStat(T *a, int n, int k, bool (*isLess)(const T &l, const T &r)=isLessDefault) {
    for (int pivotPos = Partition(a, n, isLess); pivotPos != k; pivotPos = Partition(a, n, isLess)) {
        if (!isLess(pivotPos, k)) {
            n = pivotPos;
        } else {
            pivotPos += (pivotPos == 0 ? 1 : 0);
            a += pivotPos;
            k -= pivotPos;
            n -= pivotPos;
        }
    }

    return a[k];
}

int main() {
    int n;
    std::cin >> n;
    int k;
    std::cin >> k;

    int *arr = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    std::cout << FindKStat(arr, n, k) << std::endl;

    delete [] arr;
}
