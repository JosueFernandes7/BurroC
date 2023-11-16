#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Lista.h"

// Funcao para criar uma lista
LSE* criaListaLSE() {
    /* Aloca memória para uma nova lista */
    LSE *nova = (LSE*)malloc(sizeof(LSE));  
    nova->primeiro = NULL;
    nova->n_elementos = 0;
    return nova;
}

// Funcao para mostrar uma carta
void mostraCarta(Carta *novo){
    if(novo != NULL){
        printf("\n\t Naipe:%s",novo->naipe);
        printf("\t Numero:%d",novo->numero);
    }else{
        printf("\n Erro ao imprimir Carta Valor = NULL\n");
    }
}

// Funcao para mostrar a lista
void mostraLista(LSE *ls){
    Carta *aux = ls->primeiro;
    printf("\n\t Cartas:");
    while(aux != NULL){
        mostraCarta(aux);
        aux = aux->proximo;
    }
}

// Funcao para inserir no inicio da lista
void insereNoInicio(LSE *ls, Carta *novo){
    if(ls->primeiro == NULL)
        novo->proximo = NULL;
    else
        novo->proximo = ls->primeiro;
    ls->primeiro = novo;
    ls->n_elementos++;
    // printf("\n Carta %d de %s inserido com sucesso!",novo->numero,novo->naipe);
}

// Funcao para remover uma carta da lista, dado naipe e numero
Carta* removeCarta(LSE *ls, char naipe[], int numero) {
    if (ls->primeiro == NULL) {
        printf("Baralho vazio\n");
        return NULL;
    }

    Carta *aux = ls->primeiro;
    Carta *anterior = NULL;

    while (aux != NULL) {
        if (strcmp(aux->naipe, naipe) == 0 && aux->numero == numero) {
            if (anterior == NULL) {
                // Remoção do primeiro elemento
                ls->primeiro = aux->proximo;
            } else {
                // Remoção de um elemento no meio ou final
                anterior->proximo = aux->proximo;
            }
            aux->proximo = NULL;
            // printf("\nCarta Naipe: %s, Numero: %d removida com sucesso\n", aux->naipe, aux->numero);
            ls->n_elementos--;
            return aux;
        } else {
            anterior = aux;
            aux = aux->proximo;
        }
    }

    printf("\nCarta nao encontrada no baralho tente novamente\n");
    return NULL;
}

