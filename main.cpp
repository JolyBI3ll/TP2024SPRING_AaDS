//2_2. Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения массива строго возрастают, а на интервале [m, n-1] строго убывают. Найти m за O(log m).
//Требования:  Время работы O(log m). Внимание! В этой задаче сначала нужно определить диапазон для бинарного поиска размером порядка m с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.
//
//2 ≤ n ≤ 10000.

#include <iostream>
#include <cassert>

//Фукнция решения задачи, которая сначала ищет интервал, в котором находится точка m, экспоненциальным поиском, а затем бинарным поиском в пределах найденного интервала выполняет поиск точки m
int exponentialAndBinarySearch( int* array, int size ) {
    assert( size > 0 );
    int i = 1;

    while (i < size && array[i] <= array[i + 1]) {
        i *= 2;
    }

    int leftborder = i / 2;
    int rightborder = std::min(i, size - 1);

    while (leftborder < rightborder) { // Выполняем бинарный поиск для найденного интеравала
        int mid = (leftborder + rightborder) / 2;
        if (array[mid] > array[mid + 1] and array[mid] > array[mid - 1]) {
            return mid;
        }
        if ( array[mid] < array[mid + 1] ) {
            leftborder = mid + 1;
        }
        else {
            rightborder = mid - 1;
        }
    }

    return leftborder;
}

int main() {
    int n = 0;
    std::cin >> n;
    int* A = new int[n];
    for ( int i = 0; i < n; ++i ) {
        std::cin >> A[i];
    }
    std::cout << exponentialAndBinarySearch( A, n );
    delete[] A;
    return 0;
}