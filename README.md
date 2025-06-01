
# Sistema de Consulta de Pacientes

Este é um sistema simples em C para gerenciamento e consulta de dados de pacientes, utilizando como base um arquivo CSV. O sistema permite buscar pacientes por nome ou CPF e listar todos os pacientes cadastrados.

## 📁 Estrutura do Projeto

```
.
├── main.c              # Arquivo principal com o menu e a lógica principal
├── bdpaciente.c        # Funções auxiliares para leitura e consulta de dados
├── bdpaciente.h        # Arquivo de cabeçalho com as definições
├── bd_paciente.csv     # Base de dados com os pacientes (formato CSV)
├── Makefile            # Automação da compilação do projeto
└── README.md           # Este arquivo
```

## ⚙️ Funcionalidades

- 📄 Carregar dados dos pacientes de um arquivo CSV.
- 🔍 Consultar pacientes por nome (com busca por prefixo ou parte do nome).
- 🔍 Consultar pacientes por CPF (com busca por prefixo ou parte do CPF).
- 📋 Listar todos os pacientes cadastrados.
- 🧼 Limpeza de tela para facilitar a visualização.

## 🧪 Exemplo de Formato do CSV

O arquivo `bd_paciente.csv` deve conter os dados separados por vírgulas, com o seguinte cabeçalho:

```
ID,CPF,Nome,Idade,Data_Cadastro
1,12345678900,Ana Silva,30,2024-01-10
2,98765432100,João Costa,45,2023-12-05
```

## 🚀 Como Compilar e Executar

### Usando o Makefile

Para compilar:
```bash
make
```

Para executar:
```bash
./main.exe   # No Windows
```

Para limpar os arquivos gerados:
```bash
make clean
```

### Compilação Manual

```bash
gcc main.c bdpaciente.c -o main.exe
./main.exe
```

## 💻 Requisitos

- GCC (ou outro compilador C compatível)
- Sistema operacional Windows (ou adaptação para Linux se usar `clear` em vez de `cls`)
- Arquivo `bd_paciente.csv` no mesmo diretório

## 📌 Observações

- A busca por nome e CPF é feita por prefixo. Para busca parcial em qualquer parte do nome ou CPF, pode-se substituir `strncmp` por `strstr`.
- O sistema foi feito para fins didáticos e pode ser expandido com funcionalidades como adição, edição e remoção de pacientes.

## 👨‍💻 Autores

- Kaio Victor Marroque de Jesus
- Enzo Hubner

Curso: **Sistemas de Informação**  
Disciplina: **Estrutura de Dados**
