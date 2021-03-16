#include <iostream>
#include <cstring>

#define INVALID_DATA -1

int next_pos(const bool *round, const int &size, const int &step, const int &pos) {
    int res_pos = pos;
    for (int i = 0; i < step; ) {
        ++res_pos;

        if (res_pos == size) {
            res_pos = 0;
        }

        if (round[res_pos]) {
            ++i;
        }
    }

    return res_pos;
}

int countdown(const int &size, const int &step) {
    if (size == 0 || step <= 0) {
        return INVALID_DATA;
    }

    if (size == 1) {
        return 1;
    }

    bool *round = new bool[size];
    memset(round, true, sizeof(bool) * size);

    int end = size;
    int i = -1;
    while (end != 0) {
        i = next_pos(round, size, step, i);
        round[i] = false;
        --end;
    }

    delete [] round;
    return i + 1;
}

int main() {
    int N;
    int k;
    std::cin >> N;
    std::cin >> k;
    std::cout << countdown(N, k) << std::endl;
    return 0;
}
