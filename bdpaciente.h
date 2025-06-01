#ifndef BDPACIENTE_H
#define BDPACIENTE_H

#define MAX_pacientes 1000

typedef struct {
    int ID;
    char CPF[15];
    char Nome[50];
    int Idade;
    char Data_Cadastro[11];
} Paciente;

typedef struct {
    Paciente pacientes[MAX_pacientes];
    int quantidade;
} BDPaciente;

void imprimir_cabecalho();

void limparQuebraLinha(char *str);

void guardar_dados (BDPaciente *bd);

void imprimir_paciente(Paciente p);

void consultar_pacientes(BDPaciente *bd);

void consultar_pelo_cpf(BDPaciente *bd);

void consultar_pelo_nome(BDPaciente *bd);

void imprimir_todos_pacientes(BDPaciente *bd);

#endif
