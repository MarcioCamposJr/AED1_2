// Nomes: Marcio Adriano de Campos Junior N°USP: 11871625
//        Isabela da Mata Tiezzi                6697732

#include "AVL.h"
#include <iostream>
#include <cstdlib>
#include <new>
#include <ctime>
#include <functional>

using namespace std;

template <typename TreeEntry>
AVLTree<TreeEntry>::AVLTree(std::function<bool(const User&, const User&)> comp,
                            std::function<bool(const User&, const User&)> equalComp,
                            std::function<string(const User&)> print)
    : comparator(comp), equalComparator(equalComp), print(print) {
    root = NULL;
}

template <typename TreeEntry>
AVLTree<TreeEntry>::~AVLTree() {
    clear(root);
}

template <typename TreeEntry>
void AVLTree<TreeEntry>::clear(TreePointer &t) {
    // Pré-condição: Nenhuma
    // Pós-condição: Todos os nós da árvore são deletados e a memória é liberada.
    if (t != NULL) {
        clear(t->leftNode);
        clear(t->rightNode);
        delete t;
        t = NULL;
    }
}

template <typename TreeEntry>
void AVLTree<TreeEntry>::searchInsert(TreeEntry x) {
    // Pré-condição: Nenhuma
    // Pós-condição: Um novo nó com a entrada 'x' é inserido na árvore, ou a contagem de um nó existente é incrementada.
    bool h = false;
    rSearchInsert(x, root, h);
}

template <typename TreeEntry>
void AVLTree<TreeEntry>::rSearchInsert(TreeEntry x, TreePointer &pA, bool &h) {
    // Pré-condição: 'pA' é um ponteiro válido para um nó da árvore.
    // Pós-condição: Um novo nó com a entrada 'x' é inserido ou um nó existente tem sua contagem incrementada.
    TreePointer pB, pC;

    if (pA == NULL) {
        pA = new TreeNode;
        h = true;
        pA->entry = x;
        pA->count = 1;
        pA->leftNode = pA->rightNode = NULL;
        pA->bal = 0;
        NumbNode++;
    } else {
        if (comparator(x, pA->entry)) {
            NumbCompar++;
            rSearchInsert(x, pA->leftNode, h);
            if (h) {
                switch (pA->bal) {
                case -1:
                    pA->bal = 0;
                    h = false;
                    break;
                case 0:
                    pA->bal = +1;
                    break;
                case +1:
                    pB = pA->leftNode;
                    if (pB->bal == +1) {
                        pA->leftNode = pB->rightNode;
                        pB->rightNode = pA;
                        pA->bal = 0;
                        pA = pB;
                    } else {
                        pC = pB->rightNode;
                        pB->rightNode = pC->leftNode;
                        pC->leftNode = pB;
                        pA->leftNode = pC->rightNode;
                        pC->rightNode = pA;
                        pA->bal = (pC->bal == +1) ? -1 : 0;
                        pB->bal = (pC->bal == -1) ? +1 : 0;
                        pA = pC;
                    }
                    pA->bal = 0;
                    h = false;
                    NumbRotation ++;
                }
            }
        } else if (equalComparator(x, pA->entry)) {
            NumbCompar++;
            pA->count++;
        } else {
            NumbCompar++;
            rSearchInsert(x, pA->rightNode, h);
            if (h) {
                switch (pA->bal) {
                case +1:
                    pA->bal = 0;
                    h = false;
                    break;
                case 0:
                    pA->bal = -1;
                    break;
                case -1:
                    pB = pA->rightNode;
                    if (pB->bal == -1) {
                        pA->rightNode = pB->leftNode;
                        pB->leftNode = pA;
                        pA->bal = 0;
                        pA = pB;
                    } else {
                        pC = pB->leftNode;
                        pB->leftNode = pC->rightNode;
                        pC->rightNode = pB;
                        pA->rightNode = pC->leftNode;
                        pC->leftNode = pA;
                        pA->bal = (pC->bal == -1) ? +1 : 0;
                        pB->bal = (pC->bal == +1) ? -1 : 0;
                        pA = pC;
                    }
                    pA->bal = 0;
                    h = false;
                    NumbRotation ++;
                }
            }
        }
    }
}

template <typename TreeEntry>
bool AVLTree<TreeEntry>::RemoveByClass(TreeEntry x) {
    // Pré-condição: Nenhuma
    // Pós-condição: Remove o nó com a entrada 'x' da árvore, se existir, e retorna true; caso contrário, false.
    bool h = false;
    return rRemove(x, root, h);
}

template <typename TreeEntry>
bool AVLTree<TreeEntry>::rRemove(TreeEntry x, TreePointer &p, bool &h) {
    // Pré-condição: 'p' é um ponteiro válido para um nó da árvore.
    // Pós-condição: Remove o nó com a entrada 'x', se existir, e ajusta a árvore adequadamente.
    TreePointer q;
    bool removeu;

    if (p == NULL) {
        return false;
    }
    if (comparator(x, p->entry)) {
        removeu = rRemove(x, p->leftNode, h);
        if (h) {
            balanceL(p, h);
        }
        return removeu;
    } else if (equalComparator(x, p->entry)) {
        q = p;
        if (q->rightNode == NULL) {
            p = q->leftNode;
            h = true;
        } else if (q->leftNode == NULL) {
            p = q->rightNode;
            h = true;
        } else {
            removeMin(q, q->rightNode, h);
            if (h) {
                balanceR(p, h);
            }
        }
        delete q;
        return true;
    } else {
        removeu = rRemove(x, p->rightNode, h);
        if (h) {
            balanceR(p, h);
        }
        return removeu;
    }
}

template <typename TreeEntry>
void AVLTree<TreeEntry>::removeMin(TreePointer &q, TreePointer &r, bool &h) {
    // Pré-condição: 'q' e 'r' são ponteiros válidos para nós da árvore.
    // Pós-condição: Remove o menor nó na subárvore enraizada em 'r' e ajusta 'q' adequadamente.
    if (r->leftNode != NULL) {
        removeMin(q, r->leftNode, h);
        if (h) {
            balanceL(r, h);
        }
    } else {
        q->entry = r->entry;
        q->count = r->count;
        q = r;
        r = r->rightNode;
        h = true;
    }
}

template <typename TreeEntry>
void AVLTree<TreeEntry>::balanceL(TreePointer &pA, bool &h) {
    // Função auxiliar para balanceamento à esquerda
    TreePointer pB, pC;
    int balB, balC;

    switch (pA->bal) {
    case +1:
        pA->bal = 0;
        break;
    case 0:
        pA->bal = -1;
        h = false;
        break;
    case -1:
        pB = pA->rightNode;
        balB = pB->bal;
        if (balB <= 0) {
            pA->rightNode = pB->leftNode;
            pB->leftNode = pA;
            if (balB == 0) {
                pA->bal = -1;
                pB->bal = +1;
                h = false;
            } else {
                pA->bal = 0;
                pB->bal = 0;
            }
            pA = pB;
        } else {
            pC = pB->leftNode;
            balC = pC->bal;
            pB->leftNode = pC->rightNode;
            pC->rightNode = pB;
            pA->rightNode = pC->leftNode;
            pC->leftNode = pA;
            pA->bal = (balC == -1) ? +1 : 0;
            pB->bal = (balC == +1) ? -1 : 0;
            pA = pC;
            pC->bal = 0;
        }
    }
}

template <typename TreeEntry>
void AVLTree<TreeEntry>::balanceR(TreePointer &pA, bool &h){
// Função auxiliar para balanceamento à direita
TreePointer pB, pC;
    int balB, balC;

    switch (pA->bal) {
    case -1:
        pA->bal = 0;
        break;
    case 0:
        pA->bal = -1;
        h = false;
        break;
    case +1:
        pB = pA->leftNode;
        balB = pB->bal;
        if (balB >= 0) {
            pA->leftNode = pB->rightNode;
            pB->rightNode = pA;
            if (balB == 0) {
                pA->bal = +1;
                pB->bal = -1;
                h = false;
            } else {
                pA->bal = 0;
                pB->bal = 0;
            }
            pA = pB;
        } else {
            pC = pB->rightNode;
            balC = pC->bal;
            pB->rightNode = pC->leftNode;
            pC->leftNode = pB;
            pA->leftNode = pC->rightNode;
            pC->rightNode = pA;
            pA->bal = (balC == -1) ? +1 : 0;
            pB->bal = (balC == +1) ? -1 : 0;
            pA = pC;
            pC->bal = 0;
        }
    }
}

template <typename TreeEntry>
int AVLTree<TreeEntry>::CountLeaf() {
    // Pré-condição: Nenhuma
    // Pós-condição: Retorna o número de folhas na árvore.
    return rCountLeaf(root);
}

template <typename TreeEntry>
int AVLTree<TreeEntry>::rCountLeaf(TreePointer &t) {
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
int AVLTree<TreeEntry>::CountNode() {
    // Pré-condição: Nenhuma
    // Pós-condição: Retorna o número de nós na árvore.
    return rCountNode(root);
}

template <typename TreeEntry>
int AVLTree<TreeEntry>::rCountNode(TreePointer &t) {
    // Pré-condição: 't' é um ponteiro válido para um nó da árvore.
    // Pós-condição: Retorna o número de nós na subárvore enraizada em 't'.
    if (t == NULL) {
        return 0;
    } else {
        return 1 + rCountNode(t->leftNode) + rCountNode(t->rightNode);
    }
}

template <typename TreeEntry>
int AVLTree<TreeEntry>::Height() {
    // Pré-condição: Nenhuma
    // Pós-condição: Retorna a altura da árvore.
    return rHeight(root);
}

template <typename TreeEntry>
int AVLTree<TreeEntry>::rHeight(TreePointer &t) {
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
TreeEntry AVLTree<TreeEntry>::minimum() {
    // Pré-condição: A árvore não está vazia.
    // Pós-condição: Retorna o elemento mínimo da árvore.
    TreePointer t = root;
    while (t->leftNode != NULL) {
        t = t->leftNode;
    }
    return t->entry;
}

template <typename TreeEntry>
TreeEntry AVLTree<TreeEntry>::maximum() {
    // Pré-condição: A árvore não está vazia.
    // Pós-condição: Retorna o elemento máximo da árvore.
    TreePointer t = root;
    while (t->rightNode != NULL) {
        t = t->rightNode;
    }
    return t->entry;
}

template <typename TreeEntry>
void AVLTree<TreeEntry>::inOrder() {
    // Pré-condição: Nenhuma
    // Pós-condição: Realiza um percurso em ordem na árvore e imprime os elementos.
    rInOrder(root);
}

template <typename TreeEntry>
void AVLTree<TreeEntry>::rInOrder(TreePointer &t) {
    // Pré-condição: 't' é um ponteiro válido para um nó da árvore.
    // Pós-condição: Realiza um percurso em ordem na subárvore enraizada em 't' e imprime os elementos.
    if (t != NULL) {
        rInOrder(t->leftNode);
        cout << print(t->entry) << " ";
        rInOrder(t->rightNode);
    }
}

template <typename TreeEntry>
void AVLTree<TreeEntry>::preOrder() {
    // Pré-condição: Nenhuma
    // Pós-condição: Realiza um percurso pré-ordem na árvore e imprime os elementos.
    rPreOrder(root);
}

template <typename TreeEntry>
void AVLTree<TreeEntry>::rPreOrder(TreePointer &t) {
    // Pré-condição: 't' é um ponteiro válido para um nó da árvore.
    // Pós-condição: Realiza um percurso pré-ordem na subárvore enraizada em 't' e imprime os elementos.
    if (t != NULL) {
        cout << print(t->entry) << " ";
        rPreOrder(t->leftNode);
        rPreOrder(t->rightNode);
    }
}

template <typename TreeEntry>
void AVLTree<TreeEntry>::postOrder() {
    // Pré-condição: Nenhuma
    // Pós-condição: Realiza um percurso pós-ordem na árvore e imprime os elementos.
    rPostOrder(root);
}

template <typename TreeEntry>
void AVLTree<TreeEntry>::rPostOrder(TreePointer &t) {
    // Pré-condição: 't' é um ponteiro válido para um nó da árvore.
    // Pós-condição: Realiza um percurso pós-ordem na subárvore enraizada em 't' e imprime os elementos.
    if (t != NULL) {
        rPostOrder(t->leftNode);
        rPostOrder(t->rightNode);
        cout << print(t->entry) << " ";
    }
}

template <typename TreeEntry>
bool AVLTree<TreeEntry>::empty() {
    // Pré-condição: Nenhuma
    // Pós-condição: Retorna true se a árvore estiver vazia, caso contrário, false.
    return root == NULL;
}


template <typename TreeEntry>
bool AVLTree<TreeEntry>::Search(TreeEntry x) {
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
int AVLTree<TreeEntry>::getNumbNode() {
    // Pré-condição: Nenhuma
    // Pós-condição: Retorna o número de nós na árvore.
    return NumbNode;
}

template <typename TreeEntry>
int AVLTree<TreeEntry>::getNumbRotation() {
    // Pré-condição: Nenhuma
    // Pós-condição: Retorna o número de retações feitas na árvore na inserção.
    return NumbRotation;
}

template <typename TreeEntry>
int AVLTree<TreeEntry>::getNumbCompar() {
    // Pré-condição: Nenhuma
    // Pós-condição: Retorna o número de comparações feitas na árvore na inserção.
    return NumbCompar;
}