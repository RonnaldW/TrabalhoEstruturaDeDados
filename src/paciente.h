#ifndef PACIENTE_H
#define PACIENTE_H

void carregarDadosPacientes(const char *filename);
void salvarDadosPacientes(const char *filename);
void consultarPaciente();
void atualizarPaciente();
void removerPaciente();
void inserirPaciente();
void imprimirListaPacientes();
void formatarCPF(char *cpf);

#endif