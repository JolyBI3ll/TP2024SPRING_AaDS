//На числовой прямой окрасили N отрезков.
//Известны координаты левого и правого концов каждого отрезка [Li, Ri]. Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
//N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 109].
//
//Формат ввода
//В первой строке записано количество отрезков.
//В каждой последующей строке через пробел записаны координаты левого и правого концов отрезка.
//
//Формат вывода
//Выведите целое число — длину окрашенной в один слой части.

#include <iostream>

struct Point{
    int x;
    int delta;
    Point(): x( 0 ), delta( 0 ) {}

};

template<class T>
class IsLessByX {
public:
    IsLessByX() = default;
    ~IsLessByX() = default;

    IsLessByX( IsLessByX& ) = default;
    IsLessByX operator=( const IsLessByX& ) = delete;

    bool operator()( const T& left, const T& right )
    {
        return left.x < right.x || (left.x == right.x && left.delta < right.delta);
    }
};

template<class T, class IsLess>
void merge( T* points, int left, int mid, int right, IsLess comparator )
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Point* L = new Point[n1];
    Point* R = new Point[n2];

    for ( int i = 0; i < n1; i++ )
    {
        L[i] = points[left + i];
    }
    for ( int j = 0; j < n2; j++ )
    {
        R[j] = points[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while ( i < n1 && j < n2 )
    {
        if ( comparator( L[i], R[j] ) )
        {
            points[k++] = L[i++];
        } else
        {
            points[k++] = R[j++];
        }
    }

    while ( i < n1 )
    {
        points[k++] = L[i++];
    }
    while ( j < n2 )
    {
        points[k++] = R[j++];
    }
    delete[] L;
    delete[] R;
}

template<class T, class IsLess>
void mergeSort( T* points, int n, IsLess comparator)
{
    for ( int width = 1; width < n; width = 2 * width )
    {
        for ( int i = 0; i < n; i = i + 2 * width )
        {
            int left = i;
            int right = std::min( i + 2 * width - 1, n - 1 );
            int mid = std::min( i + width - 1, right );
            merge( points, left, mid, right, comparator );
        }
    }
}

template<class T>
int calculateLength( T* points, int size )
{
    int sum = 0;
    int layers = 0;
    int prev = points[0].x;

    for ( int i = 0; i < size; i++ )
    {
        if ( layers == 1 )
        {
            sum += points[i].x - prev;
        }
        layers += points[i].delta;
        prev = points[i].x;
    }
    return sum;
}

int main()
{
    int n = 0;
    std::cin >> n;
    IsLessByX<Point> compareByX;
    Point* points = new Point[2 * n];

    for ( int i = 0; i < 2 * n; i += 2 )
    {
        std::cin >> points[i].x >> points[i+1].x;
        points[i].delta = 1;
        points[i+1].delta = -1;
    }

    mergeSort( points, 2 * n, compareByX );

    std::cout << calculateLength( points, 2 * n ) << std::endl;
    delete[] points;
    return 0;
}
