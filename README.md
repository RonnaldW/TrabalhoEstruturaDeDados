# Sistema de Gerenciamento de Dados de Pacientes

Este projeto consiste em um sistema de gerenciamento de dados de pacientes desenvolvido em linguagem C. O sistema permite o cadastro, consulta, atualização e exclusão de registros de pacientes, armazenando os dados em um arquivo CSV. O objetivo principal é praticar conceitos como listas encadeadas, modularização, manipulação de arquivos e documentação de código.

## Funcionalidades

O sistema oferece as seguintes funcionalidades:

1. **Consultar paciente**: Permite buscar um paciente por nome ou CPF.
2. **Atualizar paciente**: Permite modificar os dados de um paciente existente.
3. **Remover paciente**: Permite excluir um paciente do sistema.
4. **Inserir paciente**: Permite adicionar um novo paciente ao sistema.
5. **Imprimir lista de pacientes**: Exibe todos os pacientes cadastrados no sistema.

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

- **main.c**: Contém a função principal do programa e a lógica do menu.
- **menu.h**: Define as funções e estruturas relacionadas ao menu de interação com o usuário.
- **menu.c**: Implementa as funções do menu, como exibição e tratamento das opções do usuário.
- **paciente.h**: Define a estrutura de dados e as funções relacionadas ao TAD `BDPaciente`.
- **paciente.c**: Implementa as funções do TAD `BDPaciente`.
- **bd_paciente.csv**: Arquivo CSV que armazena os dados dos pacientes.
- **Makefile**: Facilita a compilação do projeto.

## Como executar o Projeto

1. **Clonar o Repositório**
    git clone https://github.com/RonnaldW/TrabalhoEstruturaDeDados.git

2. **Navegar até a pasta**
    cd TrabalhoEstruturaDeDados

3. **Instalar o GCC 11**
    "sudo apt install -y gcc-11" e  no terminal

4. **Compilar o projeto**
    Digitar "make" no terminal


## Decisões de Implementação

**Lista Encadeada**: Optou-se por utilizar uma lista encadeada para armazenar os pacientes em memória, devido à sua flexibilidade e facilidade de manipulação.

**Modularização**: O código foi dividido em módulos para facilitar a manutenção e a compreensão. Cada módulo tem uma responsabilidade clara.

## Requisitos do Ambiente

Sistema Operacional: Linux Ubuntu 22.04

Compilador: GCC 11

## Autores

- [@rafaeldeps](https://www.github.com/rafaeldeps)
- [@ronnaldw](https://www.github.com/ronnaldw)
