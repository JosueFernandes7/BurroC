#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Pilha.h"

// Funcao para criar a pilha
Pilha *criaPilha()
{
  // cria estrutura para pilha
  Pilha *p = (Pilha *)malloc(sizeof(Pilha));
  p->topo = NULL;
  p->qtd = 0;
  return p;
}


Carta *criaCarta(int numero, char naipe[])
{
  Carta *e = (Carta *)malloc(sizeof(Carta));
  e->proximo = NULL;
  e->numero = numero;
  strcpy(e->naipe, naipe);

  return e;
}

// Incrementa ao ultimo item da pilha
void push(Pilha *p, Carta *e)
{
  e->proximo = p->topo;
  p->topo = e;
  p->qtd++;
}

// Remove o ultimo item da pilha
Carta *pop(Pilha *p)
{
  // salta um Carta da pilha
  Carta *aux = p->topo;
  if (aux == NULL)
  {
    printf("\n -- Nao pode realizar POP - Pilha Vazia\n");
  }
  else
  {
    aux = p->topo;
    p->topo = p->topo->proximo;
    p->qtd--;
    aux->proximo = NULL;
  }
  return aux;
}

// Funcao para criar o baralho
Pilha *inicializarBaralho() {
    Pilha *p = criaPilha();
    char naipes[4][10] = {"copas", "espadas", "ouros", "paus"};
    srand(time(NULL));

    // Adiciona 13 cartas de cada naipe ao baralho
    for(int i = 0; i < 4; i++) {
        for(int j = 1; j <= 13; j++) {
            Carta *e = criaCarta(j, naipes[i]);
            push(p, e);
        }
    }

    return p;
}

// Funcao para Embaralhar os itens da pilha
void embaralharPilha(Pilha *p) {
  
    Carta *elementos[52];
    int i, j;
    int qtd = p->qtd;
    srand(time(NULL));

    // Cria um array de elementosDePilha
    Carta *aux = p->topo;
    for (i = 0; i < p->qtd; i++) {
        elementos[i] = aux;
        aux = aux->proximo;
    }

    // Embaralhar os elementos usando o algoritmo Fisher-Yates
    // fonte: https://rockprogramacaoegames.com.br/programacao/como-embaralhar-listas-em-c-utilizando-o-algoritmo-de-fisher-yates/#O_algoritmo_na_pratica
    
    // a ideia e partir do último indice do array para até o primeiro,por exemplo se sao 52 posicoes no caso do jogo de cartas
    for (i = p->qtd - 1; i > 0; i--) {
        
        // j = rand % (52) ou seja j tem 52 posibilidades 0 a 51 e vai caindo de acordo com o i, 0 a 50, 0 a 49 ... até 0, 1
        // em resumo a posicao i pode trocar com todos que estao abaixo dela na lista do array [1,2,3,4,5] , 5 pode trocar com 1,2,3,4
        j = rand() % (i + 1);

        // Troca elementos[i] com elementos[j]
        // pego elemento na posicao i
        Carta *temp = elementos[i];
        // na pos i vai vir um elemento aleatorio de uma posicao j vinda do rand
        elementos[i] = elementos[j];
        // na pos j eu devolvo o que eu removi do i inicial assim efetuando a troca
        elementos[j] = temp;
    }

    // Limpa a pilha original
    while (p->topo != NULL) {
        Carta* e = pop(p);
        // nao posso dar free, pois eles ainda estao na memoria, só que no array desordenado
    }

    // Reorganiza a pilha com os elementos embaralhados
    for (i = 0; i < qtd; i++) {
        push(p, elementos[i]);
    }
}







