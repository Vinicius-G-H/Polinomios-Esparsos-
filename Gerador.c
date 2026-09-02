#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_GRAU 500000
#define NUM_TERMOS 50000
#define NUM_ESCALAS 20000

/* Função para embaralhar o vetor (Fisher-Yates)
   Garante a escolha de graus sem repetição */
void embaralha_graus(int *graus, int tamanho) {
    for (int i = tamanho - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = graus[i];
        graus[i] = graus[j];
        graus[j] = temp;
    }
}

/* Gera o bloco DEF de um polinômio conforme o enunciado */
void gerar_polinomio(const char* nome, int* vetor_graus) {
    printf("DEF %s %d\n", nome, NUM_TERMOS);
    
    // Embaralha para pegar NUM_TERMOS aleatórios não repetidos
    embaralha_graus(vetor_graus, MAX_GRAU + 1);
    
    for (int i = 0; i < NUM_TERMOS; i++) {
        int grau = vetor_graus[i];
        
        // Sorteia coeficiente entre -1000 e 1000, garantindo que não seja 0
        int coef = 0;
        while (coef == 0) {
            coef = (rand() % 2001) - 1000;
        }
        
        printf("%d %d\n", coef, grau);
    }
}

int main(void) {
    // Semente baseada no tempo para gerar entradas diferentes a cada execução
    srand(time(NULL));

    // Cria e inicializa o vetor de domínio dos graus [0, 500.000]
    int *vetor_graus = (int *)malloc((MAX_GRAU + 1) * sizeof(int));
    if (vetor_graus == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória para o vetor de graus.\n");
        return 1;
    }
    for (int i = 0; i <= MAX_GRAU; i++) {
        vetor_graus[i] = i;
    }

    // 1. Gera o primeiro polinômio A (50.000 termos)
    gerar_polinomio("A", vetor_graus);

    // 2. Imprime 20.000 comandos ESCALA em sequência 
    // com fator -1 ou 1 (para garantir que nunca seja 0, conforme o edital)
    for (int i = 0; i < NUM_ESCALAS; i++) {
        int c = (rand() % 2 == 0) ? 1 : -1; 
        printf("ESCALA A %d\n", c);
    }

    // 3. Imprime as consultas solicitadas
    printf("IMPRIME A\n");
    printf("GRAU A\n");

    // 4. Gera o segundo polinômio B do mesmo jeito
    gerar_polinomio("B", vetor_graus);

    // 5. Soma os dois polinômios
    printf("SOMA A B R\n");

    // 6. Encerra a execução
    printf("FIM\n");

    free(vetor_graus);
    return 0;
}
