//7_3. Binary MSD для long long.
//Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 10^6. Отсортировать массив методом MSD по битам (бинарный QuickSort).

#include <iostream>
#include <cassert>

#define BITS_PER_WORD 63

void BinaryMSD(unsigned long long *a, int first, int last, int w) {
    int i = first;
    int j = last;
    if (last <= first || w < 0)
        return;
    while(j != i) {
        while ((a[i] & ((unsigned long long)1 << w)) == 0 && (i < j))
            ++i;
        while ((a[j] & ((unsigned long long)1 << w)) != 0 && (j > i))
            --j;
        std::swap(a[i], a[j]);
    }
    if ((a[last] & ((unsigned long long)1 << w)) == 0)
        ++j;
    BinaryMSD(a, first, j - 1, w - 1);
    BinaryMSD(a, j, last, w - 1);
}

int main() {
    int n;
    std::cin >> n;
    assert(n > 0);
    unsigned long long* arr = new unsigned long long [n];
    for ( int i = 0; i < n; ++i )
    {
        std::cin >> arr[i];
    }
    BinaryMSD( arr, 0, n - 1, BITS_PER_WORD );
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << ' ';
    }
    delete[] arr;
    return 0;
}