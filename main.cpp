#include <iostream>
#include "SparseMatrix.h"
using namespace std;

// recebe como entrada uma matriz esparsa vazia e o nome do arquivo de entrada
void readSparseMatrix(SparseMatrix& m, std::string nome_do_arquivo){

}

// recebe como parâmetro as matrizes A e B, devolvendo uma matriz C com o resultado da soma de A e B
//SparseMatrix sum(SparseMatrix& A, SparseMatrix& B){

//}

// recebe como parâmetro as matrizes A e B, devolvendo uma matriz C com a multiplicação de A por B
//SparseMatrix multiply(SparseMatrix& A, SparseMatrix& B){
    
//}

int main() {
    SparseMatrix mat(3, 3);
    mat.insert(1, 1, 10);
    mat.insert(2, 2, 30);
    mat.insert(3, 3, 40);

    mat.print(); // Imprime a matriz inteira no terminal

    double valor = mat.get(2, 2); // Obtém o valor na posição (2, 2)
    std::cout << "Valor na posição (2, 2): " << valor << std::endl; // Exibe o valor no terminal

    return 0;
}


