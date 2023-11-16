#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Lista.h"
#include "Pilha.h"

// Função para comparar cartas por naipe
int compararCartas(Carta *carta1, Carta *carta2)
{
  if (strcmp(carta1->naipe, carta2->naipe) == 0)
    return 1; // As cartas são de mesmo naipe
  else
    return 0; // As cartas são de naipes diferentes
}

// Estrutura que representa um jogador
typedef struct jogador
{
  char nome[100];
  LSE *cartas;
} Jogador;

// Função para criar o jogador
Jogador *criarJogador(char nome[], LSE *lse)
{
  Jogador *novoJogador = (Jogador *)malloc(sizeof(Jogador));
  strcpy(novoJogador->nome, nome);
  novoJogador->cartas = lse;
  return novoJogador;
}

// Função para mostar a mao do jogador
void mostraMao(Jogador *jogador)
{
  printf("\n\n\tNome %s", jogador->nome);
  mostraLista(jogador->cartas);
}

// Função para mostrar a carta atual em jogo
void mostrarCartaAtual(Carta *cartaAtual)
{
  if (cartaAtual != NULL)
  {
    printf("\nCarta Atual %d de %s", cartaAtual->numero, cartaAtual->naipe);
  }
  else
  {
    printf("\nInsira uma Carta Para iniciar a rodada");
  }
}

// Função para puxar uma carta do baralho e adicioná-la à mão do jogador
void puxarDoBaralho(Jogador *j, Pilha *baralho)
{
  Carta *c = pop(baralho);
  if (c == NULL)
    baralho = inicializarBaralho();
  else
    insereNoInicio(j->cartas, pop(baralho));
}

// Função para obter a escolha do jogador e remover a carta da mão
Carta *obterEscolhaDoJogador(Jogador *jogador)
{
  char naipe[20];
  int numero;
  printf("\nNumero: ");
  scanf("%d", &numero);
  printf("Naipe: ");
  scanf("%s", naipe);
  return removeCarta(jogador->cartas, naipe, numero);
}

// Função principal para realizar a rodada do jogo entre dois jogadores
int jogar(Jogador *jogador, Jogador *jogador2, Pilha *baralho, Carta **cartaAtual)
{
  char naipe[20];
  int numero;
  int trocar = 0;

  mostrarCartaAtual(*cartaAtual);

  // Jogador 1: não pode puxar do baralho, pois ele começa a rodada e define o naipe
   while (1)
  {
    mostraMao(jogador);

    Carta *cartaRemovida = obterEscolhaDoJogador(jogador);
    if (cartaRemovida != NULL)
    {
      *cartaAtual = cartaRemovida;
      
      // se for a ultima carta jogador 1 venceu
      if (jogador->cartas->n_elementos == 0)
      {
        printf("\n%s VENCEU", jogador->nome);
        return 1;
      }
      break;
    }
  }

  // jogador 2
  while (1)
  {
    mostrarCartaAtual(*cartaAtual);
    mostraMao(jogador2);
    int op;
    printf("\n[1] Puxar do Baralho");
    printf("\n[2] Escolher uma Carta\n");
    scanf("%d", &op);
    if (op == 1)
    {
      puxarDoBaralho(jogador2, baralho);
    }
    else
    {
      Carta *cartaRemovida = obterEscolhaDoJogador(jogador2);

      // verifica se tem carta
      if (cartaRemovida != NULL)
      {
        // verifica se é do mesmo naipe
        if (compararCartas(cartaRemovida, *cartaAtual))
        {
          // troca a ordem, pq quem venceu joga a próxima
          if (cartaRemovida->numero > (*cartaAtual)->numero) trocar = 1;
          *cartaAtual = cartaRemovida;

          // se for a última carta, jogador 2 venceu
          if (jogador2->cartas->n_elementos == 0)
          {
            printf("\n%s VENCEU", jogador2->nome);
            return 1;
          }

          break;
        }
        else
        {
          // devolve para a mão se for de naipe diferente
          insereNoInicio(jogador2->cartas, cartaRemovida);
          printf("\nNaipe Diferente, por favor insira uma carta com o naipe de %s", (*cartaAtual)->naipe);
        }
      }
    }
  }

  // Recursivamente chama a função jogar, trocando a ordem dos jogadores se necessário
  if (trocar == 1)
  {
    return jogar(jogador2, jogador, baralho, cartaAtual);
  }
  else
  {
    return jogar(jogador, jogador2, baralho, cartaAtual);
  }

  return 0;
}

// Função principal para iniciar o jogo
void iniciarJogo(Jogador *p1, Jogador *p2, Pilha *baralho)
{
  Carta *cartaAtual = NULL;
  while (1)
  {
    if (jogar(p1, p2, baralho, &cartaAtual))
    {
      break;
    }
  }
}

int main()
{
  // Inicializa e embaralha o baralho
  Pilha *baralho = inicializarBaralho();
  embaralharPilha(baralho);

  // cria os players
  Jogador *p1 = criarJogador("Player 1", criaListaLSE());
  Jogador *p2 = criarJogador("Player 2", criaListaLSE());

  // da as 3 cartas iniciais
  for (int i = 0; i < 3; i++)
  {
    insereNoInicio(p1->cartas, pop(baralho));
    insereNoInicio(p2->cartas, pop(baralho));
  }

  // da start no jogo
  iniciarJogo(p1, p2, baralho);

  // para executar no terminal  gcc -o meuapp Main.c Pilha.c Lista.c
  return 0;
}
