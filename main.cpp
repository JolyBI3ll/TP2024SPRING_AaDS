//Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью динамического буфера.
//
//Обрабатывать команды push back и pop front.
//
//Формат ввода
//В первой строке количество команд n. n ≤ 1000000.
//
//Каждая команда задаётся как 2 целых числа: a b.
//
//a = 2 - pop front
//a = 3 - push back
//
//Если дана команда pop front, то число b - ожидаемое значение. Если команда pop front вызвана для пустой структуры данных, то ожидается “-1”.
//
//Формат вывода
//Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

#include <iostream>
#include <cassert>

//Реализация структуры данных "Стек" на основе динамического буффера
class Stack {
public:
    Stack();
    explicit Stack( int size );
    ~Stack();

    Stack( Stack& ) = delete;
    Stack operator=( const Stack& ) = delete;

    void Push( int element );
    int Pop();

    bool IsEmpty() const;

private:
    int buffersize;
    int top;
    int* buffer;
    void grow();
};

Stack::Stack(): top( -1 ), buffersize( 0 ), buffer( nullptr ) {}

Stack::Stack( int size ): buffersize( size ), top( buffersize - 1 ) {
    buffer = new int [buffersize];
}

Stack::~Stack() {
    delete [] buffer;
}

//Функция расширения буффера
void Stack::grow() {
    int new_buffersize = ( buffersize == 0 ) ? 1 : buffersize * 2;
    int* new_buffer = new int[new_buffersize];
    for ( int i = 0; i < buffersize; ++i ) {
        new_buffer[i] = buffer[i];
    }
    delete[] buffer;
    buffer = new_buffer;
    buffersize = new_buffersize;
}

void Stack::Push( int element ) {
    if ( top == buffersize - 1 ) {
        this->grow();
    }
    buffer[++top] = element;
}

int Stack::Pop() {
    assert ( top != -1 );
    return buffer[top--];
}

bool Stack::IsEmpty() const {
    return top == -1;
}

//Реализация очереди на основе двух стеков
class Queue{
public:
    Queue() = default;
    ~Queue();

    Queue(Queue&) = delete;
    Queue operator=( const Queue& ) = delete;

    void Enqueue( int data );
    int Dequeue();

private:
    Stack stIn;
    Stack stOut;
};

Queue::~Queue() {
    while ( !stIn.IsEmpty() || !stOut.IsEmpty() ) {
        Dequeue();
    }
}

void Queue::Enqueue( int data ) {
    stIn.Push( data );
}

int Queue::Dequeue() {
    if ( stIn.IsEmpty() && stOut.IsEmpty() ) {
        return -1;
    }
    if ( stOut.IsEmpty() ) {
        while ( !stIn.IsEmpty() ) {
            stOut.Push( stIn.Pop() );
        }
    }
    return stOut.Pop();
}

int main() {
    Queue intQueue;
    int n = 0;
    std::cin >> n;
    bool res = true;
    for (int i = 0; i < n; ++i) {
        int command = 0;
        int data = 0;
        std::cin >> command >> data;
        switch ( command ) {
            case 2:
                if ( intQueue.Dequeue() != data ) {
                    res = false;
                }
                break;
            case 3:
                intQueue.Enqueue( data );
                break;
            default:
                assert( false );
        }
    }
    std::cout << ( res ? "YES" : "NO" ) << std::endl;
    return 0;
}
