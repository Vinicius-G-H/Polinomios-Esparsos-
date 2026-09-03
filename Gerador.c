#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_GRAU 500000
#define NUM_TERMOS 50000
#define NUM_ESCALAS 20000

void embaralha_graus(int *graus, int tamanho) {
    for (int i = tamanho - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = graus[i];
        graus[i] = graus[j];
        graus[j] = temp;
    }
}

void gerar_polinomio(const char* nome, int* vetor_graus) {
    printf("DEF %s %d\n", nome, NUM_TERMOS);
    
    embaralha_graus(vetor_graus, MAX_GRAU + 1);
    
    for (int i = 0; i < NUM_TERMOS; i++) {
        int grau = vetor_graus[i];
        
        int coef = 0;
        while (coef == 0) {
            coef = (rand() % 2001) - 1000;
        }
        
        printf("%d %d\n", coef, grau);
    }
}

int main(void) {
    srand(time(NULL));

    int *vetor_graus = (int *)malloc((MAX_GRAU + 1) * sizeof(int));
    if (vetor_graus == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória para o vetor de graus.\n");
        return 1;
    }
    for (int i = 0; i <= MAX_GRAU; i++) {
        vetor_graus[i] = i;
    }

    gerar_polinomio("A", vetor_graus);

    for (int i = 0; i < NUM_ESCALAS; i++) {
        int c = (rand() % 2 == 0) ? 1 : -1; 
        printf("ESCALA A %d\n", c);
    }

    printf("IMPRIME A\n");
    printf("GRAU A\n");

    gerar_polinomio("B", vetor_graus);

    printf("SOMA A B R\n");
    printf("FIM\n");

    free(vetor_graus);
   
    return 0;
}
