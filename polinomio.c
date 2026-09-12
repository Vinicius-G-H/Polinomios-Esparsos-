#include <stdio.h>
#include <stdlib.h>
#include "polinomio.h"

typedef struct no_ NO;


struct no_ {
    long long coef;
    long long grau;
    NO *ant;
    NO *prox;
};

struct polinomio_ {
    char nome[100];
    NO *head;
    NO *tail;
};

boolean remover(POLINOMIO *p, long long g) {
    if (p == NULL) return FALSE;

    NO *atual = p->head;
    while (atual != NULL && atual->grau > g) {
        atual = atual->prox;
    }

    if (atual != NULL && atual->grau == g) {
        if (atual->ant != NULL) atual->ant->prox = atual->prox;
        else p->head = atual->prox;

        if (atual->prox != NULL) atual->prox->ant = atual->ant;
        else p->tail = atual->ant;

        free(atual);
        return TRUE;
    }

    return FALSE;
}
boolean remove_menor(POLINOMIO *p) {
    if (p == NULL || p->head == NULL) return FALSE;

    NO *atual = p->tail;
    NO *anterior = atual->ant;

    if (anterior != NULL) anterior->prox = NULL;
    else p->head = NULL;

    p->tail = anterior;
    free(atual);
    return TRUE;
}

long long grau(POLINOMIO *p) {
    if (p == NULL || p->head == NULL) return -1;
    else return p->head->grau;
    
}

void imprimir(POLINOMIO *p) {
    if (p == NULL || p->head == NULL) return FALSE;
    NO *atual = p->head;
    while (atual != NULL) {
    if (atual != p->head) printf(" ");
        printf("%lld*x^%lld", atual->coef, atual->grau);
        atual = atual->prox;
    }
    printf("\n");  
    return;
    }

void imprimir_inv(POLINOMIO *p) {
    if (p == NULL || p->head == NULL) return FALSE;
    NO *atual = p->tail;
    while (atual != NULL) {
        if (atual != p->tail) printf(" ");
        printf("%lld*x^%lld", atual->coef, atual->grau);
        atual = atual->ant;
    }
    printf("\n");
    return;
    }

boolean liberar(POLINOMIO **p) {
    if ((*p) == NULL || (*p)->head == NULL) return FALSE;
    NO *atual = (*p)->head;
    NO *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    free(*p);
    *p = NULL;
    return TRUE;
}
