/**
@file
@brief Реализация методов класса DSU

@see DSU
*/

#include "dsu.h"

/**
@brief Конструктор DSU

Инициализирует систему с заданным количеством элементов.
Каждый элемент изначально является родителем самому себе.

@param count Количество элементов в системе
*/
DSU::DSU(int count) : parent(count), rank(count, 0) {
    for (int i = 0; i < parent.size(); ++i) {
        parent[i] = i;
    }
}

/**
@brief Найти представителя множества

Использует эвристику сжатия пути для оптимизации будущих запросов.

@param v Элемент, для которого ищется представитель
@return Представитель множества, содержащего элемент v
*/
int DSU::FindParent(int v) {
    if (v == parent[v]) {
        return v;
    }
    parent[v] = FindParent(parent[v]);
    return parent[v];
}

/**
@brief Объединить два множества

Использует эвристику объединения по рангу для поддержания
эффективной структуры деревьев.

@param v1 Первый элемент
@param v2 Второй элемент
*/
void DSU::Union(int v1, int v2) {
    int p1 = FindParent(v1);
    int p2 = FindParent(v2);
    if (p1 == p2) {
        return;
    }
    if (rank[p1] < rank[p2]) {
        parent[p1] = p2;
    } else {
        parent[p2] = p1;
        if (rank[p1] == rank[p2]) {
            ++rank[p2];
        }
    }
}