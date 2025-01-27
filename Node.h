#ifndef NODE_H
#define NODE_H

struct Node{
    Node *direita; // referencia o proximo elemento diferente de zero na mesma linha
    Node *abaixo; // referencia o proximo elemento diferente de zero na mesma coluna
    int linha; // numero da linha que armazena o nó
    int coluna; // numero da coluna que armazena o nó
    double valor; // valor do nó

    //construtor
    Node( int i, int j, double v, Node *prox_abaixo, Node *prox_direita){
        linha = i;
        coluna = j;
        valor = v;
        abaixo = prox_abaixo;
        direita = prox_direita;
    }
};

#endif