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

void polinomio_imprimir_inv(POLINOMIO *p) {
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

const char *polinomio_get_nome(POLINOMIO *p){
    if (p == NULL){
     return NULL;
    }
    return p->nome;
}

void polinomio_set_nome(POLINOMIO *p, const char *nome) {
    if (p != NULL && nome != NULL) {
        strncpy(p->nome, nome, sizeof(p->nome) - 1);
        p->nome[sizeof(p->nome) - 1] = '\0'; // Garante o caractere nulo final
    }
}


static POLINOMIO* buscar_polinomio(POLINOMIO **vetor, int qtd, const char *nome) { //acrescentei aqui, estava na main
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

static int buscar_indice(POLINOMIO **vetor, int qtd, const char *nome) { //acrescentei aqui, estava na main
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


boolean polinomio_add(POLINOMIO *p, long long c, long long g) {
    if (p == NULL) {
    return FALSE;
    }
    if (c == 0){
     return TRUE; // Somar 0 não altera o polinômio
    }

    NO *atual = p->head;

    // Caminha na lista enquanto o grau for maior (ordem decrescente)
    while (atual != NULL && atual->grau > g) {
        atual = atual->prox;
    }

    // Caso 1: Termo com o mesmo grau já existe (soma coeficientes)
    if (atual != NULL && atual->grau == g) {
        atual->coef += c;

        // Se a soma zerou o coeficiente, remove o nó para economizar memória
        if (atual->coef == 0) {
            if (atual->ant != NULL) {
                atual->ant->prox = atual->prox;
            } else {
                p->head = atual->prox; // Atualiza início da lista
            }

            if (atual->prox != NULL) {
                atual->prox->ant = atual->ant;
            } else {
                p->tail = atual->ant; // Atualiza fim da lista
            }

            free(atual);
        }
        return TRUE;
    }

    // Caso 2: Criar novo nó
    NO *novo = (NO *)malloc(sizeof(NO));
    if (novo == NULL) {
    return FALSE;
    }

    novo->coef = c;
    novo->grau = g;

    // Subcaso 2.1: Inserção no início da lista (ou lista vazia)
    if (atual == p->head) {
        novo->ant = NULL;
        novo->prox = p->head;

        if (p->head != NULL) {
            p->head->ant = novo;
        } else {
            p->tail = novo; // Se a lista estava vazia, tail também é atualizado
        }
        p->head = novo;
    }
    // Subcaso 2.2: Inserção no final da lista
    else if (atual == NULL) {
        novo->prox = NULL;
        novo->ant = p->tail;

        if (p->tail != NULL) {
            p->tail->prox = novo;
        }
        p->tail = novo;
    }
    // Subcaso 2.3: Inserção no meio da lista (inserir antes de 'atual')
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

    // Aloca dinamicamente o novo polinômio resultado
    *R = (POLINOMIO *)malloc(sizeof(POLINOMIO));
    if (*R == NULL){ 
    return FALSE;
    }

    (*R)->head = NULL;
    (*R)->tail = NULL;
    snprintf((*R)->nome, sizeof((*R)->nome), "(%s)+(%s)", A->nome, B->nome);

    NO *pA = A->head;
    NO *pB = B->head;

    // Percorre ambas as listas em ordem decrescente de grau (Merge)
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
         else { // graus iguais: soma os coeficientes
            c = pA->coef + pB->coef;
            g = pA->grau;
            pA = pA->prox;
            pB = pB->prox;
        }

        // Adiciona ao final de R apenas se o coeficiente resultante for diferente de zero
        if (c != 0) {
            NO *novo = (NO *)malloc(sizeof(NO));
            if (novo == NULL) {
                // Em caso de falha de alocação, libera o que já foi inserido
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

    // Aloca a estrutura do polinômio resultado
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

    // Se c == 0, o resultado é o polinômio nulo (libera toda a memória)
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

    // Se c == 1, o polinômio permanece inalterado
    if (c == 1){
     return TRUE;
    }

    // Multiplica o coeficiente de cada termo pela escala
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

    // Caminha na lista enquanto os graus forem maiores que g
    while (atual != NULL && atual->grau > g) {
        atual = atual->prox;
    }

    // Se encontrou o nó com o grau desejado
    if (atual != NULL && atual->grau == g) {
        return atual->coef;
    }

    // Se passou do grau ou a lista acabou, o coeficiente é zero
    return 0;
}

POLINOMIO* polinomio_def(const char *nome, int k) {
    POLINOMIO *p = (POLINOMIO *)malloc(sizeof(POLINOMIO));
    if (p == NULL) return NULL;

    // Copia o nome com segurança evitando estouro de buffer
    if (nome != NULL) {
        strncpy(p->nome, nome, sizeof(p->nome) - 1);
        p->nome[sizeof(p->nome) - 1] = '\0';
    } else {
        p->nome[0] = '\0';
    }

    p->head = NULL;
    p->tail = NULL;

    // Adiciona o termo inicial x^k se k for um grau válido
    if (k >= 0) {
        if (!polinomio_add(p, 1, (long long)k)) {
            free(p);
            return NULL;
        }
    }

    return p;
}