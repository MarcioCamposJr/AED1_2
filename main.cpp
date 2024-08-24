// Nomes: Marcio Adriano de Campos Junior N°USP:11871625
//        Isabela da Mata Tiezzi                6697732

#include "FileReader.h"
#include "ABB.h"
#include "AVL.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <limits>

void StartMenu(AVLTree<User>& AVLBirthday, AVLTree<User>& AVLName, AVLTree<User>& AVLID,
    BinarySearchTree<User>& ABBBirthday, BinarySearchTree<User>& ABBName, BinarySearchTree<User>& ABBID, int choice );

// Funções de comparação para diferentes critérios
bool compareByName(const User& a, const User& b) {
    return a.name < b.name;
}

bool compareByID(const User& a, const User& b) {
    return a.id < b.id;
}

bool compareByBirthday(const User& a, const User& b) {
    std::tm tempA = a.birthday;
    std::tm tempB = b.birthday;
    if (tempA.tm_year != tempB.tm_year)
        return tempA.tm_year < tempB.tm_year;
    if (tempA.tm_mon != tempB.tm_mon)
        return tempA.tm_mon < tempB.tm_mon;
    return tempA.tm_mday < tempB.tm_mday;
}

// Funções de comparação para igualdade
bool CompareEqualName(const User& a, const User& b) {
    return a.name == b.name;
}

bool CompareEqualID(const User& a, const User& b) {
    return a.id == b.id;
}

bool CompareEqualBirthday(const User& a, const User& b) {
    std::tm tempA = a.birthday;
    std::tm tempB = b.birthday;
    return (tempA.tm_year == tempB.tm_year && tempA.tm_mon == tempB.tm_mon && tempA.tm_mday == tempB.tm_mday);
}

// Funções de impressão para diferentes atributos
string printName(const User& a) {
    return a.name;
}

string printID(const User& a) {
    return std::to_string(a.id);
}

string printBirthday(const User& a) {
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", &a.birthday);
    return std::string(buffer);
}

User getUser(){

    User usuario;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout<< "Digite o nome do usuario:" <<endl;
    std::getline(std::cin, usuario.name);    

    cout<< "Digite o ID do usuario:" <<endl;
    cin >> usuario.id;

    cout<< "Digite o dia de nascimento do usuario:" <<endl;
    cin>> usuario.birthday.tm_mday;

    cout<< "Digite o numero do mes de nascimento do usuario:" <<endl;
    cin>> usuario.birthday.tm_mon;

    cout<< "Digite o ano de nascimento do usuario:" <<endl;
    cin>> usuario.birthday.tm_year;

    return usuario;
}

void SearchABB(BinarySearchTree<User> &arvore, int &choice){

    User usuario;

    usuario = getUser();

    if(arvore.Search(usuario)){
        cout<< "O usuario foi encontrado" << endl;
    }else{
        cout<< "O usuario nao foi encontrado" << endl;
    }
    choice = 0;
}

void addABB(BinarySearchTree<User> &arvore, int &choice){

    User usuario;

    usuario = getUser();

    arvore.searchInsert(usuario);
    choice = 0;
}

void removeABB(BinarySearchTree<User> &arvore, int &choice){

    User usuario;

    usuario = getUser();

    if(arvore.RemoveByClass(usuario)){
        cout<< "O usuario foi removido com sucesso" << endl;
    }
    else{
        cout<< "O usuario nao foi encontrado" << endl;
    }
    choice = 0;
}

void BinarySearchTreeMenu(AVLTree<User> &AVLBirthday, AVLTree<User> &AVLName, AVLTree<User> &AVLID,
 BinarySearchTree<User> &ABBBirthday, BinarySearchTree<User> &ABBName, BinarySearchTree<User> &ABBID, int number){

    BinarySearchTree<User>* arvore =nullptr;

    switch (number){
    case 4: arvore = &ABBBirthday; break;
    case 5: arvore = &ABBName; break;
    case 6: arvore = &ABBID; break;
}

    cout << "Escolha uma opcao:" << endl;

    cout << "1 - Buscar uma tupla." << endl;
    cout << "2 - Adicionar uma nova tupla" << endl;
    cout << "3 - Remover uma tupla" << endl;
    cout << "4 - Volar ao Menu Inicial" << endl;

    int choice;

    cout << "Digite um numero: ";  // Exibe uma mensagem solicitando ao usuário que insira um número
    cin >> choice;  // Lê o valor inserido pelo usuário e atribui à variável numero

    switch (choice){
    case 1: SearchABB(*arvore, choice); break;
    case 2: addABB(*arvore, choice);break;
    case 3: removeABB(*arvore, choice); break;
    case 4:{ int aux = 0; 
    StartMenu(AVLBirthday, AVLName, AVLID, ABBBirthday, ABBName, ABBID, aux);
     break;}

    default: 
        cout << "Escolha um numero valido";
        BinarySearchTreeMenu(AVLBirthday, AVLName, AVLID, ABBBirthday, ABBName, ABBID, number);
}   
    StartMenu(AVLBirthday, AVLName, AVLID, ABBBirthday, ABBName, ABBID, choice);
}

void SearchAVL(AVLTree<User> &arvore, int &choice){

    User usuario;

    usuario = getUser();

    if(arvore.Search(usuario)){
        cout<< "O usuario foi encontrado" << endl;
    }else{
        cout<< "O usuario nao foi encontrado" << endl;
    }

    choice = 0;
    
}

void addAVL(AVLTree<User> &arvore, int &choice){

    User usuario;

    usuario = getUser();

    arvore.searchInsert(usuario);

    choice = 0;
}

void removeAVL(AVLTree<User> &arvore, int &choice){

    User usuario;

    usuario = getUser();

    if(arvore.RemoveByClass(usuario)){
        cout<< "O usuario foi removido com sucesso" << endl;
    }
    else{
        cout<< "O usuario nao foi encontrado" << endl;
    }

    choice = 0;
}

void AVLTreeMenu(AVLTree<User> &AVLBirthday, AVLTree<User> &AVLName, AVLTree<User> &AVLID,
 BinarySearchTree<User> &ABBBirthday, BinarySearchTree<User> &ABBName, BinarySearchTree<User> &ABBID, int number){
    
    AVLTree<User>* arvore;

    switch (number){
    case 1: arvore = &AVLBirthday; break;
    case 2: arvore = &AVLName; break;
    case 3: arvore = &AVLID; break;
}
    cout << endl;
    cout << "Escolha uma opcao:" << endl;

    cout << "1 - Buscar uma tupla" << endl;
    cout << "2 - Adicionar uma nova tupla" << endl;
    cout << "3 - Remover uma tupla" << endl;
    cout << "4 - Voltar ao Menu Inicial" << endl;

    int choice;
    cout << "Digite um numero: ";  // Exibe uma mensagem solicitando ao usuário que insira um número
    cin >> choice;  // Lê o valor inserido pelo usuário e atribui à variável numero

    switch (choice){
    case 1: SearchAVL(*arvore, choice); break;
    case 2: addAVL(*arvore, choice); break;
    case 3: removeAVL(*arvore, choice); break;
    case 4:{ int aux = 0;
    StartMenu(AVLBirthday, AVLName, AVLID, ABBBirthday, ABBName, ABBID, aux);
    break;}

    default: 
        cout << endl;
        cout << "Escolha um numero valido";
        AVLTreeMenu(AVLBirthday, AVLName, AVLID, ABBBirthday, ABBName, ABBID, choice);
        break;
}
    StartMenu(AVLBirthday, AVLName, AVLID, ABBBirthday, ABBName, ABBID, choice);
}

void showParameters(AVLTree<User> &AVLBirthday, AVLTree<User> &AVLName, AVLTree<User> &AVLID,
 BinarySearchTree<User> &ABBBirthday, BinarySearchTree<User> &ABBName, BinarySearchTree<User> &ABBID){
    
    cout << endl;
    cout << "Metricas:" << endl;
    cout << endl;

    cout << "Numero de Usuarios:" << endl;
    cout << endl;

    cout << "BinarySearchTree:" << endl;
    cout << endl;
    
    cout << "ABBBirthday: ";
    cout << ABBBirthday.getNumbNode() << endl;
    cout << "ABBName: ";
    cout << ABBName.getNumbNode() << endl;
    cout << "ABBID: ";
    cout << ABBID.getNumbNode() << endl;

    cout << endl;
    cout << "AVLTree:" << endl;
    cout << endl;

    cout << "AVLBirthday: ";
    cout << AVLBirthday.getNumbNode() << endl;
    cout << "AVLName: ";
    cout << AVLName.getNumbNode() << endl;
    cout << "AVLID: ";
    cout << AVLID.getNumbNode() << endl;
    cout << endl;

    cout << "Altura das arvores:" << endl;
    cout << endl;

    cout << "BinarySearchTree:" << endl;
    cout << endl;
    
    cout << "ABBBirthday: ";
    cout << ABBBirthday.Height() << endl;
    cout << "ABBName: ";
    cout << ABBName.Height() << endl;
    cout << "ABBID: ";
    cout << ABBID.Height() << endl;

    cout << endl;
    cout << "AVLTree:" << endl;
    cout << endl;

    cout << "AVLBirthday: ";
    cout << AVLBirthday.Height() << endl;
    cout << "AVLName: ";
    cout << AVLName.Height() << endl;
    cout << "AVLID: ";
    cout << AVLID.Height() << endl;
    cout << endl;

    cout << "Numero de folhas:" << endl;
    cout << endl;

    cout << "BinarySearchTree:" << endl;
    cout << endl;
    
    cout << "ABBBirthday: ";
    cout << ABBBirthday.CountLeaf() << endl;
    cout << "ABBName: ";
    cout << ABBName.CountLeaf() << endl;
    cout << "ABBID: ";
    cout << ABBID.CountLeaf() << endl;

    cout << endl;
    cout << "AVLTree:" << endl;
    cout << endl;

    cout << "AVLBirthday: ";
    cout << AVLBirthday.CountLeaf() << endl;
    cout << "AVLName: ";
    cout << AVLName.CountLeaf() << endl;
    cout << "AVLID: ";
    cout << AVLID.CountLeaf() << endl;
    cout << endl;

    cout << "Rotacoes na insercao de AVL" << endl;
    cout << endl;

    cout << "AVLBirthday: ";
    cout << AVLBirthday.getNumbRotation() << endl;
    cout << "AVLName: ";
    cout << AVLName.getNumbRotation() << endl;
    cout << "AVLID: ";
    cout << AVLID.getNumbRotation() << endl;
    cout << endl;

    cout << "Numero de comparacoes feitas na insercao:" << endl;
    cout << endl;

    cout << "BinarySearchTree:" << endl;
    cout << endl;
    
    cout << "ABBBirthday: ";
    cout << ABBBirthday.getNumbCompar() << endl;
    cout << "ABBName: ";
    cout << ABBName.getNumbCompar() << endl;
    cout << "ABBID: ";
    cout << ABBID.getNumbCompar() << endl;

    cout << endl;
    cout << "AVLTree:" << endl;
    cout << endl;

    cout << "AVLBirthday: ";
    cout << AVLBirthday.getNumbCompar() << endl;
    cout << "AVLName: ";
    cout << AVLName.getNumbCompar() << endl;
    cout << "AVLID: ";
    cout << AVLID.getNumbCompar() << endl;
    cout << endl;
    cout << endl;
    cout << endl;

    cout << "Media de Comparacoes por Usuario na ABB:" << endl;
    cout << endl;

    cout << "ABBBirthday: ";

    float meanCompar1 = static_cast<float>(ABBBirthday.getNumbCompar())/static_cast<float>(ABBBirthday.getNumbNode());
    float meanCompar2 = static_cast<float>(ABBName.getNumbCompar())/static_cast<float>(ABBName.getNumbNode());
    float meanCompar3 = static_cast<float>(ABBID.getNumbCompar())/static_cast<float>(ABBID.getNumbNode());

    cout << meanCompar1 << endl;
    cout << "ABBName: ";
    cout << meanCompar2 << endl;
    cout << "ABBID: ";
    cout << meanCompar3 << endl;

    cout << endl;
    cout << "Media de Comparacoes por Usuario na AVL:" << endl;
    cout << endl;
    

    cout << "AVLBirthday: ";
    cout << static_cast<float>(AVLBirthday.getNumbCompar())/static_cast<float>(AVLBirthday.getNumbNode()) << endl;
    cout << "AVLName: ";
    cout << static_cast<float>(AVLName.getNumbCompar())/static_cast<float>(AVLName.getNumbNode()) << endl;
    cout << "AVLID: ";
    cout << static_cast<float>(AVLID.getNumbCompar())/static_cast<float>(AVLID.getNumbNode()) << endl;

    cout << endl;
    cout << "Media de Rotacoes por Usuario na AVL:" << endl;
    cout << endl;

    cout << "AVLBirthday: ";
    cout << static_cast<float>(AVLBirthday.getNumbRotation())/static_cast<float>(AVLBirthday.getNumbNode()) << endl;
    cout << "AVLName: ";
    cout << static_cast<float>(AVLName.getNumbRotation())/static_cast<float>(AVLName.getNumbNode()) << endl;
    cout << "AVLID: ";
    cout << static_cast<float>(AVLID.getNumbRotation())/static_cast<float>(AVLID.getNumbNode()) << endl;
    cout << endl;
    cout << endl;

    int choice = 0;
    StartMenu(AVLBirthday, AVLName, AVLID, ABBBirthday, ABBName, ABBID, choice);
 }

void StartMenu(AVLTree<User> &AVLBirthday, AVLTree<User> &AVLName, AVLTree<User> &AVLID,
 BinarySearchTree<User> &ABBBirthday, BinarySearchTree<User> &ABBName, BinarySearchTree<User> &ABBID, int choice){

    if(choice == 0 ){
    cout << "Escolha sua arvore para continuar ou entao escolha exibir os parametros:" << endl;

    cout << "1.AVL (Birthday)" << endl;
    cout << "2.AVL (Name)" << endl;
    cout << "3.AVL (ID)" << endl;

    cout << "4.AVL (Birthday)" << endl;
    cout << "5.AVL (Name)" << endl;
    cout << "6.AVL (ID)" << endl;

    cout << "7.Exibir parametros compartivos entre as arvores" << endl;

    cout << "0.Fechar" << endl;

    cout << "Digite um numero: ";  // Exibe uma mensagem solicitando ao usuário que insira um número
    cin >> choice;

    switch (choice){
    case 1: AVLTreeMenu(AVLBirthday, AVLName, AVLID, ABBBirthday, ABBName, ABBID, choice);break;
    case 2: AVLTreeMenu(AVLBirthday, AVLName, AVLID, ABBBirthday, ABBName, ABBID, choice); break;
    case 3: AVLTreeMenu(AVLBirthday, AVLName, AVLID, ABBBirthday, ABBName, ABBID, choice); break;

    case 4: BinarySearchTreeMenu(AVLBirthday, AVLName, AVLID, ABBBirthday, ABBName, ABBID, choice); break;
    case 5: BinarySearchTreeMenu(AVLBirthday, AVLName, AVLID, ABBBirthday, ABBName, ABBID, choice); break;
    case 6: BinarySearchTreeMenu(AVLBirthday, AVLName, AVLID, ABBBirthday, ABBName, ABBID, choice); break;

    case 7: showParameters(AVLBirthday, AVLName, AVLID, ABBBirthday, ABBName, ABBID); break;
    case 0: break;

    default: 
        cout << "Escolha um numero valido";
        int aux = 0;
        StartMenu(AVLBirthday, AVLName, AVLID, ABBBirthday, ABBName, ABBID, aux);
}}}

int main() {
    // Criação da árvore binária com funções de comparação e impressão específicas para data de nascimento
    BinarySearchTree<User> ABBBirthday(compareByBirthday, CompareEqualBirthday, printBirthday);
    BinarySearchTree<User> ABBName(compareByName, CompareEqualName, printName);
    BinarySearchTree<User> ABBID(compareByID, CompareEqualID, printID);

    // Criação da árvore binária com funções de comparação e impressão específicas para data de nascimento
    AVLTree<User> AVLBirthday(compareByBirthday, CompareEqualBirthday, printBirthday);
    AVLTree<User> AVLName(compareByName, CompareEqualName, printName);
    AVLTree<User> AVLID(compareByID, CompareEqualID, printID);

    string filename = "users.csv";

    // Leitura dos usuários a partir de um arquivo CSV
    vector<User> users = readCSV(filename);

    // Inserção dos usuários na árvore
    for (const auto& user : users) {
        AVLBirthday.searchInsert(user);
        AVLName.searchInsert(user);
        AVLID.searchInsert(user);

        ABBBirthday.searchInsert(user);
        ABBName.searchInsert(user);
        ABBID.searchInsert(user);
    }
    int choice = 0;
    StartMenu(AVLBirthday, AVLName, AVLID, ABBBirthday, ABBName, ABBID, choice);

    return 0;
}