#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bdpaciente.h"

// Função para remover o '\n' do final da string
void limparQuebraLinha(char *str) 
{
    str[strcspn(str, "\n")] = '\0';
}

// Função para converter string para minúsculo
void para_minusculo(char *str, char *resultado) 
{
    int i;
    for (i = 0; str[i]; i++) {
        resultado[i] = tolower(str[i]);
    }
    resultado[i] = '\0';
}

// Função para ler o arquivo CSV e armazenar os dados no vetor
void guardar_dados(BDPaciente *bd) 
{
    char linha[200];
    FILE *file = fopen("bd_paciente.csv", "r");

    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fgets(linha, sizeof(linha), file); // Pula a primeira linha (cabeçalho)

    while (fgets(linha, sizeof(linha), file) != NULL) 
    {
        Paciente p;
        char *token = strtok(linha, ",");

        p.ID = atoi(token);

        token = strtok(NULL, ",");
        strcpy(p.CPF, token);
        limparQuebraLinha(p.CPF);

        token = strtok(NULL, ",");
        strcpy(p.Nome, token);
        limparQuebraLinha(p.Nome);

        token = strtok(NULL, ",");
        p.Idade = atoi(token);

        token = strtok(NULL, ",");
        strcpy(p.Data_Cadastro, token);
        limparQuebraLinha(p.Data_Cadastro);

        bd->pacientes[bd->quantidade++] = p;
    }

    fclose(file);
}

// Função auxiliar para imprimir os dados de um paciente
void imprimir_paciente(Paciente p) 
{
    printf("%-5d | %-20s | %-14s | %-5d | %s\n",
           p.ID, p.Nome, p.CPF, p.Idade, p.Data_Cadastro);
}

// Função para imprimir o cabeçalho da tabela
void imprimir_cabecalho() 
{
    printf("\n%-5s | %-20s | %-14s | %-5s | %s\n",
           "ID", "Nome", "CPF", "Idade", "Data Cadastro");
    printf("--------------------------------------------------------------\n");
}

// Função para consultar os pacientes pelo nome (prefixo)
void consultar_pelo_nome(BDPaciente *bd) 
{
    char nome[50];
    char nome_lower[50];
    char paciente_nome_lower[50];
    
    printf("Digite o nome ou parte do nome do paciente: ");
    scanf(" %[^\n]", nome); 
    limparQuebraLinha(nome);
    para_minusculo(nome, nome_lower);

    int encontrou = 0;
    imprimir_cabecalho();

    for (int i = 0; i < bd->quantidade; i++) 
    {
        para_minusculo(bd->pacientes[i].Nome, paciente_nome_lower);
        if (strncmp(paciente_nome_lower, nome_lower, strlen(nome_lower)) == 0) 
        {
            imprimir_paciente(bd->pacientes[i]);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum paciente encontrado com esse nome.\n");
    }
}

// Função para consultar os pacientes pelo CPF
void consultar_pelo_cpf(BDPaciente *bd) 
{
    char cpf[15];
    printf("Digite o CPF ou parte do CPF do paciente: ");
    scanf(" %[^\n]", cpf); 
    limparQuebraLinha(cpf);

    int encontrou = 0;
    imprimir_cabecalho();

    for (int i = 0; i < bd->quantidade; i++) 
    {
        if (strncmp(bd->pacientes[i].CPF, cpf, strlen(cpf)) == 0) 
        {
            imprimir_paciente(bd->pacientes[i]);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum paciente encontrado com esse CPF.\n");
    }
}

// Função principal de consulta
void consultar_pacientes(BDPaciente *bd) 
{
    system("clear");

    int opcao = 0;
    while (opcao != 3) 
    {
        printf("\n===== CONSULTAR PACIENTES =====\n");
        printf("1 - Consultar por nome\n");
        printf("2 - Consultar por CPF\n");
        printf("3 - Voltar\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        system("clear"); 

        switch (opcao) {
            case 1:
                consultar_pelo_nome(bd);
                break;
            case 2:
                consultar_pelo_cpf(bd);
                break;
            case 3:
                printf("Voltando ao menu anterior...\n");
                break;
            default:
                printf("Opcao inválida. Tente novamente.\n");
        }
    }
}

void imprimir_todos_pacientes(BDPaciente *bd)
{
    system("clear");
    imprimir_cabecalho();
    if (bd->quantidade == 0) 
    {
        printf("Nenhum paciente registrado");
    }
    for (int i = 0; i < bd->quantidade; i++)
    {
        imprimir_paciente(bd->pacientes[i]);
    }
}