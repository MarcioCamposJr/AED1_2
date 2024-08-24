// Nomes: Marcio Adriano de Campos Junior N°USP: 11871625
//        Isabela da Mata Tiezzi                6697732

#ifndef AVL_H
#define AVL_H

#include "FileReader.h"

#include <iostream>
#include <string>
#include <ctime>
#include <functional>

using namespace std;

template <typename TreeEntry> 
class AVLTree {
    
    // Estrutura do nó da árvore
    struct TreeNode {
        int count;                     // Contador de ocorrências
        TreeEntry entry;               // Entrada do nó
        TreeNode* leftNode = nullptr;  // Ponteiro para o nó esquerdo
        TreeNode* rightNode = nullptr; // Ponteiro para o nó direito
        int bal;
    };

    typedef TreeNode* TreePointer;     // Ponteiro para TreeNode

private:

    std::function<bool(const User&, const User&)> comparator;         // Função de comparação
    std::function<bool(const User&, const User&)> equalComparator;    // Função de igualdade
    std::function<string(const User&)> print;                        // Função de impressão

    int NumbNode = 0;             // Número de nós na árvore
    int NumbRotation = 0;         // Número de rotações na inserção da AVL
    int NumbCompar = 0;           // Número de comparações na inserção da AVL
    TreePointer root = nullptr;   // Raiz da árvore

    // Funções recursivas para operações na árvore
    void rSearchInsert(TreeEntry x, TreePointer &t, bool &h);                  // Inserção/Busca recursiva

    bool rRemove(TreeEntry x, TreePointer &p, bool &h);                        // Remoção recursiva
    void removeMin(TreePointer &q, TreePointer &r, bool &h);                   // Remover o mínimo

    void balanceL(TreePointer &pA, bool &h);
    void balanceR(TreePointer &pA, bool &h);

    void clear(TreePointer &t);                                       // Limpar a árvore

    int rCountNode(TreePointer &t);                                   // Contar nós recursivamente
    int rCountLeaf(TreePointer &t);                                   // Contar folhas recursivamente
    int rHeight(TreePointer &t);                                      // Altura recursiva

    void rInOrder(TreePointer &t);                                    // Percurso em ordem
    void rPreOrder(TreePointer &t);                                   // Percurso pré-ordem
    void rPostOrder(TreePointer &t);                                  // Percurso pós-ordem

public:
    // Construtor
    AVLTree(function<bool(const User&, const User&)> comp,
               function<bool(const User&, const User&)> equalComp,
               function<string(const User&)> print);

    // Destrutor
    ~AVLTree();

    // Funções públicas
    bool Search(TreeEntry x);                  // Buscar entrada

    int CountNode();                           // Contar número de nós
    int CountLeaf();                           // Contar número de folhas
    int Height();                              // Altura da árvore

    int getNumbNode();                         // Obter número de nós
    int getNumbRotation();                     // Obter número de retoções feitas na inserção
    int getNumbCompar();                       // Obter número de comparações feitas na inserção

    void searchInsert(TreeEntry x);            // Buscar e inserir entrada
    bool RemoveByClass(TreeEntry x);                  // Remover entrada

    TreeEntry minimum();                       // Encontrar o mínimo    
    TreeEntry maximum();                       // Encontrar o máximo

    bool empty();                              // Verificar se está vazia

    void inOrder();                            // Percurso em ordem
    void preOrder();                           // Percurso pré-ordem
    void postOrder();                          // Percurso pós-ordem
};

// Implementação explícita do template para o tipo User
template class AVLTree<User>;
#endif
