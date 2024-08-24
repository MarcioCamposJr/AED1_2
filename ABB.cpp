// Nomes: Marcio Adriano de Campos Junior N°USP: 11871625
//        Isabela da Mata Tiezzi                6697732

#include "ABB.h"
#include <iostream>
#include <cstdlib>
#include <new>
#include <ctime>
#include <functional>

using namespace std;

template <typename TreeEntry>
BinarySearchTree<TreeEntry>::BinarySearchTree(std::function<bool(const User&, const User&)> comp,
                                  std::function<bool(const User&, const User&)> equalComp,
                                  std::function<string(const User&)> print)
    : comparator(comp), equalComparator(equalComp), print(print) {
    root = NULL;
}

template <typename TreeEntry>
BinarySearchTree<TreeEntry>::~BinarySearchTree() {
    clear(root);
}

template <typename TreeEntry>
void BinarySearchTree<TreeEntry>::clear(TreePointer &t) {
    // Pré-condição: Nenhuma
    // Pós-condição: Todos os nós da árvore são deletados e a memória é liberada.
    if (t != NULL) {
        clear(t->leftNode);
        clear(t->rightNode);
        delete t;
    }
}

template <typename TreeEntry>
void BinarySearchTree<TreeEntry>::Insert(TreeEntry x) {
    // Pré-condição: Nenhuma
    // Pós-condição: Um novo nó com a entrada 'x' é inserido na árvore.
    if (root == NULL) {
        root = new TreeNode;
        root->entry = x;
        NumbNode++;
    } else {
        TreePointer t = root;
        rInsert(x, t);
    }
}

template <typename TreeEntry>
void BinarySearchTree<TreeEntry>::rInsert(TreeEntry x, TreePointer &t) {
    // Pré-condição: 't' é um ponteiro válido para um nó da árvore.
    // Pós-condição: Um novo nó com a entrada 'x' é inserido na posição correta da árvore.
    if (t == NULL) {
        t = new TreeNode;
        t->entry = x;
        NumbNode++;
    } else if (comparator(x, t->entry)) {
        rInsert(x, t->leftNode);
    } else {
        rInsert(x, t->rightNode);
    }
}

template <typename TreeEntry>
void BinarySearchTree<TreeEntry>::iInsert(TreeEntry x) {
    // Pré-condição: Nenhuma
    // Pós-condição: Um novo nó com a entrada 'x' é inserido iterativamente na árvore.
    TreePointer t = root, p = NULL, r;

    while (t != NULL) {
        p = t; // p é o pai de t, sendo útil para depois inserir novo nó a partir do pai
        if (comparator(x, t->entry)) {
            t = t->leftNode;
        } else {
            t = t->rightNode;
        }
    }

    r = new TreeNode;
    if (r == NULL) {
        cout << "Erro ao alocar memória" << endl;
        abort();
    }

    r->entry = x;
    r->leftNode = NULL;
    r->rightNode = NULL;

    if (p == NULL) {
        root = r; // árvore vazia
    } else if (comparator(x, p->entry)) {
        p->leftNode = r;
    } else {
        p->rightNode = r;
    }
    NumbNode++;
}

template <typename TreeEntry>
void BinarySearchTree<TreeEntry>::searchInsert(TreeEntry x) {
    // Pré-condição: Nenhuma
    // Pós-condição: Um novo nó com a entrada 'x' é inserido na árvore, ou a contagem de um nó existente é incrementada.
    rSearchInsert(x, root);
}

template <typename TreeEntry>
void BinarySearchTree<TreeEntry>::rSearchInsert(TreeEntry x, TreePointer &t) {
    // Pré-condição: 't' é um ponteiro válido para um nó da árvore.
    // Pós-condição: Um novo nó com a entrada 'x' é inserido ou um nó existente tem sua contagem incrementada.
    if (t == NULL) {
        t = new TreeNode;
        t->entry = x;
        t->count = 1;
        NumbNode ++;
    } else {
        if (comparator(x, t->entry)) {
            NumbCompar++;
            rSearchInsert(x, t->leftNode);
        } else if (equalComparator(x, t->entry)) {
            NumbCompar++;
            t->count++;
        } else {
            NumbCompar++;
            rSearchInsert(x, t->rightNode);
        }
    }
}

template <typename TreeEntry>
bool BinarySearchTree<TreeEntry>::Search(TreeEntry x) {
    // Pré-condição: Nenhuma
    // Pós-condição: Retorna true se a entrada 'x' for encontrada na árvore, caso contrário, false.
    TreePointer t = root;
    while (t != NULL && !equalComparator(t->entry, x)) {
        if (comparator(x, t->entry)) {
            t = t->leftNode;
        } else {
            t = t->rightNode;
        }
    }
    return t != NULL;
}

template <typename TreeEntry>
bool BinarySearchTree<TreeEntry>::empty() {
    // Pré-condição: Nenhuma
    // Pós-condição: Retorna true se a árvore estiver vazia, caso contrário, false.
    return root == NULL;
}

template <typename TreeEntry>
int BinarySearchTree<TreeEntry>::getNumbNode() {
    // Pré-condição: Nenhuma
    // Pós-condição: Retorna o número de nós na árvore.
    return NumbNode;
}

template <typename TreeEntry>
int BinarySearchTree<TreeEntry>::getNumbCompar() {
    // Pré-condição: Nenhuma
    // Pós-condição: Retorna o número de comparações feitas na árvore na inserção.
    return NumbCompar;
}

template <typename TreeEntry>
bool BinarySearchTree<TreeEntry>::RemoveByClass(TreeEntry x) {
    // Pré-condição: Nenhuma
    // Pós-condição: Remove o nó com a entrada 'x' da árvore, se existir, e retorna true; caso contrário, false.
    return rRemove(x, root);
}

template <typename TreeEntry>
bool BinarySearchTree<TreeEntry>::rRemove(TreeEntry x, TreePointer &t) {
    // Pré-condição: 't' é um ponteiro válido para um nó da árvore.
    // Pós-condição: Remove o nó com a entrada 'x', se existir, e ajusta a árvore adequadamente.
    if (t == NULL) {
        return false;
    }

    if (comparator(x, t->entry)) {      // Coparação menor que
        return rRemove(x, t->leftNode);
    }

    if (equalComparator(x, t->entry)) { // Comparação iguais
        TreePointer q = t;

        if (q->leftNode == NULL) {
            t = q->rightNode;
        } else if (q->rightNode == NULL) {
            t = q->leftNode;
        } else {
            removeMin(q, q->rightNode);
        }

        delete q;
        return true;
    }

    return rRemove(x, t->rightNode);   // Comparação maior que
}

template <typename TreeEntry>
void BinarySearchTree<TreeEntry>::removeMin(TreePointer &q, TreePointer &r) {
    // Pré-condição: 'q' e 'r' são ponteiros válidos para nós da árvore.
    // Pós-condição: Remove o menor nó na subárvore enraizada em 'r' e ajusta 'q' adequadamente.
    if (r->leftNode != NULL) {
        removeMin(q, r->leftNode);
    } else {
        q->entry = r->entry;
        q->count = r->count;
        q = r;
        r = r->rightNode;
    }
}

template <typename TreeEntry>
int BinarySearchTree<TreeEntry>::CountLeaf() {
    // Pré-condição: Nenhuma
    // Pós-condição: Retorna o número de folhas na árvore.
    return rCountLeaf(root);
}

template <typename TreeEntry>
int BinarySearchTree<TreeEntry>::rCountLeaf(TreePointer &t) {
    // Pré-condição: 't' é um ponteiro válido para um nó da árvore.
    // Pós-condição: Retorna o número de folhas na subárvore enraizada em 't'.
    if (t == NULL) {
        return 0;
    } else if (t->leftNode == NULL && t->rightNode == NULL) {
        return 1;
    } else {
        return rCountLeaf(t->leftNode) + rCountLeaf(t->rightNode);
    }
}

template <typename TreeEntry>
int BinarySearchTree<TreeEntry>::CountNode() {
    // Pré-condição: Nenhuma
    // Pós-condição: Retorna o número de nós na árvore.
    return rCountNode(root);
}

template <typename TreeEntry>
int BinarySearchTree<TreeEntry>::rCountNode(TreePointer &t) {
    // Pré-condição: 't' é um ponteiro válido para um nó da árvore.
    // Pós-condição: Retorna o número de nós na subárvore enraizada em 't'.
    if (t == NULL) {
        return 0;
    } else {
        return 1 + rCountNode(t->leftNode) + rCountNode(t->rightNode);
    }
}

template <typename TreeEntry>
int BinarySearchTree<TreeEntry>::Height() {
    // Pré-condição: Nenhuma
    // Pós-condição: Retorna a altura da árvore.
    return rHeight(root);
}

template <typename TreeEntry>
int BinarySearchTree<TreeEntry>::rHeight(TreePointer &t) {
    // Pré-condição: 't' é um ponteiro válido para um nó da árvore.
    // Pós-condição: Retorna a altura da subárvore enraizada em 't'.
    if (t == NULL) {
        return -1;
    } else {
        int left = rHeight(t->leftNode);
        int right = rHeight(t->rightNode);
        return max(left, right) + 1;
    }
}

template <typename TreeEntry>
TreeEntry BinarySearchTree<TreeEntry>::minimum() {
    // Pré-condição: A árvore não está vazia.
    // Pós-condição: Retorna o elemento mínimo da árvore.
    TreePointer t = root;
    while (t->leftNode != NULL) {
        t = t->leftNode;
    }
    return t->entry;
}

template <typename TreeEntry>
TreeEntry BinarySearchTree<TreeEntry>::maximum() {
    // Pré-condição: A árvore não está vazia.
    // Pós-condição: Retorna o elemento máximo da árvore.
    TreePointer t = root;
    while (t->rightNode != NULL) {
        t = t->rightNode;
    }
    return t->entry;
}

template <typename TreeEntry>
void BinarySearchTree<TreeEntry>::inOrder() {
    // Pré-condição: Nenhuma
    // Pós-condição: Realiza um percurso em ordem na árvore e imprime os elementos.
    rInOrder(root);
}

template <typename TreeEntry>
void BinarySearchTree<TreeEntry>::rInOrder(TreePointer &t) {
    // Pré-condição: 't' é um ponteiro válido para um nó da árvore.
    // Pós-condição: Realiza um percurso em ordem na subárvore enraizada em 't' e imprime os elementos.
    if (t != NULL) {
        rInOrder(t->leftNode);
        cout << print(t->entry) << " ";
        rInOrder(t->rightNode);
    }
}

template <typename TreeEntry>
void BinarySearchTree<TreeEntry>::preOrder() {
    // Pré-condição: Nenhuma
    // Pós-condição: Realiza um percurso pré-ordem na árvore e imprime os elementos.
    rPreOrder(root);
}

template <typename TreeEntry>
void BinarySearchTree<TreeEntry>::rPreOrder(TreePointer &t) {
    // Pré-condição: 't' é um ponteiro válido para um nó da árvore.
    // Pós-condição: Realiza um percurso pré-ordem na subárvore enraizada em 't' e imprime os elementos.
    if (t != NULL) {
        cout << print(t->entry) << " ";
        rPreOrder(t->leftNode);
        rPreOrder(t->rightNode);
    }
}

template <typename TreeEntry>
void BinarySearchTree<TreeEntry>::postOrder() {
    // Pré-condição: Nenhuma
    // Pós-condição: Realiza um percurso pós-ordem na árvore e imprime os elementos.
    rPostOrder(root);
}

template <typename TreeEntry>
void BinarySearchTree<TreeEntry>::rPostOrder(TreePointer &t) {
    // Pré-condição: 't' é um ponteiro válido para um nó da árvore.
    // Pós-condição: Realiza um percurso pós-ordem na subárvore enraizada em 't' e imprime os elementos.
    if (t != NULL) {
        rPostOrder(t->leftNode);
        rPostOrder(t->rightNode);
        cout << print(t->entry) << " ";
    }
}
