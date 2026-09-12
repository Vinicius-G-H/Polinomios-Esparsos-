#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int buscar_indice(POLINOMIO **vetor, int qtd, const char *nome) {
    if (nome == NULL) {
        return -1;
    }
    for (int i = 0; i < qtd; i++) {
        if (vetor[i] != NULL) {
            const char *nome_p = polinomio_get_nome(vetor[i]);
            if (nome_p != NULL && strcmp(nome_p, nome) == 0) {
                return i;
            }
        }
    }
    return -1;
}

POLINOMIO* buscar_polinomio(POLINOMIO **vetor, int qtd, const char *nome) {  
    if (nome == NULL) {
    return NULL;
    }
    for (int i = 0; i < qtd; i++) {
        if (vetor[i] != NULL) {
            const char *nome_p = polinomio_get_nome(vetor[i]);
            if (nome_p != NULL && strcmp(nome_p, nome) == 0) {
                return vetor[i];
            }
        }
    }
    return NULL;
}
const char *polinomio_get_nome(POLINOMIO *p){
    if (p == NULL){
     return NULL;
    }
    return p->nome;
}

void polinomio_set_nome(POLINOMIO *p, const char *nome) {
    if (p != NULL && nome != NULL) {
        strncpy(p->nome, nome, sizeof(p->nome) - 1);
        p->nome[sizeof(p->nome) - 1] = '\0';
    }
}

POLINOMIO* polinomio_def(const char *nome, int k) {
    POLINOMIO *p = (POLINOMIO *)malloc(sizeof(POLINOMIO));
    if (p == NULL) return NULL;
    if (nome != NULL) {
        strncpy(p->nome, nome, sizeof(p->nome) - 1);
        p->nome[sizeof(p->nome) - 1] = '\0';
    } else {
        p->nome[0] = '\0';
    }

    p->head = NULL;
    p->tail = NULL;

    return p;
}

boolean polinomio_add(POLINOMIO *p, long long c, long long g) {
    if (p == NULL) {
    return FALSE;
    }
    if (c == 0){
     return TRUE; 
    }
    NO *atual = p->head;

    while (atual != NULL && atual->grau > g) {
        atual = atual->prox;
    }

    if (atual != NULL && atual->grau == g) {
        atual->coef += c;
        if (atual->coef == 0) {
            if (atual->ant != NULL) {
                atual->ant->prox = atual->prox;
            } else {
                p->head = atual->prox;
            }

            if (atual->prox != NULL) {
                atual->prox->ant = atual->ant;
            } else {
                p->tail = atual->ant; 
            }

            free(atual);
        }
        return TRUE;
    }

    NO *novo = (NO *)malloc(sizeof(NO));
    if (novo == NULL) {
    return FALSE;
    }

    novo->coef = c;
    novo->grau = g;

    if (atual == p->head) {
        novo->ant = NULL;
        novo->prox = p->head;

        if (p->head != NULL) {
            p->head->ant = novo;
        } else {
            p->tail = novo; 
        }
        p->head = novo;
    }
    else if (atual == NULL) {
        novo->prox = NULL;
        novo->ant = p->tail;

        if (p->tail != NULL) {
            p->tail->prox = novo;
        }
        p->tail = novo;
    }
    else {
        novo->prox = atual;
        novo->ant = atual->ant;
        atual->ant->prox = novo;
        atual->ant = novo;
    }

    return TRUE;
}

boolean polinomio_soma(POLINOMIO *A, POLINOMIO *B, POLINOMIO **R) {
    if (A == NULL || B == NULL || R == NULL) {
    return FALSE;
    }

    *R = (POLINOMIO *)malloc(sizeof(POLINOMIO));
    if (*R == NULL){ 
    return FALSE;
    }

    (*R)->head = NULL;
    (*R)->tail = NULL;
    snprintf((*R)->nome, sizeof((*R)->nome), "(%s)+(%s)", A->nome, B->nome);

    NO *pA = A->head;
    NO *pB = B->head;

    while (pA != NULL || pB != NULL) {
        long long c = 0;
        long long g = 0;

        if (pA != NULL && (pB == NULL || pA->grau > pB->grau)) {
            c = pA->coef;
            g = pA->grau;
            pA = pA->prox;
        }
         else if (pB != NULL && (pA == NULL || pB->grau > pA->grau)) {
            c = pB->coef;
            g = pB->grau;
            pB = pB->prox;
        }
         else { 
            c = pA->coef + pB->coef;
            g = pA->grau;
            pA = pA->prox;
            pB = pB->prox;
        }

        // Adiciona ao final de R apenas se o coeficiente resultante for diferente de zero
        if (c != 0) {
            NO *novo = (NO *)malloc(sizeof(NO));
            if (novo == NULL) {
                NO *atual = (*R)->head;
                while (atual != NULL) {
                    NO *temp = atual;
                    atual = atual->prox;
                    free(temp);
                }
                free(*R);
                *R = NULL;
                return FALSE;
            }

            novo->coef = c;
            novo->grau = g;
            novo->prox = NULL;
            novo->ant = (*R)->tail;

            if ((*R)->tail != NULL) {
                (*R)->tail->prox = novo;
            } else {
                (*R)->head = novo;
            }
            (*R)->tail = novo;
        }
    }

    return TRUE;
}

boolean polinomio_prod(POLINOMIO *A, POLINOMIO *B, POLINOMIO **R) {
    if (A == NULL || B == NULL || R == NULL) return FALSE;

    *R = (POLINOMIO *)malloc(sizeof(POLINOMIO));
    if (*R == NULL) return FALSE;

    (*R)->head = NULL;
    (*R)->tail = NULL;
    snprintf((*R)->nome, sizeof((*R)->nome), "(%s)*(%s)", A->nome, B->nome);

    if (A->head == NULL || B->head == NULL) {
        return TRUE;
    }

    for (NO *pA = A->head; pA != NULL; pA = pA->prox) {
        for (NO *pB = B->head; pB != NULL; pB = pB->prox) {
            long long c = pA->coef * pB->coef;
            long long g = pA->grau + pB->grau;

            if (!polinomio_add(*R, c, g)) {
                NO *atual = (*R)->head;
                while (atual != NULL) {
                    NO *temp = atual;
                    atual = atual->prox;
                    free(temp);
                }
                free(*R);
                *R = NULL;
                return FALSE;
            }
        }
    }

    return TRUE;
}

boolean polinomio_escala(POLINOMIO *p, long long c) {
    if (p == NULL){ 
    return FALSE;
    }

    if (c == 0) {
        NO *atual = p->head;
        while (atual != NULL) {
            NO *temp = atual;
            atual = atual->prox;
            free(temp);
        }
        p->head = NULL;
        p->tail = NULL;
        return TRUE;
    }

    if (c == 1){
     return TRUE;
    }

    NO *atual = p->head;
    while (atual != NULL) {
        atual->coef *= c;
        atual = atual->prox;
    }

    return TRUE;
}

long long polinomio_coef(POLINOMIO *p, long long g) {
    if (p == NULL) return 0;

    NO *atual = p->head;

    while (atual != NULL && atual->grau > g) {
        atual = atual->prox;
    }
    if (atual != NULL && atual->grau == g) {
        return atual->coef;
    }
    return 0;
}

boolean polinomio_remove(POLINOMIO *p, long long g) {
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

boolean polinomio_remove_menor(POLINOMIO *p) {
    if (p == NULL || p->head == NULL) return FALSE;

    NO *atual = p->tail;
    NO *anterior = atual->ant;

    if (anterior != NULL) anterior->prox = NULL;
    else p->head = NULL;

    p->tail = anterior;
    free(atual);
    return TRUE;
}

long long polinomio_grau(POLINOMIO *p) {
    if (p == NULL || p->head == NULL) return -1;
    else return p->head->grau;
    
}

void polinomio_imprimir(POLINOMIO *p) {
    if (p == NULL || p->head == NULL) {
        printf("0\n");
        return; }
    NO *atual = p->head;
    while (atual != NULL) {
    if (atual != p->head) printf(" ");
        printf("%lld*x^%lld", atual->coef, atual->grau);
        atual = atual->prox;
    }
    printf("\n");  
    return;
    }

void polinomio_imprimir_inv(POLINOMIO *p) {
    if (p == NULL || p->head == NULL){
    printf("0\n");
        return; }
    NO *atual = p->tail;
    while (atual != NULL) {
        if (atual != p->tail) printf(" ");
        printf("%lld*x^%lld", atual->coef, atual->grau);
        atual = atual->ant;
    }
    printf("\n");
    return;
    }

boolean polinomio_free(POLINOMIO **p) {
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
