#ifndef BDPACIENTE_H
#define BDPACIENTE_H

// Definições completas das estruturas
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

//Utilitarias
void limparQuebraLinha(char *str);
void para_minusculo(char *str, char *resultado);
int valida_cpf(char *cpf);

//Manipulação de Pacientes
void inserir_paciente_na_lista(ListaPacientes *lista, Paciente p);
int obter_proximo_id(ListaPacientes *lista);
int inserir_paciente(ListaPacientes *lista); 
int remover_paciente(ListaPacientes *lista, int id); 
int atualizar_paciente(ListaPacientes *lista, int id);
void free_lista(ListaPacientes *lista);

//Funcoes de exibição
void imprimir_paciente(Paciente p);
void imprimir_cabecalho();
void imprimir_todos_pacientes(ListaPacientes *lista);

//Funções de consulta
void consultar_pelo_nome(ListaPacientes *lista);
void consultar_pelo_cpf(ListaPacientes *lista);
void consultar_pacientes(ListaPacientes *lista);

//Manipulação de dados no arquivo
void salvar_dados(ListaPacientes *lista);
void guardar_dados(ListaPacientes *lista);

//Função principal do sistema
void iniciar_sistema();

#endif