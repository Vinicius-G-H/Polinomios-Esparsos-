# Polinômios Esparsos — Estruturas de Dados I (ICMC-USP)

[![C Standard](https://img.shields.io/badge/C-C11-blue.svg)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))
[![License](https://img.shields.io/badge/License-Academic-lightgrey.svg)]()

Repositório referente ao **Trabalho Prático 1** da disciplina **SCC0223 - Estruturas de Dados I** do Instituto de Ciências Matemáticas e de Computação (ICMC-USP). O projeto consiste no desenvolvimento de uma biblioteca e interpretador para manipulação eficiente de **polinômios esparsos**.

---

## 📌 Sobre o Projeto

Em computação científica e álgebra simbólica, polinômios podem atingir graus extremamente elevados (até $10^{18}$), contendo apenas uma pequena fração de termos não nulos. Representar tais polinômios em arrays densos é inviável, pois exigiria quantidades impraticáveis de memória.

A solução é o uso de **estruturas de dados esparsas**, armazenando unicamente os termos com coeficientes diferentes de zero. O programa lê comandos diretamente da entrada padrão (`stdin`) e executa as operações correspondentes até encontrar o comando `FIM`.

---

## 🛠️ Convenções e Especificações Técnicas

Para atender aos requisitos obrigatórios do trabalho, o código adere estritamente aos seguintes padrões:

* **Executável gerado:** `poliesparso`
* **Cabeçalho principal:** `polilista.h`
* **Tipo do termo do polinômio:** `TermoPoli`
* **Constante de capacidade da tabela de nomes:** `CAP_TERMOS_211`
* **Padrão de nomenclatura das funções:** `Funcao_poly_(abreviação_da_funcao_p)`
* **Padrão C:** C11 (especificado via `PADRAO_C11` no `Makefile`)
* **Flags de compilação:** `-Wall -Wextra -O2 -std=c11`

---

## 💻 Comandos Suportados

| Comando | Descrição | Saída |
| :--- | :--- | :--- |
| `DEF nome k` | Define o polinômio `nome` a partir dos $k$ termos fornecidos nas linhas seguintes. | Nenhuma |
| `SOMA A B R` | Computa $R = A + B$. | Nenhuma |
| `PROD A B R` | Computa $R = A \times B$. | Nenhuma |
| `ADD A c g` | Adiciona ao polinômio $A$ o termo de coeficiente $c$ e grau $g$. | Nenhuma |
| `ESCALA A c` | Multiplica todos os coeficientes de $A$ pelo inteiro $c$. | Nenhuma |
| `COEF A g` | Consulta o coeficiente correspondente ao grau $g$ em $A$. | Exibe o coeficiente |
| `REMOVE A g` | Remove de $A$ o termo de grau $g$. | Nenhuma |
| `REMOVEMENOR A` | Remove de $A$ o termo que possui o menor grau. | Nenhuma |
| `GRAU A` | Retorna o maior grau com coeficiente não nulo em $A$ (retorna `-1` caso seja o polinômio nulo). | Exibe o grau |
| `IMPRIME A` | Imprime o polinômio $A$ em ordem canônica (grau decrescente). | Exibe o polinômio |
| `IMPRIMEINV A` | Imprime o polinômio $A$ em ordem crescente de grau. | Exibe o polinômio |
| `LIBERA A` | Desaloca a memória de $A$, tornando o nome indefinido. | Nenhuma |
| `FIM` | Encerra a execução do programa. | Nenhuma |

---

## 🚨 Tratamento de Erros e Retornos

* **Comando não reconhecido:** O programa é encerrado imediatamente com código de retorno **3**.
* **Polinômio não definido:** Imprime a mensagem `erro: polinomio nao definido` no canal de erros (`stderr`) e encerra com código de retorno **2**.

---

## 📊 Limites Operacionais

* **Grau do polinômio:** $0$ a $10^{18}$
* **Coeficientes de entrada:** $-10^3$ a $10^3$
* **Termos por comando `DEF`:** Até $100.000$
* **Polinômios ativos simultaneamente:** Até $512$
* **Comprimento do nome do polinômio:** Até $32$ caracteres
* **Quantidade total de comandos:** Até $200.000$ por execução

---

## 🚀 Como Compilar e Executar

### Compilação do Projeto
Para compilar o código utilizando as flags e variáveis exigidas no `Makefile`:

```bash
make

