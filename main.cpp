//4_2. Порядковые статистики
//Дано число N и N строк. Каждая строка содержащит команду добавления
// или удаления натуральных чисел, а также запрос на получение k-ой
// порядковой статистики. Команда добавления числа A задается положительным
// числом A, команда удаления числа A задается отрицательным числом “-A”.
// Запрос на получение k-ой порядковой статистики задается числом k.
// Требуемая скорость выполнения запроса - O(log n)

#include <iostream>
#include <vector>

template<class T>
struct IntCmp {
    bool operator()(T l, T r) const { return l < r; }
};

template<class T, class Compare>
class AVLTree {
public:
    AVLTree(const Compare &_cmp);

    ~AVLTree();

    AVLTree(AVLTree &) = delete;

    AVLTree operator=(const AVLTree &) = delete;

    void Add(const T &key);

    void Remove(const T &key);

    T getKthOrderStatistic(int k);

private:
    struct Node {
        T Key;
        Node *Left;
        Node *Right;
        unsigned int height;
        unsigned int count;

        Node(const T &key) : Key(key), Left(nullptr), Right(nullptr), height(1), count(1) {}
    };

    Node *root;
    Compare cmp;

    T getKthOrderStatisticHelper(Node *node, int k);

    void destroyNode(Node *node);

    T height(Node *node);

    T bfactor(Node *node);

    void fixHeight(Node *node);

    void add(Node *&node, const T &key);

    void remove(Node *&node, const T &key);

    void findAndRemoveMin(Node *&node, Node *&min, Node *&right);

    void rotateRight(Node *&node);

    void rotateLeft(Node *&node);

    void checkBalance(Node *&node);

    T count(Node *node);

    void fixCount(Node *node);
};

template<class T, class Compare>
T AVLTree<T, Compare>::getKthOrderStatistic(int k) {
    return getKthOrderStatisticHelper(root, k);
}

template<class T, class Compare>
T AVLTree<T, Compare>::getKthOrderStatisticHelper(AVLTree::Node *node, int k) {
    Node *currentNode = node;
    Node *leftNode = currentNode->Left;
    while (leftNode || currentNode->Right) {
        if (leftNode && leftNode->count == k) break;
        if (k == 0 && !leftNode) break;
        if (leftNode && leftNode->count > k) {
            currentNode = currentNode->Left;
        } else {
            currentNode = currentNode->Right;
            if (leftNode) k = k - leftNode->count - 1;
            else k -= 1;
        }
        leftNode = currentNode->Left;
    }

    return currentNode->Key;
}


template<class T, class Compare>
void AVLTree<T, Compare>::checkBalance(Node *&node) {
    fixHeight(node);
    fixCount(node);
    int balance = bfactor(node);

    if (balance == 2) {
        if (bfactor(node->Right) < 0) {
            rotateRight(node->Right);
        }
        rotateLeft(node);
    } else if (balance == -2) {
        if (bfactor(node->Left) > 0) {
            rotateLeft(node->Left);
        }
        rotateRight(node);
    }
}

template<class T, class Compare>
void AVLTree<T, Compare>::rotateLeft(AVLTree::Node *&node) {
    Node *bufferNode = node->Right;
    node->Right = bufferNode->Left;
    bufferNode->Left = node;
    fixHeight(node);
    fixCount(node);
    fixHeight(bufferNode);
    fixCount(bufferNode);
    node = bufferNode;
}

template<class T, class Compare>
void AVLTree<T, Compare>::rotateRight(AVLTree::Node *&node) {
    Node *bufferNode = node->Left;
    node->Left = bufferNode->Right;
    bufferNode->Right = node;
    fixHeight(node);
    fixCount(node);
    fixHeight(bufferNode);
    fixCount(bufferNode);
    node = bufferNode;
}

template<class T, class Compare>
void AVLTree<T, Compare>::findAndRemoveMin(AVLTree::Node *&node, AVLTree::Node *&min, AVLTree::Node *&right) {
    if (node->Left == nullptr) {
        min = node;
        right = node->Right;
        return;
    }
    findAndRemoveMin(node->Left, min, right);
    node->Left = right;
    checkBalance(node);
    right = node;
}

template<class T, class Compare>
void AVLTree<T, Compare>::remove(AVLTree::Node *&node, const T &key) {
    if (!node) return;
    if (key < node->Key)
        remove(node->Left, key);
    else if (key > node->Key)
        remove(node->Right, key);
    else //  k == p->key
    {
        Node *left = node->Left;
        Node *right = node->Right;
        delete node;
        //ищем минимальный
        if (right == nullptr) {
            node = left;
        } else {
            Node *min;
            Node *minRight;
            findAndRemoveMin(right, min, minRight);
            node = min;
            node->Left = left;
            node->Right = minRight;
        }
    }
    if (node != nullptr)
        checkBalance(node);
}

template<class T, class Compare>
void AVLTree<T, Compare>::Remove(const T &key) {
    remove(root, key);
}

template<class T, class Compare>
AVLTree<T, Compare>::AVLTree(const Compare &_cmp): root(nullptr), cmp(_cmp) {}

template<class T, class Compare>
void AVLTree<T, Compare>::add(AVLTree::Node *&node, const T &key) {
    if (node == nullptr) {
        node = new Node(key);
        return;
    }

    if (cmp(key, node->Key)) {
        add(node->Left, key);
    } else {
        add(node->Right, key);
    }

    checkBalance(node);
}

template<class T, class Compare>
void AVLTree<T, Compare>::Add(const T &key) {
    add(root, key);
}


template<class T, class Compare>
void AVLTree<T, Compare>::destroyNode(AVLTree::Node *node) {
    if (node == nullptr) {
        return;
    }

    destroyNode(node->Left);
    destroyNode(node->Right);
    delete node;
}

template<class T, class Compare>
AVLTree<T, Compare>::~AVLTree() {
    destroyNode(root);
}

template<class T, class Compare>
T AVLTree<T, Compare>::bfactor(AVLTree::Node *node) {
    return height(node->Right) - height(node->Left);
}

template<class T, class Compare>
T AVLTree<T, Compare>::height(AVLTree::Node *node) {
    return node ? node->height : 0;
}

template<class T, class Compare>
T AVLTree<T, Compare>::count(AVLTree::Node *node) {
    return node ? node->count : 0;
}

template<class T, class Compare>
void AVLTree<T, Compare>::fixCount(AVLTree::Node *node) {
    unsigned int cL = count(node->Left);
    unsigned int cR = count(node->Right);
    node->count = (cL + cR) + 1;
}

template<class T, class Compare>
void AVLTree<T, Compare>::fixHeight(AVLTree::Node *node) {
    unsigned int hL = height(node->Left);
    unsigned int hR = height(node->Right);
    node->height = (hL > hR ? hL : hR) + 1;
}

int main() {
    IntCmp<int> cmp;
    AVLTree<int, IntCmp<int>> tree(cmp);
    int n = 0, element = 0, kStat = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> element >> kStat;
        if (element > 0) {
            tree.Add(element);
        } else {
            tree.Remove(-element);
        }
        std::cout << tree.getKthOrderStatistic(kStat) << std::endl;
    }
    return 0;
}
