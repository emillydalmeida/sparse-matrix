#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H
#include <iostream>
#include "Node.h"
using namespace std;

class SparseMatrix {
private:
    Node* sentinela; // ponteiro para nó sentinela
    int linha; // numero de linhas da matriz
    int coluna; // numero de colunas da matriz

public:
    // construtor defaut: cria uma matriz esparsa vazia com capacidade para x linhas e z colunas
    SparseMatrix(int linhas, int colunas) {
        this->linha = linhas;
        this->coluna = colunas;

        sentinela = new Node(0, 0, 0, nullptr, nullptr);
        // referencia os ponteiros para tornar a lista circular
        sentinela->abaixo = sentinela;
        sentinela->direita = sentinela;

        Node* atualLinha = sentinela; // aux para circular pela matriz de nó em nó
        for (int i = 1; i <= linhas; i++) {
            Node* novaLinha = new Node(i, 0, 0, nullptr, nullptr);
            novaLinha->abaixo = sentinela;
            atualLinha->abaixo = novaLinha;
            atualLinha = novaLinha;
            atualLinha->direita = atualLinha;
        }
        atualLinha->abaixo = sentinela;
        atualLinha->direita = atualLinha;

        Node* atualColuna = sentinela;
        for (int j = 1; j <= colunas; j++) {
            Node* novaColuna = new Node(0, j, 0, nullptr, nullptr);
            novaColuna->direita = sentinela;
            atualColuna->direita = novaColuna;
            atualColuna = novaColuna;
            atualColuna->abaixo = atualColuna;
        }
        atualColuna->direita = sentinela;
        atualColuna->abaixo = atualColuna;

        std::cout << "Construtor: Matriz esparsa inicializada com sucesso." << std::endl;
    }

    // destrutor: libera toda a memoria alocada dinamicamente
    ~SparseMatrix() {
        Node* linhaAtual = sentinela->abaixo; // aux para receber a linha abaixo da sentinela
        while (linhaAtual != sentinela) {
            Node* proximaLinha = linhaAtual->abaixo; // aux para ser o proximo da linha atual
            Node* atual = linhaAtual->direita; // aux atual para andar pela coluna
            while (atual != linhaAtual) {
                Node* proximo = atual->direita; // aux que vai armazenando o ultimo nó daquela coluna
                delete atual;
                atual = proximo;
            }
            delete linhaAtual;
            linhaAtual = proximaLinha;
        }
        delete sentinela;
    }


    // faz o valor do nó (linha,coluna) ser igual a value
    void insert(int l, int c, double value) {
        
        // verifica se a posição é válida
        if (l <= 0 || l > linha || c <= 0 || c > coluna) {
            std::cerr << "Erro: Posição inválida para inserção (" << l << ", " << c << ")." << std::endl;
            return;
        }

        Node* linhaAtual = sentinela->abaixo; // nó para percorrer o indice desejado da linha
        while (linhaAtual->linha < l) {
            linhaAtual = linhaAtual->abaixo;
        }// linha atual = (i,0)

        Node* colunaAnterior = linhaAtual; 
        Node* colunaAtual = linhaAtual->direita; // nó para percorrer o indice desejado da coluna
        while (colunaAtual != linhaAtual && colunaAtual->coluna < c) {
            colunaAnterior = colunaAtual;
            colunaAtual = colunaAtual->direita;
        }// coluna atual = (i,j)

        Node* colunaAtualPrincipal = sentinela->direita; // nó para percorrer o indice desejado da coluna
        while (colunaAtualPrincipal->coluna < c) {
            colunaAtualPrincipal = colunaAtualPrincipal->direita;
        }// coluna atual = (0,j)

        Node* linhaAnterior = colunaAtualPrincipal;
        Node* linhaAtualPrincipal = colunaAtualPrincipal->abaixo; // nó para percorrer o indice desejado da linha
        while (linhaAtualPrincipal != colunaAtualPrincipal && linhaAtualPrincipal->linha < l) {
            linhaAnterior = linhaAtualPrincipal;
            linhaAtualPrincipal = linhaAtualPrincipal->abaixo;
        }// linha atual = (i,j)

        // verifica se o nó já existe
        if (colunaAtual != linhaAtual && colunaAtual->linha == l && colunaAtual->coluna == c) {
            if (value == 0) { 
                // remove o nó se o valor for 0
                colunaAnterior->direita = colunaAtual->direita;
                linhaAnterior->abaixo = linhaAtualPrincipal->abaixo;
                delete colunaAtual;
            } else {
                colunaAtual->valor = value; // atualiza o valor do nó
            }
            return;
        }

        // insere um novo nó se o valor for diferente de 0
        if (value != 0) {
            Node* novoNo = new Node(l, c, value, linhaAtualPrincipal, colunaAtual);
            colunaAnterior->direita = novoNo;
            linhaAnterior->abaixo = novoNo;
        }
    }

    // devolve o valor do nó(linha,coluna)
    double get(int l, int c){
        if (l <= 0 || l > linha || c <= 0 || c > coluna) {
            std::cerr << "Posição inválida para inserção!" << std::endl; // cerr sendo utilizado para retornar a mensagem assim que o erro acontecer, e não após a execução do programa
            return 0.0;
        }

        Node* linhaSentinela = sentinela->abaixo; // nó para percorrer até a linha desejada
        while (linhaSentinela->linha < l){
            linhaSentinela = linhaSentinela->abaixo;
        }

        Node* atual = linhaSentinela->direita; // nó para percorrer até o indice desejado
        while (atual != linhaSentinela && atual->coluna < c){
            atual = atual->direita;
        }

        if (atual->linha == l && atual->coluna == c){ // retornando o valor do indice
            return atual->valor;
        }
        return 0.0;
    }

    // imprime a matriz no terminal, incluindo os elementos iguais a 0
    void print(){
        for (int i = 1; i <= linha; i++) {
            for (int j = 1; j <= coluna; j++) {
                std::cout << get(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif