//Дано множество целых чисел из [0..10^9] размера n.
//Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
//10%  перцентиль
//        медиана
//90%  перцентиль
//
//Требования: к дополнительной памяти: O(n).
//Среднее время работы: O(n)
//Должна быть отдельно выделенная функция partition.
//Рекурсия запрещена.
//Решение должно поддерживать передачу функции сравнения снаружи.
//
//6_4. Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.


#include <iostream>
#include <cassert>

template <class T>
class IsLessByValue{
public:
    IsLessByValue() = default;
    ~IsLessByValue() = default;

    IsLessByValue( IsLessByValue& ) = default;
    IsLessByValue operator=( const IsLessByValue& ) = delete;

    bool operator()( const T& left, const T& right )
    {
        return left < right;
    }
};

template <class T, class IsLess>
int Partition( T* arr, int n, IsLess isless )
{
    if ( n <= 1 )
        return 0;

    srand(time(0));
    int pivot = std::rand() % n;
    std::swap(arr[pivot], arr[0]);

    int i = n - 1;
    for (int j = n - 1; j > 0; --j) {
        if( !isless( arr[j], arr[0] ) )
        {
            std::swap( arr[i--], arr[j] );
        }
    }
    std::swap( arr[i], arr[0] );
    return i;
}

template <class T, class IsLess>
int FindKStat( T* array, int n, int k, IsLess isless )
{
    assert( k >= 0 && k < n );
    int left = 0;
    int right = n - 1;

    while ( true )
    {
        int pivotPos = Partition(array + left, right - left + 1, isless);
        if ( pivotPos == k )
            return array[left + k];
        else if ( k < pivotPos )
            right = left + pivotPos - 1;
        else
        {
            left = left + pivotPos + 1;
            k -= pivotPos + 1;
        }
    }
}

int main() {
    int n = 0;
    std::cin >> n;
    IsLessByValue<int> isLess;
    int* array = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }
    std::cout << FindKStat(array, n, n / 10, isLess) << std::endl;
    std::cout << FindKStat(array, n, n / 2, isLess) << std::endl;
    std::cout << FindKStat(array, n, (n * 9) / 10, isLess);
    delete[] array;
    return 0;
}
