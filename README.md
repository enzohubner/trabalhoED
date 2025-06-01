# Sistema de Consulta de Pacientes

Este projeto é um sistema simples em C para gerenciamento e consulta de dados de pacientes, utilizando como base um arquivo CSV. O sistema permite buscar pacientes por nome ou CPF e listar todos os pacientes cadastrados.

---

## 📋 Sumário

- [Estrutura do Projeto](#estrutura-do-projeto)
- [Como Executar o Programa](#como-executar-o-programa)
- [Principais TADs (Tipos Abstratos de Dados)](#principais-tads-tipos-abstratos-de-dados)
- [Principais Decisões de Implementação](#principais-decisoes-de-implementacao)
- [Exemplo de Formato do CSV](#exemplo-de-formato-do-csv)
- [Autores](#autores)

---

## 📁 Estrutura do Projeto

```
.
├── main.c              # Arquivo principal com o menu e a lógica principal
├── bdpaciente.c        # Funções auxiliares para leitura e consulta de dados
├── bdpaciente.h        # Arquivo de cabeçalho com as definições dos TADs e funções
├── bd_paciente.csv     # Base de dados com os pacientes (formato CSV)
├── Makefile            # Automação da compilação do projeto
└── README.md           # Este arquivo
```

---

## 🚀 Como Executar o Programa

### 1. Pré-requisitos

- GCC (ou outro compilador C compatível)
- Sistema operacional Windows (ou Linux, adaptando o comando de limpeza de tela)
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

O projeto utiliza dois TADs principais, definidos em `bdpaciente.h`:

```c
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
```

- **Paciente**: representa um paciente, com campos para ID, CPF, nome, idade e data de cadastro.
- **BDPaciente**: representa a base de dados de pacientes, armazenando um vetor de pacientes e a quantidade cadastrada.

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

- A busca por nome e CPF é feita por prefixo. Para busca parcial em qualquer parte do nome ou CPF, pode-se substituir `strncmp` por `strstr`.
- O sistema foi desenvolvido para fins didáticos e pode ser expandido com funcionalidades como adição, edição e remoção de pacientes.