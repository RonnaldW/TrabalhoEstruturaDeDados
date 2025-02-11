#include <stdio.h>
#include "menu.h"
#include "paciente.h"

// Função principal do programa
int main() {
    // Carrega os dados dos pacientes a partir de um arquivo CSV
    // A função carregarDadosPacientes lê os dados do arquivo especificado e os armazena em uma estrutura de dados apropriada
    carregarDadosPacientes("data/bd_paciente.csv");
    
    // Chama a função que exibe o menu do programa
    // A função menu apresenta as opções disponíveis para o usuário e gerencia a interação com o mesmo
    menu();
    
    // Salva os dados dos pacientes em um arquivo CSV
    // A função salvarDadosPacientes escreve os dados da estrutura de dados em um arquivo CSV, preservando as alterações feitas durante a execução do programa
    salvarDadosPacientes("data/bd_paciente.csv");

    return 0;
}