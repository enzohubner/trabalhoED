#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bdpaciente.h"

// Remove o caractere '\n' do final da string, se existir
void limparQuebraLinha(char *str) 
{
    str[strcspn(str, "\n")] = '\0';
}

// Converte uma string para minúsculo, armazenando o resultado em 'resultado'
void para_minusculo(char *str, char *resultado) 
{
    int i;
    for (i = 0; str[i]; i++) {
        resultado[i] = tolower(str[i]);
    }
    resultado[i] = '\0';
}

// Valida se o CPF possui 11 dígitos numéricos
int valida_cpf(char *cpf) 
{
    if (strlen(cpf) != 11) {
        return 0;
    }
    for (int i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) {
            return 0;
        }
    }
    return 1;
}

// Insere um paciente na lista encadeada (função interna)
void inserir_paciente_na_lista(ListaPacientes *lista, Paciente p)
{
    Node *novoNode = (Node *)malloc(sizeof(Node));
    if (!novoNode) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    novoNode->paciente = p;
    novoNode->next = NULL;

    // Insere no final da lista
    if (lista->head == NULL) {
        lista->head = novoNode;
    } else {
        Node *atual = lista->head;
        while (atual->next != NULL) {
            atual = atual->next;
        }
        atual->next = novoNode;
    }

    lista->quantidade++;
}

// Obtém o próximo ID sequencial para um novo paciente
int obter_proximo_id(ListaPacientes *lista) 
{
    if (lista->head == NULL) {
        return 1;
    }

    int maior_id = 0;
    Node *atual = lista->head;
    
    while (atual != NULL) {
        if (atual->paciente.ID > maior_id) {
            maior_id = atual->paciente.ID;
        }
        atual = atual->next;
    }
    
    return maior_id + 1;
}

// Interface para inserir um novo paciente via usuário
int inserir_paciente(ListaPacientes *lista)
{
    Paciente novoPaciente;

    // Gera um novo ID sequencial
    novoPaciente.ID = obter_proximo_id(lista);

    printf("Digite o CPF do paciente: ");
    scanf(" %[^\n]", novoPaciente.CPF);
    limparQuebraLinha(novoPaciente.CPF);
    if (!valida_cpf(novoPaciente.CPF)) {
        printf("CPF inválido. Deve conter 11 dígitos numéricos.\n");
        return 0; 
    }
    
    Node *atual = lista->head;
    while (atual != NULL) {
        if (strcmp(atual->paciente.CPF, novoPaciente.CPF) == 0) {
            printf("CPF já existe no sistema. Operação cancelada.\n");
            return 0;
        }
        atual = atual->next;
    }

    printf("Digite o nome do paciente: ");
    scanf(" %[^\n]", novoPaciente.Nome);
    limparQuebraLinha(novoPaciente.Nome);

    printf("Digite a idade do paciente: ");
    scanf("%d", &novoPaciente.Idade);

    printf("Digite a data de cadastro (aaaa-mm-dd): ");
    scanf(" %[^\n]", novoPaciente.Data_Cadastro);
    limparQuebraLinha(novoPaciente.Data_Cadastro);

    // Confirmação antes de inserir
    printf("\nConfirma a inserção do seguinte paciente? (s/n)\n");
    imprimir_paciente(novoPaciente);
    char confirmacao;
    scanf(" %c", &confirmacao);

    if (tolower(confirmacao) != 's') {
        printf("Operação de inserção cancelada.\n");
        return 0; 
    }

    inserir_paciente_na_lista(lista, novoPaciente);
    printf("Paciente inserido com sucesso.\n");
    return 1;
}

// Remove um paciente da lista pelo ID
int remover_paciente(ListaPacientes *lista, int id) 
{
    Node *atual = lista->head;
    Node *anterior = NULL;

    // Busca o paciente pelo ID para mostrar seus dados
    Node *temp = atual;
    while (temp != NULL && temp->paciente.ID != id) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Paciente com ID %d não encontrado.\n", id);
        return 0;
    }

    printf("Paciente encontrado:\n");
    imprimir_cabecalho();
    imprimir_paciente(temp->paciente);
    
    printf("\nTem certeza que deseja remover este paciente? (s/n): ");
    char confirmacao;
    scanf(" %c", &confirmacao);

    if (tolower(confirmacao) != 's') {
        printf("Operação de remoção cancelada.\n");
        return 0; 
    }

    // Busca o paciente pelo ID novamente para remover
    while (atual != NULL && atual->paciente.ID != id) {
        anterior = atual;
        atual = atual->next;
    }

    printf("Paciente removido:\n");
    imprimir_paciente(atual->paciente);

    // Remove o nó da lista
    if (anterior == NULL) {
        lista->head = atual->next; 
    } else {
        anterior->next = atual->next; 
    }

    free(atual);
    lista->quantidade--;
    return 1;
}

// Lê os dados do arquivo CSV e carrega na lista
void guardar_dados(ListaPacientes *lista)
{
    char linha[200];
    FILE *file = fopen("bd_paciente.csv", "r");

    if (!file) {
        printf("Arquivo bd_paciente.csv não encontrado. Iniciando com lista vazia.\n");
        return;
    }

    fgets(linha, sizeof(linha), file); // Pula o cabeçalho

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

        inserir_paciente_na_lista(lista, p);
    }

    fclose(file);
}

// Atualiza os dados de um paciente existente
int atualizar_paciente(ListaPacientes *lista, int id) 
{
    Node *atual = lista->head;

    // Busca o paciente pelo ID
    while (atual != NULL && atual->paciente.ID != id) {
        atual = atual->next;
    }

    if (atual == NULL) {
        printf("Paciente com ID %d não encontrado.\n", id);
        return 0; // Paciente não encontrado
    }

    printf("Paciente encontrado:\n");
    imprimir_paciente(atual->paciente);

    printf("Deseja editar este paciente? (s/n): ");
    char confirmacao;
    scanf(" %c", &confirmacao);

    if (tolower(confirmacao) != 's') {
        printf("Operação de edição cancelada.\n");
        return 0; 
    }

    // Cria uma cópia
    Paciente temp = atual->paciente;

    printf("Digite os novos dados do paciente (use '-' para manter o valor atual):\n");

    // Atualiza nome
    printf("Nome atual: %s\nNovo nome: ", temp.Nome);
    char novoNome[50];
    scanf(" %[^\n]", novoNome);
    if (strcmp(novoNome, "-") != 0) {
        strcpy(temp.Nome, novoNome);
    }

    // Atualiza CPF
    printf("CPF atual: %s\nNovo CPF: ", temp.CPF);
    char novoCPF[15];
    scanf(" %[^\n]", novoCPF);
    if (strcmp(novoCPF, "-") != 0) {
        if (!valida_cpf(novoCPF)) {
            printf("CPF inválido. Operação cancelada.\n");
            return 0;
        }
        // Verifica se o CPF já existe 
        Node *verificacao = lista->head;
        while (verificacao != NULL) {
            if (verificacao->paciente.ID != id && strcmp(verificacao->paciente.CPF, novoCPF) == 0) {
                printf("CPF já existe para outro paciente. Operação cancelada.\n");
                return 0;
            }
            verificacao = verificacao->next;
        }
        
        strcpy(temp.CPF, novoCPF);
    }

    // Atualiza idade
    printf("Idade atual: %d\nNova idade: ", temp.Idade);
    int novaIdade;
    scanf("%d", &novaIdade);
    if (novaIdade != -1) {
        temp.Idade = novaIdade;
    }

    // Atualiza data de cadastro
    printf("Data de cadastro atual: %s\nNova data de cadastro: ", temp.Data_Cadastro);
    char novaDataCadastro[20];
    scanf(" %[^\n]", novaDataCadastro);
    if (strcmp(novaDataCadastro, "-") != 0) {
        strcpy(temp.Data_Cadastro, novaDataCadastro);
    }

    printf("\nConfirma a atualização com os seguintes dados? (s/n)\n");
    imprimir_paciente(temp);
    char confirmacaoFinal;
    scanf(" %c", &confirmacaoFinal);

    if (tolower(confirmacaoFinal) != 's') {
        printf("Operação de atualização cancelada.\n");
        return 0;
    }

    atual->paciente = temp;
    printf("Paciente atualizado com sucesso.\n");
    return 1;
}

// Libera toda a memória alocada para a lista de pacientes
void free_lista(ListaPacientes *lista) 
{
    Node *atual = lista->head;
    Node *proximo;

    while (atual != NULL) {
        proximo = atual->next;
        free(atual);
        atual = proximo;
    }

    lista->head = NULL;
    lista->quantidade = 0;
}

// Imprime os dados de um paciente em formato de tabela
void imprimir_paciente(Paciente p) 
{
    printf("%-5d | %-20s | %-14s | %-5d | %s\n",
           p.ID, p.Nome, p.CPF, p.Idade, p.Data_Cadastro);
}

// Imprime o cabeçalho da tabela de pacientes
void imprimir_cabecalho() 
{
    printf("\n%-5s | %-20s | %-14s | %-5s | %s\n",
           "ID", "Nome", "CPF", "Idade", "Data Cadastro");
    printf("--------------------------------------------------------------\n");
}

// Consulta pacientes pelo nome (busca por substring, case-insensitive)
void consultar_pelo_nome(ListaPacientes *lista) 
{
    char nome[50];
    printf("Digite o nome do paciente: ");
    scanf(" %[^\n]", nome); 
    limparQuebraLinha(nome);

    char nome_minusculo[50];
    para_minusculo(nome, nome_minusculo);

    int encontrou = 0;
    imprimir_cabecalho();

    Node *atual = lista->head;
    while (atual != NULL) 
    {
        char paciente_minusculo[50];
        para_minusculo(atual->paciente.Nome, paciente_minusculo);

        if (strncmp(paciente_minusculo, nome_minusculo, strlen(nome_minusculo)) == 0) 
        {
            imprimir_paciente(atual->paciente);
            encontrou = 1;
        }
        atual = atual->next;
    }

    if (!encontrou) {
        printf("Nenhum paciente encontrado com esse nome.\n");
    }
}

// Consulta pacientes pelo CPF
void consultar_pelo_cpf(ListaPacientes *lista) 
{
    char cpf[15];
    printf("Digite o CPF ou prefixo do CPF do paciente: ");
    scanf(" %[^\n]", cpf); 
    limparQuebraLinha(cpf);

    int encontrou = 0;
    imprimir_cabecalho();

    Node *atual = lista->head;
    while (atual != NULL) 
    {
        if (strncmp(atual->paciente.CPF, cpf, strlen(cpf)) == 0) 
        {
            imprimir_paciente(atual->paciente);
            encontrou = 1;
        }
        atual = atual->next;
    }

    if (!encontrou) {
        printf("Nenhum paciente encontrado com esse CPF ou prefixo.\n");
    }
}

// Menu de consulta de pacientes (por nome ou CPF)
void consultar_pacientes(ListaPacientes *lista) 
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
                consultar_pelo_nome(lista);
                break;
            case 2:
                consultar_pelo_cpf(lista);
                break;
            case 3:
                printf("Voltando ao menu anterior...\n");
                break;
            default:
                printf("Opcao inválida. Tente novamente.\n");
        }
    }
}

// Imprime todos os pacientes cadastrados
void imprimir_todos_pacientes(ListaPacientes *lista)
{
    system("clear");
    imprimir_cabecalho();
    if(lista->quantidade == 0) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }
    Node *atual = lista->head;
    while (atual != NULL) 
    {
        imprimir_paciente(atual->paciente);
        atual = atual->next;
    }
}

// Salva os dados da lista de pacientes no arquivo CSV
void salvar_dados(ListaPacientes *lista) 
{
    FILE *file = fopen("bd_paciente.csv", "w");
    if (!file) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escreve o cabeçalho
    fprintf(file, "ID,CPF,Nome,Idade,Data_Cadastro\n");

    Node *atual = lista->head;
    while (atual != NULL) 
    {
        Paciente p = atual->paciente;
        fprintf(file, "%d,%s,%s,%d,%s\n", p.ID, p.CPF, p.Nome, p.Idade, p.Data_Cadastro);
        atual = atual->next;
    }

    fclose(file);
    printf("Dados salvos com sucesso.\n");
}

// Função principal do sistema, exibe o menu
void iniciar_sistema() {
    ListaPacientes lista;
    lista.head = NULL;
    lista.quantidade = 0;

    // Carrega dados do arquivo, se existir
    guardar_dados(&lista);

    char opcao;
    do {
        printf("\n===== HealthSys - Sistema de Gerenciamento de Pacientes =====\n");
        printf("1 - Consultar paciente\n");
        printf("2 - Atualizar paciente\n");
        printf("3 - Remover paciente\n");
        printf("4 - Inserir paciente\n");
        printf("5 - Imprimir lista de pacientes\n");
        printf("Q - Sair\n");
        printf("Digite a opção desejada: ");
        scanf(" %c", &opcao);

        switch (opcao) {
            case '1':
                consultar_pacientes(&lista);
                break;
            case '2': {
                int id;
                printf("Digite o ID do paciente a ser atualizado: ");
                scanf("%d", &id);
                if (atualizar_paciente(&lista, id)) {
                    salvar_dados(&lista);
                }
                break;
            }
            case '3': {
                int id;
                printf("Digite o ID do paciente a ser removido: ");
                scanf("%d", &id);
                
                if (remover_paciente(&lista, id)) {
                    salvar_dados(&lista);
                }
                break;
            }

            case '4':
                if (inserir_paciente(&lista)) {
                    salvar_dados(&lista);
                }
                
                break;
            case '5':
                imprimir_todos_pacientes(&lista);
                printf("\nPressione ENTER para continuar...");
                getchar();
                getchar();
                break;
            case 'Q':
            case 'q':
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 'Q' && opcao != 'q');
    free_lista(&lista);
}