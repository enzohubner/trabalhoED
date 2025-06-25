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

typedef struct Node {
    Paciente paciente;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int quantidade;
} ListaPacientes;

void imprimir_cabecalho();

void limparQuebraLinha(char *str);

//void guardar_dados (BDPaciente *bd);

//void imprimir_paciente(Paciente p);

//void consultar_pacientes(BDPaciente *bd);

//void consultar_pelo_cpf(BDPaciente *bd);

//void consultar_pelo_nome(BDPaciente *bd);

//void imprimir_todos_pacientes(BDPaciente *bd);sa
void iniciar_sistema();

void salvar_dados(ListaPacientes *lista);

void guardar_dados(ListaPacientes *lista);

void consultar_pacientes(ListaPacientes *lista);

void consultar_pelo_cpf(ListaPacientes *lista);

void consultar_pelo_nome(ListaPacientes *lista);

void imprimir_todos_pacientes(ListaPacientes *lista);

void imprimir_paciente(Paciente p);

void inserir_paciente(ListaPacientes *lista);

void remover_paciente(ListaPacientes *lista, int id);

void atualizar_paciente(ListaPacientes *lista, Paciente p);

void free_lista(ListaPacientes *lista);

#endif
