#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Define estrutura

typedef struct Sala {
    char nome[40];
    struct Sala *esq;
    struct Sala *dir;
} Sala;

// Cria a sala

Sala* criarSala(const char* nome) {
    Sala* s = (Sala*) malloc(sizeof(Sala));
    if (s == NULL) {
        printf("Erro de memoria.\n");
        exit(1);
    }
    strcpy(s->nome, nome);
    s->esq = NULL;
    s->dir = NULL;
    return s;
}

// Libera a sala

void liberar(Sala* r) {
    if (r != NULL) {
        liberar(r->esq);
        liberar(r->dir);
        free(r);
    }
}

// Explora a sala

void explorarSalas(Sala* raiz) {
    Sala* atual = raiz;
    char op;

    if (atual == NULL) {
        printf("Mapa vazio.\n");
        return;
    }

    printf("=== Detective Quest ===\n");

    while (1) {
        printf("\nVoce esta em: %s\n", atual->nome);

        if (atual->esq == NULL && atual->dir == NULL) {
            printf("Fim do percurso.\n");
            break;
        }

        printf("Escolha: ");
        if (atual->esq) printf("[e] esquerda ");
        if (atual->dir) printf("[d] direita ");
        printf("[s] sair\n> ");

        if (scanf(" %c", &op) != 1) break;

        if (op == 's') {
            printf("Exploracao encerrada.\n");
            break;
        } else if (op == 'e' && atual->esq != NULL) {
            atual = atual->esq;
        } else if (op == 'd' && atual->dir != NULL) {
            atual = atual->dir;
        } else {
            printf("Opcao invalida para esta sala.\n");
        }
    }

    printf("=== Fim ===\n");
}

int main(void) {

    Sala* hall = criarSala("Hall de Entrada");
    hall->esq = criarSala("Sala de Estar");
    hall->dir = criarSala("Biblioteca");

    hall->esq->esq = criarSala("Quarto de Hospedes");
    hall->esq->dir = criarSala("Cozinha");

    hall->dir->esq = criarSala("Escritorio");
    hall->dir->dir = criarSala("Jardim de Inverno");

    explorarSalas(hall);
    liberar(hall);
    return 0;
}
