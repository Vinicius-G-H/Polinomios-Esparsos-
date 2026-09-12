#ifndef POLINOMIO_H
#define POLINOMIO_H

#define boolean int
#define FALSE 0
#define TRUE 1

typedef struct no_ NO;
typedef struct polinomio_ POLINOMIO;

const char *get_nome(POLINOMIO *p);
void set_nome(POLINOMIO *p, const char *nome);
POLINOMIO *def(const char *nome, int k);
boolean add(POLINOMIO *p, long long c, long long g);
boolean soma(POLINOMIO *A, POLINOMIO *B, POLINOMIO **R);
boolean prod(POLINOMIO *A, POLINOMIO *B, POLINOMIO **R);
boolean escala(POLINOMIO *p, long long c);
long long coef(POLINOMIO *p, long long g);
boolean remover(POLINOMIO *p, long long g);
boolean remove_menor(POLINOMIO *p);
long long grau(POLINOMIO *p);
void imprimir(POLINOMIO *p);
void imprimir_inv(POLINOMIO *p);
boolean Liberar(POLINOMIO **p);

#endif