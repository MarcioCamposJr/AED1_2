// Nomes: Marcio Adriano de Campos Junior N°USP: 11871625
//        Isabela da Mata Tiezzi                6697732

#ifndef ABB_H
#define ABB_H

#include "FileReader.h"

#include <iostream>
#include <string>
#include <ctime>
#include <functional>

using namespace std;

template <typename TreeEntry> 
class BinarySearchTree {
    
    // Estrutura do nó da árvore
    struct TreeNode {
        int count;                     // Contador de ocorrências
        TreeEntry entry;               // Entrada do nó
        TreeNode* leftNode = nullptr;  // Ponteiro para o nó esquerdo
        TreeNode* rightNode = nullptr; // Ponteiro para o nó direito
    };

    typedef TreeNode* TreePointer;     // Ponteiro para TreeNode

private:

    std::function<bool(const User&, const User&)> comparator;         // Função de comparação
    std::function<bool(const User&, const User&)> equalComparator;    // Função de igualdade
    std::function<string(const User&)> print;                        // Função de impressão

    int NumbNode = 0;             // Número de nós na árvore
    int NumbCompar = 0;           // Número de comparações na inserção da AVL
    TreePointer root = nullptr;   // Raiz da árvore

    // Funções recursivas para operações na árvore
    void rInsert(TreeEntry nome, TreePointer &t);                     // Inserção recursiva //O(h)
    void iInsert(TreeEntry nome);                                     // Inserção iterativa //O(h)

    void rSearchInsert(TreeEntry x, TreePointer &t);                  // Inserção/Busca recursiva   //O(h)

    bool rRemove(TreeEntry x, TreePointer &t);                        // Remoção recursiva  //O(h)
    void removeMin(TreePointer &q, TreePointer &r);                   // Remover o mínimo   //O(h)

    void clear(TreePointer &t);                                       // Limpar a árvore    //O(h)

    int rCountNode(TreePointer &t);                                   // Contar nós recursivamente  //O(h)
    int rCountLeaf(TreePointer &t);                                   // Contar folhas recursivamente   //O(h)
    int rHeight(TreePointer &t);                                      // Altura recursiva   //O(h)

    void rInOrder(TreePointer &t);                                    // Percurso em ordem  //O(h)
    void rPreOrder(TreePointer &t);                                   // Percurso pré-ordem //O(h)
    void rPostOrder(TreePointer &t);                                  // Percurso pós-ordem //O(h)

public:
    // Construtor
    BinarySearchTree(function<bool(const User&, const User&)> comp,
               function<bool(const User&, const User&)> equalComp,
               function<string(const User&)> print);

    // Destrutor
    ~BinarySearchTree();

    // Funções públicas
    bool Search(TreeEntry x);                  // Buscar entrada    //O(h)

    int getNumbNode();                         // Obter número de nós   //O(1)
    int getNumbCompar();                       // Obter número de comparações feitas na inserção    //O(1)
    int CountNode();                           // Contar número de nós  //O(h)
    int CountLeaf();                           // Contar número de folhas   //O(h)
    int Height();                              // Altura da árvore  //O(h)

    void Insert(TreeEntry nome);               // Inserir entrada   //O(h)
    void searchInsert(TreeEntry x);            // Buscar e inserir entrada  //O(h)
    bool RemoveByClass(TreeEntry x);           // Remover entrada   //O(h)

    TreeEntry minimum();                       // Encontrar o mínimo
    TreeEntry maximum();                       // Encontrar o máximo

    bool empty();                              // Verificar se está vazia   

    void inOrder();                            // Percurso em ordem
    void preOrder();                           // Percurso pré-ordem
    void postOrder();                          // Percurso pós-ordem
};

// Implementação explícita do template para o tipo User
template class BinarySearchTree<User>;
#endif
