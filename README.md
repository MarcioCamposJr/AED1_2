# Implementação de Árvores Binárias e AVL

Este repositório contém uma implementação de Árvores Binárias de Busca (ABB) e Árvores AVL, desenvolvida para o segundo trabalho da disciplina **Algoritmos e Estruturas de Dados I**. O objetivo do trabalho é aplicar estruturas de árvores para indexar e realizar operações em uma lista de usuários extraída de um arquivo CSV.

## Objetivo

O trabalho foca na implementação de duas opções:

1. **Opção 1:** Implementação genérica de árvores ABB e AVL para indexar qualquer tipo de classe e permitir comparação por diferentes atributos. As árvores serão usadas para armazenar dados de usuários extraídos de um arquivo CSV.
2. **Opção 2:** Implementação de árvores AVL e ABB específicas para cada atributo da classe `User`, incluindo ID, Nome, e Data de Nascimento.

## Estrutura do Projeto

- **main.cpp**: Arquivo principal contendo a função `main()` responsável por criar, manipular e realizar operações de busca, inserção e remoção nas árvores ABB e AVL.
- **AEDI_Trabalho_Trees.pdf**: Documento com a descrição completa da tarefa, fornecendo instruções e métricas que devem ser extraídas após as inserções.

## Requisitos

- **Linguagem**: C++
- **Compilador**: g++ ou outro compilador C++ compatível.

## Funcionalidades

O programa principal oferece as seguintes funcionalidades:

1. **Inserção**: Inserir usuários nas árvores ABB e AVL por diferentes critérios (ID, Nome, Data de Nascimento).
2. **Busca**: Buscar uma tupla específica em qualquer uma das árvores.
3. **Remoção**: Remover uma tupla de todas as árvores.
4. **Métricas**: Extração de métricas como número de comparações na inserção, rotações realizadas nas árvores AVL, e outras métricas descritas no PDF da atividade.

## Execução

1. Compile o código:
   ```bash
   g++ main.cpp FileReader.cpp ABB.cpp AVL.cpp -o arvore
