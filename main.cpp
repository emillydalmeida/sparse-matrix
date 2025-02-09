#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include "SparseMatrix.h"
using namespace std;

// vetor de matrizes
vector<SparseMatrix> matrizes;

// menu da interface
void exibirMenu() {
    cout << "-----------------------------------------------\n";
    cout << "         Bem-vindo ao Sistema de Matrizes!     \n";
    cout << "-----------------------------------------------\n";
    cout << "Digite um comando ou 'ajuda' para ver opções:\n";
    cout << "-----------------------------------------------\n";
    cout << "ajuda ............ Mostra a lista de comandos\n";
    cout << "sair ............. Encerra o programa\n";
    cout << "criar m n ........ Cria uma nova matriz MxN\n";
    cout << "mostrar n ........ Exibe a matriz de índice n\n";
    cout << "listar ........... Lista todas as matrizes\n";
    cout << "somar a b ......... Soma matrizes a e b\n";
    cout << "multiplicar a b ... Multiplica matrizes a e b\n";
    cout << "limpar n ......... Limpa matriz n\n";
    cout << "ler .............. Lê uma matriz de um arquivo\n";
    cout << "atualizar n i j v. Atualiza matriz n na posição (i, j) com valor v\n";
    cout << "copiar n ......... Copia a matriz de índice n\n";
    cout << "apagarTudo ....... Remove todas as matrizes\n";
    cout << "-----------------------------------------------\n";
}

// recebe como entrada uma matriz esparsa vazia e o nome do arquivo de entrada
void readSparseMatrix(SparseMatrix& m, const string& nome_do_arquivo) {
    ifstream arquivo(nome_do_arquivo);
    
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo: " << nome_do_arquivo << endl;
        return;
    }
    
    int linhas, colunas;
    arquivo >> linhas >> colunas;
    
    if (linhas != m.getLinha() || colunas != m.getColuna()) {
        cerr << "Erro: Dimensões da matriz no arquivo não correspondem à matriz fornecida." << endl;
        return;
    }
    
    int l, c;
    double valor;

    while (arquivo >> l >> c >> valor) {
        m.insert(l, c, valor);
    }
    
    arquivo.close();

    matrizes.push_back(m);
}

// função para listar as matrizes no comando
void listarMatrizes() {
    if (matrizes.empty()) {
        cout << "Nenhuma matriz criada ainda.\n";
        return;
    }
    cout << "Matrizes criadas:\n";
    for (size_t i = 0; i < matrizes.size(); i++) {
        cout << "Matriz[" << i << "] - Tamanho: " 
             << matrizes[i].getLinha() << "x" << matrizes[i].getColuna() << "\n";
    }
}

// remove uma matriz do vetor no comando
void limparMatriz(int indice) {
    if (indice < 0 || static_cast<size_t>(indice) >= matrizes.size()) { // static_cast<size_t>(indice) está sendo usado para garantir que o valor de indice, que é do tipo int, seja convertido de forma segura para o tipo size_t
        cout << "Índice de matriz inválido!" << endl;
        return;
    }
    
    matrizes.erase(matrizes.begin() + indice);
    cout << "Matriz[" << indice << "] removida com sucesso!" << endl;
}

// recebe como parâmetro as matrizes A e B, devolvendo uma matriz C com o resultado da soma de A e B
SparseMatrix sum(SparseMatrix& A, SparseMatrix& B) {
    if (A.getLinha() != B.getLinha() || A.getColuna() != B.getColuna()) {
        cerr << "Erro: Matrizes de dimensões diferentes não podem ser somadas." << endl;
        exit(EXIT_FAILURE);
    }

    SparseMatrix C(A.getLinha(), A.getColuna());

    // armazena a matriz a na matriz c
    Node* linhaAtual = A.getSentinela()->abaixo;
    while (linhaAtual != A.getSentinela()) {
        Node* atual = linhaAtual->direita;
        while (atual != linhaAtual) {
            C.insert(atual->linha, atual->coluna, atual->valor);
            atual = atual->direita;
        }
        linhaAtual = linhaAtual->abaixo;
    }

    // acrescenta o valor da matriz b na matriz c
    linhaAtual = B.getSentinela()->abaixo;
    while (linhaAtual != B.getSentinela()) {
        Node* atual = linhaAtual->direita;
        while (atual != linhaAtual) {
            double valorAtual = C.get(atual->linha, atual->coluna);
            C.insert(atual->linha, atual->coluna, valorAtual + atual->valor);
            atual = atual->direita;
        }
        linhaAtual = linhaAtual->abaixo;
    }
    return C;
}

// recebe como parâmetro as matrizes A e B, devolvendo uma matriz C com a multiplicação de A por B
SparseMatrix multiply(SparseMatrix& A, SparseMatrix& B) {
    if (A.getColuna() != B.getLinha()) {
        cerr << "Erro: Número de colunas de A deve ser igual ao número de linhas de B!" << endl;
        exit(EXIT_FAILURE);
    }

    SparseMatrix C(A.getLinha(), B.getColuna());

    // percorre as linhas i e colunas j
    for (int i = 1; i <= A.getLinha(); i++) {
        for (int j = 1; j <= B.getColuna(); j++) {
            double soma = 0.0;

            // cálculo do produto escalar entre a linha i de A e a coluna j de B
            for (int k = 1; k <= A.getColuna(); k++) {
                soma += A.get(i, k) * B.get(k, j);
            }

            // adiciona o resultado na matriz c
            C.insert(i, j, soma);
        }
    }
    return C;
}

int main() {
    string comando;
    
    exibirMenu();
    
    // comandos
    while (true) {
        cout << ">> ";
        cin >> comando;

        if (comando == "ajuda") { // comando de ajuda
            exibirMenu();
        } 
        else if (comando == "sair") { // comando para sair
            cout << "Encerrando o programa...\n";
            break;
        } 
        else if (comando == "criar") { // comando para criar matriz no terminal
            int linhas, colunas;
            cin >> linhas >> colunas;
            if (cin.fail() || linhas <= 0 || colunas <= 0) {
                cout << "Erro: Insira valores positivos para linhas e colunas!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // descarta qualquer entrada inválida remanescente no buffer
                continue;
            }
            // adiciona uma nova matriz à lista `matrizes` utilizando `emplace_back`
            matrizes.emplace_back(linhas, colunas);
            cout << "Criada matriz[" << matrizes.size() - 1 << "] com tamanho " << linhas << "x" << colunas << "\n";
        } 
        else if (comando == "mostrar") { // comando para mostrar a matriz n
            int indice;
            cin >> indice;
            if (cin.fail() || indice < 0 || static_cast<size_t>(indice) >= matrizes.size()) {
                cout << "Índice de matriz inválido!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            matrizes[indice].print();
        } 
        else if (comando == "atualizar") { // comando para atualizar um valor da matriz no indice especificado
            int m, i, j;
            double valor;
            cin >> m >> i >> j >> valor;
            if (cin.fail() || m < 0 || static_cast<size_t>(m) >= matrizes.size()) {
                cout << "Índice de matriz inválido!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            matrizes[m].insert(i, j, valor);
            cout << "Matriz[" << m << "] atualizada na posição (" << i << ", " << j << ") com " << valor << "\n";
        } 
        else if (comando == "somar") { // comando para somar duas matrizes
            int a, b;
            cin >> a >> b;
            if (cin.fail() || a < 0 || static_cast<size_t>(a) >= matrizes.size() || b < 0 || static_cast<size_t>(b) >= matrizes.size()) {
                cout << "Índices de matrizes inválidos!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            matrizes.push_back(sum(matrizes[a], matrizes[b]));
            cout << "Resultado da soma armazenado como matriz[" << matrizes.size() - 1 << "]\n";
        }
        else if (comando == "multiplicar") { // comando para multiplicar duas matrizes
            int a, b;
            cin >> a >> b;
            if (cin.fail() || a < 0 || static_cast<size_t>(a) >= matrizes.size() || static_cast<size_t>(b) < 0 || static_cast<size_t>(b) >= matrizes.size()) {
                cout << "Índices de matrizes inválidos!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            matrizes.push_back(multiply(matrizes[a], matrizes[b]));
            cout << "Resultado da multiplicação armazenado como matriz[" << matrizes.size() - 1 << "]\n";
        }
        else if (comando == "listar") { // comando para listar todas as matrizes do vetor
            listarMatrizes();
        }
        else if (comando == "limpar") { // limpar matriz n
            int indice;
            cin >> indice;
            limparMatriz(indice);
        }
        else if (comando == "ler") { // ler um arquivo e salvar a matriz no vetor 
            string nome_arquivo;
            cout << "Digite o nome do arquivo: ";
            cin >> nome_arquivo;
        
            int linhas, colunas;
            cout << "Digite as dimensões da matriz (linhas colunas): ";
            cin >> linhas >> colunas;

            if (cin.fail()) {
                cout << "Erro: entrada inválida para as dimensões da matriz." << endl;
                return 1;
            }
        
            SparseMatrix matriz(linhas, colunas);
        
            ifstream arquivo(nome_arquivo);
            if (!arquivo.is_open()) {
                cout << "Erro ao tentar abrir o arquivo: " << nome_arquivo << endl;
                return 1;
            }
        
            try {
                readSparseMatrix(matriz, nome_arquivo);
            } catch (const ios_base::failure &e) {   // se o arquivo não for lido corretamente, interrompe a execução
                cout << "Erro ao tentar ler o arquivo: " << nome_arquivo << endl;
                return 1;
            }
        
            cout << "Matriz lida com sucesso do arquivo " << nome_arquivo << " e armazenado como matriz [" << matrizes.size() - 1 << "]\n";
        }
        else if (comando == "copiar") { // copiar matriz n para a matriz m
            int indice;
            cin >> indice;
            if (cin.fail() || indice < 0 || static_cast<size_t>(indice) >= matrizes.size()) {
                cout << "Índice de matriz inválido!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            SparseMatrix copia = matrizes[indice]; 
            matrizes.push_back(copia);
            cout << "Matriz[" << indice << "] copiada com sucesso para matriz[" << matrizes.size() - 1 << "]\n";
        }
        else if (comando == "apagarTudo") { // limpar o vetor de matrizes
            matrizes.clear();
            cout << "Todas as matrizes foram apagadas.\n";
        }
    }
    return 0;
}





