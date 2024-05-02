//Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
//Требуется построить бинарное дерево, заданное наивным порядком вставки.
//Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
//Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
//
//2_4. Выведите элементы в порядке level-order (по слоям, “в ширину”).

#include <iostream>
#include <cassert>
#include <vector>


template<class T, class Compare>
class BinaryTree {
public:
    BinaryTree(const Compare &_cmp) : root(nullptr), cmp(_cmp) {}

    ~BinaryTree();

    void Add(const T &key);

    bool Has(const T &key) const;

    void Bfs(void( *visit )(const T &key)) const;

private:
    struct Node {
        T Key;
        Node *Left;
        Node *Right;

        Node(const T &key) : Key(key), Left(nullptr), Right(nullptr) {}
    };

    Node *root;
    Compare cmp;

    void destroyNode(Node *node);

    void add(Node *&node, const T &key);

    bool has(Node *node, const T &key) const;

    void bfs(Node *node, void( *visit )(const T &key)) const;
};

template<class T, class Compare>
BinaryTree<T, Compare>::~BinaryTree() {
    destroyNode(root);
}

template<class T, class Compare>
void BinaryTree<T, Compare>::destroyNode(Node *node) {
    if (node == nullptr) {
        return;
    }
    std::vector<Node *> stack;
    Node *curr = node;
    Node *prev = nullptr;

    while (curr != nullptr || !stack.empty()) {
        while (curr != nullptr) {
            stack.push_back(curr);
            curr = curr->Left;
        }

        curr = stack.back();

        if (curr->Right == nullptr || curr->Right == prev) {
            stack.pop_back();
            delete curr;
            prev = curr;
            curr = nullptr;
        } else {
            curr = curr->Right;
        }
    }
}

template<class T, class Compare>
void BinaryTree<T, Compare>::Bfs(void (*visit)(const T &key)) const {
    bfs(root, visit);
}

template<class T, class Compare>
bool BinaryTree<T, Compare>::Has(const T &key) const {
    return has(root, key);
}

template<class T, class Compare>
void BinaryTree<T, Compare>::Add(const T &key) {
    add(root, key);
}

template<class T, class Compare>
void BinaryTree<T, Compare>::bfs(Node *node, void ( *visit )(const T &key)) const {
    if (node == nullptr) {
        return;
    }

    std::vector<Node *> queue;
    queue.push_back(node);

    while (!queue.empty()) {
        Node *current = queue.front();
        queue.erase(queue.begin());

        visit(current->Key);
        if (current->Left != nullptr)
            queue.push_back(current->Left);
        if (current->Right != nullptr)
            queue.push_back(current->Right);
    }
}

template<class T, class Compare>
bool BinaryTree<T, Compare>::has(Node *node, const T &key) const {
    if (node == nullptr) {
        return false;
    }

    Node *current = node;
    while (current != nullptr) {
        if (current->Key == key) {
            return true;
        }
        if (cmp(current->Key, key)) {
            current = current->Right;
        } else {
            current = current->Left;
        }
    }
    return false;
}

template<class T, class Compare>
void BinaryTree<T, Compare>::add(Node *&node, const T &key) {
    Node *newNode = new Node(key);
    if (node == nullptr) {
        node = newNode;
        return;
    }
    Node *current = node;
    Node *parent = nullptr;
    while (current != nullptr) {
        parent = current;
        if (cmp(current->Key, key)) {
            current = current->Right;
        } else {
            current = current->Left;
        }
    }

    if (cmp(parent->Key, key)) {
        parent->Right = newNode;
    } else {
        parent->Left = newNode;
    }
}

struct IntCmp {
    bool operator()(int l, int r) {
        return l < r;
    }
};

int main() {
    IntCmp cmp;
    BinaryTree<int, IntCmp> tree(cmp);
    int n = 0, el = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> el;
        tree.Add(el);
    }
    tree.Bfs([](const int &key) { std::cout << key << ' '; });
    return 0;
}
