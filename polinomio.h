#ifndef POLINOMIO_H
#define POLINOMIO_H

#define boolean int
#define FALSE 0
#define TRUE 1

typedef struct no_ NO;
typedef struct polinomio_ POLINOMIO;

const char *polinomio_get_nome(POLINOMIO *p);
void polinomio_set_nome(POLINOMIO *p, const char *nome);
POLINOMIO* polinomio_def(const char *nome, int k);
boolean polinomio_add(POLINOMIO *p, long long c, long long g);
boolean polinomio_soma(POLINOMIO *A, POLINOMIO *B, POLINOMIO **R);
boolean polinomio_prod(POLINOMIO *A, POLINOMIO *B, POLINOMIO **R);
boolean polinomio_escala(POLINOMIO *p, long long c);
long long polinomio_coef(POLINOMIO *p, long long g);
boolean polinomio_remove(POLINOMIO *p, long long g);
boolean polinomio_remove_menor(POLINOMIO *p);
long long polinomio_grau(POLINOMIO *p);
void polinomio_imprimir(POLINOMIO *p);
void polinomio_imprimir_inv(POLINOMIO *p);
boolean polinomio_free(POLINOMIO **p);
int buscar_indice(POLINOMIO **vetor, int qtd, const char *nome) ; //coloquei aqui
POLINOMIO* buscar_polinomio(POLINOMIO **vetor, int qtd, const char *nome); //coloquei aqui

#endif
