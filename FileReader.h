// Nomes: Marcio Adriano de Campos Junior N°USP:11871625
//        Isabela da Mata Tiezzi                6697732

#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <vector>
#include <ctime>

// Estrutura para armazenar os dados do usuário
struct User {
    int id = 0;
    std::string name = "";
    std::tm birthday;
};

// Declaração da função auxiliar para converter a data de string para std::tm
std::tm stringToDate(const std::string& date);

// Declaração da função para ler o arquivo CSV e separar os dados em variáveis apropriadas
std::vector<User> readCSV(const std::string& filename);

#endif // FILEREADER_H
