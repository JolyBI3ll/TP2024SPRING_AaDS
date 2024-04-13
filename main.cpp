//Имеется лог-файл, в котором хранятся пары для N пользователей (Идентификатор пользователя, посещаемость сайта).
//Напишите программу, которая выбирает K пользователей, которые чаще других заходили на сайт, и выводит их в порядке возрастания посещаемости.
//Количество заходов и идентификаторы пользователей не повторяются.
//
//Требования:
//
//Время работы O(N * logK)
//Куча должна быть реализована в виде шаблонного класса.
//Решение должно поддерживать передачу функции сравнения снаружи.
//Куча должна быть динамической.
//Формат ввода
//Сначала вводятся N и K, затем пары (Идентификатор пользователя, посещаемость сайта).
//
//Формат вывода
//Идентификаторы пользователей в порядке возрастания посещаемости.

#include <iostream>
#include <cassert>

struct User {
    int Id;
    int Value;

    friend std::ostream& operator<<(std::ostream& os, const User& user)
    {
        return os << user.Id;;
    }
};

template <class T>
class IsLessByValue{
public:
    IsLessByValue() = default;
    ~IsLessByValue() = default;

    IsLessByValue( IsLessByValue& ) = default;
    IsLessByValue operator=( const IsLessByValue& ) = delete;

    bool operator()( const T& left, const T& right )
    {
        return left.Value < right.Value;
    }
};

template <class T, class IsLess>
class MinHeap {
public:
    MinHeap( IsLess isLess );
    MinHeap( T* array, int arrSize, IsLess isLess );
    ~MinHeap();

    MinHeap( MinHeap& ) = delete;
    MinHeap operator=( const MinHeap& ) = delete;

    void Insert( const T& element );
    T ExtractMin();
    const T& PeekMin() const;
    int Size() const;

private:
    IsLess isLess;
    T* buffer;
    int bufferSize;
    int size;
    void buildHeap();
    void siftDown( int i );
    void siftUp( int i );
    void grow();
};

template<class T, class IsLess>
void MinHeap<T, IsLess>::Insert( const T& element )
{
    if ( size == bufferSize )
    {
        grow();
    }
    buffer[size] = element;
    siftUp( size );
    size++;
}

template<class T, class IsLess>
T MinHeap<T, IsLess>::ExtractMin()
{
    assert( size > 0 );
    T result = buffer[0];
    buffer[0] = buffer[size - 1];
    --size;
    if( size > 0 )
    {
        siftDown( 0 );
    }
    return result;
}

template<class T, class IsLess>
void MinHeap<T, IsLess>::siftUp( int i )
{
    while( i > 0 )
    {
        int parent = ( i - 1 ) / 2;
        if( isLess( buffer[parent], buffer[i] ) )
            return;
        std::swap( buffer[i], buffer[parent] );
        i = parent;
    }
}

template<class T, class IsLess>
const T &MinHeap<T, IsLess>::PeekMin() const
{
    assert( size > 0 );
    return buffer[0];
}

template<class T, class IsLess>
void MinHeap<T, IsLess>::buildHeap()
{
    for( int i = Size() / 2 - 1; i >= 0; --i ) {
        siftDown(i);
    }
}

template<class T, class IsLess>
MinHeap<T, IsLess>::~MinHeap()
{
    delete[] buffer;
}

template<class T, class IsLess>
MinHeap<T, IsLess>::MinHeap(T *array, int arrSize, IsLess isl): isLess( isl ), size ( arrSize ), bufferSize ( arrSize * 2 ), buffer ( array )
{
    buildHeap();
}

template<class T, class IsLess>
MinHeap<T, IsLess>::MinHeap(IsLess isl): isLess( isl ), buffer( nullptr ), size( 0 ), bufferSize( 0 ) {}

template<class T, class IsLess>
int MinHeap<T, IsLess>::Size() const
{
    return size;
}

template<class T, class IsLess>
void MinHeap<T, IsLess>::grow()
{
    int new_buffersize = ( bufferSize == 0 ) ? 1 : bufferSize * 2;
    T* new_buffer = new T[new_buffersize];
    for ( int i = 0; i < bufferSize; ++i )
    {
        new_buffer[i] = buffer[i];
    }
    delete[] buffer;
    buffer = new_buffer;
    bufferSize = new_buffersize;
}

template<class T, class IsLess>
void MinHeap<T, IsLess>:: siftDown( int i )
{
    while( 2 * i + 1 < size )
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int min = i;
        if( left < Size() && isLess( buffer[left], buffer[i] ) )
            min = left;
        if( right < Size() && isLess( buffer[right], buffer[min] ) )
            min = right;
        if( min != i )
        {
            std::swap( buffer[i], buffer[min] );
            i = min;
        }
        else break;
    }
}

int main()
{
    int n = 0, k = 0;
    IsLessByValue<User> isLess;
    MinHeap<User, IsLessByValue<User>> Heap( isLess );
    User user{ 0 , 0 };

    std::cin >> n >> k;
    User* array = new User[n];

    for ( int i = 0; i < n; ++i )
    {
        std::cin >> user.Id >> user.Value;
        array[i] = user;
    }
    for ( int i = 0; i < k; ++i )
    {
        Heap.Insert( array[i] );
    }
    for ( int i = k; i < n; ++i )
    {
        if ( isLess( Heap.PeekMin(), array[i] ) )
        {
            Heap.ExtractMin();
            Heap.Insert( array[i] );
        }
    }
    for (int i = 0; i < k; ++i) {
        std::cout << Heap.ExtractMin() << ' ';
    }
    delete[] array;
    return 0;
}