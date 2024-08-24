// Nomes: Marcio Adriano de Campos Junior N°USP:11871625
//        Isabela da Mata Tiezzi                6697732

#include "FileReader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

// Definição da função auxiliar para converter a data de string para std::tm
std::tm stringToDate(const std::string& date) {
    std::tm tm = {};
    std::istringstream ss(date);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    if (ss.fail()) {
        std::cerr << "Erro ao converter a data: " << date << std::endl;
    }
    return tm;
}

// Definição da função para ler o arquivo CSV e separar os dados em variáveis apropriadas
std::vector<User> readCSV(const std::string& filename) {
    std::vector<User> users;
    std::ifstream file(filename);
    std::string line, word;

    // Verificar se o arquivo foi aberto com sucesso
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return users;
    }

    // Ignorar a primeira linha (cabeçalho)
    std::getline(file, line);

    // Ler o arquivo linha por linha
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        User user;

        // Ler e atribuir ID (inteiro)
        std::getline(ss, word, ',');
        user.id = std::stoi(word);

        // Ler e atribuir Nome (string)
        std::getline(ss, word, ',');
        user.name = word;

        // Ler e atribuir Data de Nascimento (data tm da lib <ctime>)
        std::getline(ss, word, ',');
        user.birthday = stringToDate(word);

        users.push_back(user);
    }

    // Fechar o arquivo
    file.close();
    return users;
}
