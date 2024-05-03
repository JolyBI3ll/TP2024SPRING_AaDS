//Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
//Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера. Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
//Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
//
//Вариант 1. Для разрешения коллизий используйте квадратичное пробирование.
//i-ая проба g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

struct StringHasher {
    unsigned int operator()(const std::string &key) const {
        unsigned int hash = 0;
        for (unsigned int i = 0; i < key.size(); ++i) {
            hash = hash * 137 + key[i];
        }
        return hash;
    }
};


template<class T, class H>
class HashTable {
public:
    HashTable(int initialSize, const H &hasher);

    ~HashTable() = default;

    HashTable(HashTable &) = delete;

    HashTable operator=(const HashTable &) = delete;

    bool Has(const T &key);

    bool Add(const T &key);

    bool Delete(const T &key);

private:
    H hasher;
    unsigned int keysCount;
    unsigned int emptyCount;
    enum CellState {
        Empty,
        Key,
        Deleted
    };

    struct HashTableCell {
        T Key;
        CellState State;

        HashTableCell() : State(Empty) {}

        ~HashTableCell() = default;
    };

    std::vector<HashTableCell> table;

    void growTable();
};

template<class T, class H>
void HashTable<T, H>::growTable() {
    std::vector<HashTableCell> newTable(table.size() * 2);
    for (unsigned int i = 0; i < table.size(); ++i) {
        if (table[i].State == Key) {
            unsigned int hash = hasher(table[i].Key) % newTable.size();
            for (unsigned int j = 0; newTable[hash].State != Empty; ++j) {
                hash = (hash + j) % newTable.size();
            }
            newTable[hash] = table[i];
        }
    }
    emptyCount = newTable.size() - keysCount;
    table = std::move(newTable);
}

template<class T, class H>
bool HashTable<T, H>::Delete(const T &key) {
    unsigned int hash = hasher(key) % table.size();
    for (unsigned int i = 0; i < table.size(); ++i) {
        if (table[hash].State == Empty) {
            return false;
        } else if (table[hash].State == Key and table[hash].Key == key) {
            table[hash].State = Deleted;
            --keysCount;
            return true;
        }
        hash = (hash + i) % table.size();
    }
    return false;
}

template<class T, class H>
bool HashTable<T, H>::Add(const T &key) {
    unsigned int hash = hasher(key) % table.size();
    unsigned int firstDeleted = -1;
    for (unsigned int i = 0; i < table.size(); ++i) {
        if (table[hash].State == Deleted and firstDeleted == -1) {
            firstDeleted = hash;
        } else if (table[hash].State == Key and table[hash].Key == key) {
            return false;
        } else if (table[hash].State == Empty) {
            if (firstDeleted == -1) {
                table[hash].Key = key;
                table[hash].State = Key;
                ++keysCount;
                --emptyCount;
                if (emptyCount <= (table.size() * 1) / 4) {
                    growTable();
                }
                return true;
            } else {
                table[firstDeleted].Key = key;
                table[firstDeleted].State = Key;
                keysCount++;
                emptyCount--;
                if (emptyCount <= (table.size() * 1) / 4) {
                    growTable();
                }
                return true;
            }
        }
        hash = (hash + i) % table.size();
    }
    return true;
}

template<class T, class H>
bool HashTable<T, H>::Has(const T &key) {
    unsigned int hash = hasher(key) % table.size();
    for (unsigned int i = 0; i < table.size(); ++i) {
        if (table[hash].State == Empty) {
            return false;
        } else if (table[hash].State == Key and table[hash].Key == key) {
            return true;
        }
        hash = (hash + i) % table.size();
    }
    return false;
}

template<class T, class H>
HashTable<T, H>::HashTable(int initialSize, const H &_hasher) :
        hasher(_hasher),
        table(initialSize),
        emptyCount(initialSize),
        keysCount(0) {}

int main() {
    StringHasher hasher;
    HashTable<std::string, StringHasher> table(8, hasher);
    char operation = 0;
    std::string word;
    while (std::cin >> operation >> word) {
        switch (operation) {
            case '+':
                std::cout << (table.Add(word) ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                std::cout << (table.Delete(word) ? "OK" : "FAIL") << std::endl;
                break;
            case '?':
                std::cout << (table.Has(word) ? "OK" : "FAIL") << std::endl;
                break;
            default:
                break;
        }
    }
    return 0;
}
