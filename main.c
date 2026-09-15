#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "polinomio.h"

#define MAX_POLINOMIOS 512


int main(void) {
    POLINOMIO *polinomios[MAX_POLINOMIOS];
    int total_p = 0;
    char cmd[32];

    for (int i = 0; i < MAX_POLINOMIOS; i++) {
        polinomios[i] = NULL;
    }

    while (scanf(" %31s", cmd) == 1) {
        if (strcmp(cmd, "FIM") == 0) {
            break;
        }

        if (strcmp(cmd, "DEF") == 0) {
    char nome[33];
    int k;
    if (scanf(" %32s %d", nome, &k) == 2) {
        POLINOMIO *novo = polinomio_def(nome, k);
    for (int i = 0; i < k; i++) {
        long long c, g;
        if (scanf(" %lld %lld", &c, &g) == 2) {
            if (novo != NULL) polinomio_add(novo, c, g);
        }
    }

        int idx = buscar_indice(polinomios, total_p, nome);
        if (idx != -1) {
            polinomio_free(&polinomios[idx]);
            polinomios[idx] = novo;
        } else {
            int slot = -1;
            for (int i = 0; i < total_p; i++) {
                if (polinomios[i] == NULL) {
                    slot = i;
                    break;
                }
            }
            if (slot != -1) {
                polinomios[slot] = novo;
            } else if (total_p < MAX_POLINOMIOS) {
                polinomios[total_p] = novo;
                total_p++;
            } else {
                polinomio_free(&novo);
            }
        }
    }
}
         else if (strcmp(cmd, "SOMA") == 0) {
            char nomeA[33], nomeB[33], nomeR[33];
            if (scanf(" %32s %32s %32s", nomeA, nomeB, nomeR) == 3) {
                POLINOMIO *A = buscar_polinomio(polinomios, total_p, nomeA);
                POLINOMIO *B = buscar_polinomio(polinomios, total_p, nomeB);
                if (A != NULL && B != NULL) {
                    POLINOMIO *novoR = NULL;
                    polinomio_soma(A, B, &novoR);

                    if (novoR != NULL) {
                        polinomio_set_nome(novoR, nomeR);

                        int idxR = buscar_indice(polinomios, total_p, nomeR);
                        if (idxR != -1) {
                            polinomio_free(&polinomios[idxR]);
                            polinomios[idxR] = novoR;
                        } else {
                            int slot = -1;
                            for (int i = 0; i < total_p; i++) {
                                if (polinomios[i] == NULL) {
                                    slot = i;
                                    break;
                                }
                            }
                            if (slot != -1) {
                                polinomios[slot] = novoR;
                            } else if (total_p < MAX_POLINOMIOS) {
                                polinomios[total_p] = novoR;
                                total_p++;
                            } else {
                                polinomio_free(&novo);
                            }
                        }
                    }
                }
            }
        } else if (strcmp(cmd, "PROD") == 0) {
            char nomeA[33], nomeB[33], nomeR[33];
            if (scanf(" %32s %32s %32s", nomeA, nomeB, nomeR) == 3) {
                POLINOMIO *A = buscar_polinomio(polinomios, total_p, nomeA);
                POLINOMIO *B = buscar_polinomio(polinomios, total_p, nomeB);
                if (A != NULL && B != NULL) {
                    POLINOMIO *novoR = NULL;
                    polinomio_prod(A, B, &novoR);

                    if (novoR != NULL) {
                        polinomio_set_nome(novoR, nomeR);

                        int idxR = buscar_indice(polinomios, total_p, nomeR);
                        if (idxR != -1) {
                            polinomio_free(&polinomios[idxR]);
                            polinomios[idxR] = novoR;
                        } else {
                            int slot = -1;
                            for (int i = 0; i < total_p; i++) {
                                if (polinomios[i] == NULL) {
                                    slot = i;
                                    break;
                                }
                            }
                            if (slot != -1) {
                                polinomios[slot] = novoR;
                            } else if (total_p < MAX_POLINOMIOS) {
                                polinomios[total_p] = novoR;
                                total_p++;
                            } else {
                                polinomio_free(&novo);
                            }
                        }
                    }
                }
            }
        } else if (strcmp(cmd, "ADD") == 0) {
            char nome[33];
            long long c, g;
            if (scanf(" %32s %lld %lld", nome, &c, &g) == 3) {
                POLINOMIO *p = buscar_polinomio(polinomios, total_p, nome);
                if (p != NULL) {
                    polinomio_add(p, c, g);
                }
            }
        } else if (strcmp(cmd, "ESCALA") == 0) {
            char nome[33];
            long long c;
            if (scanf(" %32s %lld", nome, &c) == 2) {
                POLINOMIO *p = buscar_polinomio(polinomios, total_p, nome);
                if (p != NULL) {
                    polinomio_escala(p, c);
                }
            }
        } else if (strcmp(cmd, "COEF") == 0) {
            char nome[33];
            long long g;
            if (scanf(" %32s %lld", nome, &g) == 2) {
                POLINOMIO *p = buscar_polinomio(polinomios, total_p, nome);
                if (p != NULL) {
                    printf("%lld\n", polinomio_coef(p, g));
                } else {
                    printf("0\n");
                }
            }
        } else if (strcmp(cmd, "REMOVE") == 0) {
            char nome[33];
            long long g;
            if (scanf(" %32s %lld", nome, &g) == 2) {
                POLINOMIO *p = buscar_polinomio(polinomios, total_p, nome);
                if (p != NULL) {
                    polinomio_remove(p, g);
                }
            }
        } else if (strcmp(cmd, "REMOVEMENOR") == 0) {
            char nome[33];
            if (scanf(" %32s", nome) == 1) {
                POLINOMIO *p = buscar_polinomio(polinomios, total_p, nome);
                if (p != NULL) {
                    polinomio_remove_menor(p);
                }
            }
        } else if (strcmp(cmd, "GRAU") == 0) {
            char nome[33];
            if (scanf(" %32s", nome) == 1) {
                POLINOMIO *p = buscar_polinomio(polinomios, total_p, nome);
                if (p != NULL) {
                    printf("%lld\n", polinomio_grau(p));
                } else {
                    printf("-1\n");
                }
            }
        } else if (strcmp(cmd, "IMPRIME") == 0) {
            char nome[33];
            if (scanf(" %32s", nome) == 1) {
                POLINOMIO *p = buscar_polinomio(polinomios, total_p, nome);
                if (p != NULL) {
                    polinomio_imprimir(p);
                } else {
                    printf("0\n");
                }
            }
        } else if (strcmp(cmd, "IMPRIMEINV") == 0) {
            char nome[33];
            if (scanf(" %32s", nome) == 1) {
                POLINOMIO *p = buscar_polinomio(polinomios, total_p, nome);
                if (p != NULL) {
                    polinomio_imprimir_inv(p);
                } else {
                    printf("0\n");
                }
            }
        } else if (strcmp(cmd, "LIBERA") == 0) {
            char nome[33];
            if (scanf(" %32s", nome) == 1) {
                int idx = buscar_indice(polinomios, total_p, nome);
                if (idx != -1) {
                    polinomio_free(&polinomios[idx]);
                }
            }
        }
    }

    for (int i = 0; i < total_p; i++) {
        if (polinomios[i] != NULL) {
            polinomio_free(&polinomios[i]);
        }
    }

    return 0;
}
