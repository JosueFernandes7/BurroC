// ISSO GARANTE QUE IFNDEF "IF NOT DEFINED", ou seja se nao foi definido define agora, evita redeclaracao da Structs.h
// https://stackoverflow.com/questions/27810115/what-exactly-do-c-include-guards-do
#ifndef STRUCTS_H
#define STRUCTS_H

// Definição das estruturas (structs) utilizadas no programa

typedef struct carta{   //dados do elemento livro
    char naipe [20];
    int numero;
    struct carta *proximo;
}Carta;

typedef struct elementoDePilha{
    Carta carta;
    struct elementoDePilha *proximo;
}ElementoDePilha;

typedef struct pilha{   //atributos de pilha
    Carta *topo;
    int qtd;
}Pilha;

typedef struct lse {
    Carta *primeiro;
    int n_elementos;
} LSE;

#endif

// O código acima utiliza um "include guard" para evitar a inclusão múltipla
// deste arquivo de cabeçalho em uma única unidade de tradução durante a compilação.
// O guarda de inclusão (ifndef, define, endif) assegura que o conteúdo deste
// arquivo seja incluído apenas se não tiver sido incluído anteriormente. Obtive problema com a struct carta, pois dava redeclaration,
// pois a estáva utilizando tanto na pilha, quanto na lista e quando compilava ele criava 2 vezes a estrutur, com o include guard isso nao
// acontece

