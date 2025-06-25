# Sistema de Consulta de Pacientes

Este projeto é um sistema simples em C para gerenciamento e consulta de dados de pacientes, utilizando uma lista ligada (LinkedList) e persistência em arquivo CSV. O sistema permite inserir, consultar, atualizar, remover e listar pacientes.

---

## 📋 Sumário

- [Estrutura do Projeto](#estrutura-do-projeto)
- [Como Executar o Programa](#como-executar-o-programa)
- [Principais TADs (Tipos Abstratos de Dados)](#principais-tads-tipos-abstratos-de-dados)
- [Funcionalidades Implementadas](#funcionalidades-implementadas)
- [Exemplo de Formato do CSV](#exemplo-de-formato-do-csv)
- [Autores](#autores)
- [Observações](#observações)

---

## 📁 Estrutura do Projeto

```
.
├── main.c              # Arquivo principal com o menu e a lógica principal
├── bdpaciente.c        # Funções auxiliares para leitura e manipulação dos dados
├── bdpaciente.h        # Arquivo de cabeçalho com as definições dos TADs e funções
├── bd_paciente.csv     # Base de dados com os pacientes (formato CSV)
├── Makefile            # Automação da compilação do projeto
└── README.md           # Este arquivo
```

---

## 🚀 Como Executar o Programa

### 1. Pré-requisitos

- GCC (ou outro compilador C compatível)
- Sistema operacional Windows ou Linux (ajuste o comando de limpeza de tela se necessário)
- Arquivo `bd_paciente.csv` no mesmo diretório do executável

### 2. Compilação

#### Usando o Makefile

Para compilar:
```bash
make
```

Para executar:
```bash
./meu_programa
```

Para limpar os arquivos gerados:
```bash
make clean
```

#### Compilação Manual

No terminal, execute:
```bash
gcc main.c bdpaciente.c -o meu_programa
./meu_programa
```

---

## 🏗️ Principais TADs (Tipos Abstratos de Dados)

O projeto utiliza os seguintes TADs, definidos em `bdpaciente.h`:

```c
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
```

---

## ✅ Funcionalidades Implementadas
./
O sistema oferece as seguintes operações:

- **Inserir paciente:**  
  Permite cadastrar um novo paciente, preenchendo CPF, nome, idade e data de cadastro. O ID é gerado automaticamente.

- **Consultar paciente:**  
  - Por nome (busca parcial, insensível a maiúsculas/minúsculas)
  - Por CPF (busca exata)

- **Atualizar paciente:**  
  Permite editar os dados de um paciente existente, informando o ID. É possível manter campos inalterados.

- **Remover paciente:**  
  Remove um paciente da lista, informando o ID.

- **Listar todos os pacientes:**  
  Exibe todos os pacientes cadastrados em formato de tabela.

- **Persistência em arquivo:**  
  Todas as alterações (inserção, remoção, atualização) são salvas no arquivo `bd_paciente.csv`.

- **Validação de CPF:**  
  O CPF deve conter exatamente 11 dígitos numéricos.

- **Interface de menu:**  
  Menu interativo no terminal para navegação entre as operações. Ele tambem foi modularizado e apenas chamado no Main.c

---

## ⚙️ Principais Decisões de Implementação

- **Leitura de Dados**: Os dados dos pacientes são carregados de um arquivo CSV (`bd_paciente.csv`) ao iniciar o programa.
- **Busca por Prefixo**: As consultas por nome e CPF são feitas por prefixo, utilizando `strncmp` para comparar o início das strings. Para tornar a busca por nome insensível a maiúsculas/minúsculas, as strings são convertidas para minúsculo antes da comparação.
- **Limpeza de Tela**: O comando `system("clear")` é utilizado para limpar a tela a cada operação, facilitando a visualização. No Windows, pode ser necessário substituir por `system("cls")`.
- **Interface Simples**: O menu principal permite consultar pacientes por nome, por CPF, listar todos os pacientes ou sair do sistema.
- **Tamanho Máximo**: O número máximo de pacientes é definido por `#define MAX_pacientes 1000` para evitar estouro de memória.

---

## 🧪 Exemplo de Formato do CSV

O arquivo `bd_paciente.csv` deve conter os dados separados por vírgulas, com o seguinte cabeçalho:

```
ID,CPF,Nome,Idade,Data_Cadastro
1,12345678900,Ana Silva,30,2024-01-10
2,98765432100,João Costa,45,2023-12-05
```

---

## 👨‍💻 Autores

- Kaio Victor Marroque de Jesus
- Enzo Hubner

Curso: **Sistemas de Informação**  
Disciplina: **Estrutura de Dados**

---

## 📌 Observações

- A busca por nome é feita de forma parcial e insensível a maiúsculas/minúsculas.
- O sistema utiliza lista ligada para armazenar os pacientes em memória.
- O comando de limpeza de tela (`system("clear")`) pode ser alterado para `system("cls")` no Windows.
- O sistema foi desenvolvido para fins didáticos e pode ser expandido com novas funcionalidades.


