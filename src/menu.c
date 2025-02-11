#include <stdio.h>
#include "menu.h"
#include "paciente.h"

// Função que exibe o menu do programa e gerencia a interação com o usuário
void menu() {
    char opcao;
    do {
        printf("1 - Consultar paciente\n");
        printf("2 - Atualizar Paciente\n");
        printf("3 - Remover Paciente\n");
        printf("4 - Inserir Paciente\n");
        printf("5 - Imprimir lista de pacientes\n");
        printf("Q - Sair\n");
        printf("Escolha uma opção: ");
        
        scanf(" %c", &opcao);

        // Executa a ação correspondente à opção escolhida
        switch (opcao) {
            case '1':
                // Chama a função para consultar um paciente
                consultarPaciente();
                break;
            case '2':
                // Chama a função para atualizar os dados de um paciente
                atualizarPaciente();
                break;
            case '3':
                // Chama a função para remover um paciente
                removerPaciente();
                break;
            case '4':
                // Chama a função para inserir um novo paciente
                inserirPaciente();
                break;
            case '5':
                // Chama a função para imprimir a lista de pacientes
                imprimirListaPacientes();
                break;
            case 'Q':
            case 'q':
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 'Q' && opcao != 'q'); // Repete o loop até o usuário escolher sair
}