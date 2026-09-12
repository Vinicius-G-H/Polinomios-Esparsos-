# 🧮 Polinômios Esparsos em C

![C Language](https://img.shields.io/badge/Language-C-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Build](https://img.shields.io/badge/Build-Makefile-orange.svg)

Projeto em **Linguagem C** focado no gerenciamento e manipulação de **Polinômios Esparsos** utilizando **listas dinâmicas encadeadas**.

Esta solução otimiza o uso de memória RAM ao armazenar exclusivamente os termos com coeficientes não nulos ($c \cdot x^g$, onde $c 
eq 0$), garantindo alta performance em operações algébricas com grandes expoentes.

---

## 📋 Sumário

- [Estrutura do Projeto](#-estrutura-do-projeto)
- [Funcionalidades e Comandos](#-funcionalidades-e-comandos)
- [Como Compilar e Executar](#-como-compilar-e-executar)
  - [Pré-requisitos](#pré-requisitos)
  - [Compilando com Makefile](#compilando-com-makefile)
  - [Executando os Testes Automatizados](#executando-os-testes-automatizados)
- [Comandos do Interpretador (Entrada Padrão)](#-comandos-do-interpretador-entrada-padrão)
- [Fluxo de Trabalho no GitHub](#-fluxo-de-trabalho-no-github)
- [Licença](#-licença)

---

## 📁 Estrutura do Projeto

```text
.
├── polinomio.h       # Protótipos das funções, macros e definições das estruturas
├── polinomio.c       # Lógica da lista encadeada e operações algébricas
├── main.c            # Processador de comandos via entrada padrão (stdin)
├── Gerador.c         # Gerador automatizado de casos de teste de estresse
├── Makefile          # Regras de compilação rápida e testes de desempenho
└── README.md         # Documentação completa do projeto
```

---

## ⚙️ Funcionalidades e Comandos

O programa lê instruções a partir do `stdin` e suporta as seguintes operações:

| Comando | Sintaxe | Descrição |
| :--- | :--- | :--- |
| **DEF** | `DEF <nome> <k>` | Cria/inicializa um polinômio com o nome especificado |
| **ADD** | `ADD <nome> <coef> <grau>` | Insere um termo $c \cdot x^g$ no polinômio |
| **SOMA** | `SOMA <polA> <polB> <res>` | Soma dois polinômios e armazena em `<res>` |
| **PROD** | `PROD <polA> <polB> <res>` | Multiplica dois polinômios e armazena em `<res>` |
| **ESCALA** | `ESCALA <nome> <c>` | Multiplica todos os coeficientes pelo escalar $c$ |
| **COEF** | `COEF <nome> <grau>` | Retorna o coeficiente do termo de grau $g$ |
| **GRAU** | `GRAU <nome>` | Imprime o grau máximo do polinômio |
| **REMOVE** | `REMOVE <nome> <grau>` | Remove o termo de grau $g$ |
| **REMOVEMENOR**| `REMOVEMENOR <nome>` | Remove o termo de menor grau presente |
| **IMPRIME** | `IMPRIME <nome>` | Imprime os termos do polinômio na ordem padrão |
| **IMPRIMEINV**| `IMPRIMEINV <nome>` | Imprime os termos em ordem inversa |
| **LIBERA** | `LIBERA <nome>` | Libera a memória associada ao polinômio |
| **FIM** | `FIM` | Encerra o interpretador |

---

## 🚀 Como Compilar e Executar

### Pré-requisitos

Certifique-se de ter instalado em sua máquina:
* Compilador `gcc` (suporte a C11 ou superior)
* Utilitário `make`

### Compilando com Makefile

Para compilar todo o projeto de uma só vez, abra o terminal no diretório do projeto e execute:

```bash
make
```

Isso gerará os seguintes executáveis:
- `./programa` (Executável principal que processa a entrada)
- `./gerador` (Gerador de testes esparsos)

### Executando Manualmente

Após compilar, você pode rodar o programa no modo interativo:

```bash
./programa
```

Digite os comandos desejados:
```text
DEF P1 10
ADD P1 5 2
ADD P1 3 0
IMPRIME P1
FIM
```

### Executando os Testes Automatizados

Você pode gerar um arquivo de teste de estresse e medir o tempo de execução com o alvo `run-test`:

```bash
make run-test
```

Para limpar todos os executáveis e arquivos temporários `.o`:

```bash
make clean
```

---

## 🛠️ Fluxo de Trabalho no GitHub

Se você deseja clonar este repositório, fazer alterações e enviar contribuições, siga os comandos abaixo:

### 1. Clonar o Repositório
```bash
git clone https://github.com/SEU-USUARIO/Polinomios-Esparsos.git
cd Polinomios-Esparsos
```

### 2. Criar uma nova Branch para alterações
```bash
git checkout -b minha-feature
```

### 3. Salvar as alterações (Commit e Push)
```bash
git add .
git commit -m "feat: adiciona otimização na inserção ordenada"
git push origin minha-feature
```

---

## 📄 Licença

Este projeto está distribuído sob a licença **MIT**. Veja o arquivo `LICENSE` para mais detalhes.
