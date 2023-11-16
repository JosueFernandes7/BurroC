#include "Structs.h" // Inclui o arquivo de cabeçalho Structs.h

Pilha *criaPilha();
Carta *criaCarta(int numero, char naipe[]);
Carta *pop(Pilha *p);
void push(Pilha *p, Carta *e);
Pilha *inicializarBaralho();
void embaralharPilha(Pilha *p);

