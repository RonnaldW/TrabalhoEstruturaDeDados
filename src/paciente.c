#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"

// Estrutura do Paciente
typedef struct BDPaciente
{
    int id;
    char cpf[15];
    char nome[100];
    int idade;
    char data_cadastro[11];
    struct BDPaciente *prox;
} BDPaciente;

// Variável temporária para manipulação de dados do paciente
// Recurso tecnico usado na função atualizarPaciente
BDPaciente temp = {
    .id = 0,
    .cpf = "",
    .nome = "",
    .idade = 0,
    .data_cadastro = "",
    .prox = NULL};

BDPaciente *lista_pacientes = NULL;
int proximo_id = 1; // Contador global para IDs

// Função para formatar CPF
void formatarCPF(char *cpf)
{
    if (strlen(cpf) != 11)
    {
        printf("Erro: O CPF deve conter exatamente 11 dígitos.\n");
        return;
    }
    char formatado[15];
    snprintf(formatado, sizeof(formatado), "%.3s.%.3s.%.3s-%.2s", cpf, cpf + 3, cpf + 6, cpf + 9);
    strcpy(cpf, formatado);
}

// Função para carregar dados do arquivo CSV
void carregarDadosPacientes(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Erro ao abrir o arquivo de dados.\n");
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), file))
    {
        BDPaciente *novo = (BDPaciente *)malloc(sizeof(BDPaciente));
        if (sscanf(linha, "%d,%14[^,],%99[^,],%d,%10[^\n]", &novo->id, novo->cpf,
                   novo->nome, &novo->idade, novo->data_cadastro) != 5)
        {
            printf("Linha inválida ignorada: %s\n", linha);
            free(novo);
            continue;
        }
        if (novo->id >= proximo_id)
            proximo_id = novo->id + 1; // Atualiza o próximo ID disponível
        novo->prox = lista_pacientes;
        lista_pacientes = novo;
    }

    fclose(file);
}

// Função para salvar dados no arquivo CSV
void salvarDadosPacientes(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Erro ao abrir o arquivo de dados.\n");
        return;
    }

    BDPaciente *atual = lista_pacientes;
    while (atual)
    {
        fprintf(file, "%d,%s,%s,%d,%s\n", atual->id, atual->cpf,
                atual->nome, atual->idade, atual->data_cadastro);
        atual = atual->prox;
    }

    fclose(file);
}

// Função para consultar paciente por nome ou CPF
void consultarPaciente()
{
    int opcao;
    char busca[100];
    printf("Escolha o modo de consulta:\n");
    printf("1 - Por nome\n");
    printf("2 - Por CPF\n");
    printf("3 - Retornar ao menu principal\n");
    scanf("%d", &opcao);
    getchar(); // Limpa o buffer

    BDPaciente *atual = lista_pacientes;
    int encontrado = 0;

    switch (opcao)
    {
    case 1:
        printf("Digite o nome: ");
        fgets(busca, sizeof(busca), stdin);
        busca[strcspn(busca, "\n")] = '\0'; // Remover '\n'
        while (atual)
        {
            if (strstr(atual->nome, busca))
            {
                printf("ID: %d, CPF: %s, Nome: %s, Idade: %d, Data de Cadastro: %s\n",
                       atual->id, atual->cpf, atual->nome, atual->idade,
                       atual->data_cadastro);
                encontrado = 1;
            }
            atual = atual->prox;
        }
        break;

    case 2:
        printf("Digite o CPF: ");
        fgets(busca, sizeof(busca), stdin);
        busca[strcspn(busca, "\n")] = '\0'; // Remover '\n'
        formatarCPF(busca);
        while (atual)
        {
            if (strcmp(atual->cpf, busca) == 0)
            {
                printf("ID: %d, CPF: %s, Nome: %s, Idade: %d, Data de Cadastro: %s\n",
                       atual->id, atual->cpf, atual->nome, atual->idade,
                       atual->data_cadastro);
                encontrado = 1;
            }
            atual = atual->prox;
        }
        break;

    case 3:
        return;

    default:
        printf("Opção inválida!\n");
        return;
    }

    if (!encontrado)
    {
        printf("Paciente não encontrado.\n");
    }
}

// Função para atualizar um paciente
void atualizarPaciente()
{
    int id;
    imprimirListaPacientes();
    printf("Digite o ID do paciente a ser atualizado: ");
    scanf("%d", &id);
    getchar(); // Limpa o buffer

    BDPaciente *atual = lista_pacientes;
    while (atual)
    {
        if (atual->id == id)
        {

            BDPaciente temp = *atual;

            printf("Digite o novo valor para os campos CPF (apenas dígitos), Nome, Idade e Data_Cadastro (para manter o valor atual de um campo, digite '-’):\n");

            // CPF
            char cpf[15];
            scanf("%14s", cpf);
            if (strcmp(cpf, "-") != 0)
            {
                strcpy(temp.cpf, cpf);
                formatarCPF(temp.cpf);
            }
            getchar(); // Limpa o buffer

            // Nome
            char nome[100];
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0'; // Remove '\n'
            if (strcmp(nome, "-") != 0)
            {
                strcpy(temp.nome, nome);
            }

            // Idade
            char idadeStr[10];
            fgets(idadeStr, sizeof(idadeStr), stdin);
            if (strcmp(idadeStr, "-") != 0)
            {
                temp.idade = atoi(idadeStr);
            }

            // Data de Cadastro
            char data_cadastro[11];
            fgets(data_cadastro, sizeof(data_cadastro), stdin);
            data_cadastro[strcspn(data_cadastro, "\n")] = '\0'; // Remover '\n'
            if (strcmp(data_cadastro, "-") != 0)
            {
                strcpy(temp.data_cadastro, data_cadastro);
            }

            printf("\nConfirma os novos valores para o registro abaixo? (S/N)\n");
            printf("ID\tCPF\t\tNome\t\t\tIdade\tData de Cadastro\n");
            printf("%d\t%s\t%-20s\t%d\t%s\n", temp.id, temp.cpf, temp.nome, temp.idade, temp.data_cadastro);

            char confirmacao;
            scanf(" %c", &confirmacao);

            if (confirmacao == 'S' || confirmacao == 's')
            {
                *atual = temp;
                printf("Paciente atualizado com sucesso.\n");
                return;
            }
            else
            {
                printf("Operação cancelada.\n");
                return;
            }
        }
        atual = atual->prox;
    }

    printf("Paciente não encontrado.\n");
}

// Função para remover um paciente
void removerPaciente()
{
    int id;
    imprimirListaPacientes();
    printf("Digite o ID do paciente a ser removido: ");
    scanf("%d", &id);

    BDPaciente *atual = lista_pacientes;
    BDPaciente *anterior = NULL;

    while (atual)
    {
        if (atual->id == id)
        {
            printf("Tem certeza de que deseja excluir o registro abaixo? (S/N)\n");
            printf("ID: %d, CPF: %s, Nome: %s, Idade: %d, Data de Cadastro: %s\n",
                   atual->id, atual->cpf,
                   atual->nome,
                   atual->idade,
                   atual->data_cadastro);
            char confirmacao;
            scanf(" %c", &confirmacao);
            if (confirmacao == 'S' || confirmacao == 's')
            {
                if (anterior)
                    anterior->prox = atual->prox;
                else
                    lista_pacientes = atual->prox;

                free(atual);
                printf("Registro removido com sucesso.\n");
                return;
            }
            else
            {
                printf("Operação cancelada.\n");
                return;
            }
        }
        anterior = atual;
        atual = atual->prox;
    }

    printf("Paciente não encontrado.\n");
}

// Função para inserir um novo paciente
void inserirPaciente()
{
    BDPaciente *novo = (BDPaciente *)malloc(sizeof(BDPaciente));
    if (!novo)
    {
        printf("Erro de alocação de memória.\n");
        return;
    }

    printf("Para inserir um novo registro, digite os valores para os campos CPF (apenas dígitos), Nome, Idade e Data_Cadastro:\n");

    // CPF
    scanf("%11s", novo->cpf);
    formatarCPF(novo->cpf);
    getchar(); // Limpa o buffer

    // Nome
    fgets(novo->nome, sizeof(novo->nome), stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';

    // Idade
    while (scanf("%d", &novo->idade) != 1)
    {
        printf("Entrada inválida. Digite um número inteiro para a idade: ");
        while (getchar() != '\n')
            ; // Limpa o buffer
    }
    getchar(); // Limpa o buffer

    // Data de Cadastro
    scanf("%10s", novo->data_cadastro);
    getchar(); // Limpa o buffer

    printf("\nConfirma os valores para o novo registro abaixo? (S/N)\n");
    printf("CPF\t\tNome\t\t\tIdade\tData de Cadastro\n");
    printf("%s\t%-20s\t%d\t%s\n", novo->cpf, novo->nome, novo->idade, novo->data_cadastro);

    char confirmacao;
    scanf(" %c", &confirmacao);

    if (confirmacao == 'S' || confirmacao == 's')
    {

        novo->id = proximo_id++;
        novo->prox = lista_pacientes;
        lista_pacientes = novo;

        printf("Registro inserido com sucesso!\n");
    }
    else
    {
        free(novo);
        printf("Operação cancelada.\n");
    }
}

// Função para imprimir todos os pacientes
void imprimirListaPacientes()
{
    if (lista_pacientes == NULL)
    {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    BDPaciente *atual = lista_pacientes;
    printf("ID\tCPF\t\tNome\t\t\tIdade\tData de Cadastro\n");
    printf("-------------------------------------------------------------\n");

    while (atual)
    {
        printf("%d\t%s\t%-20s\t%d\t%s\n", atual->id, atual->cpf, atual->nome, atual->idade, atual->data_cadastro);
        atual = atual->prox;
    }
}