// Autor: Marius Jabami (mariusjabami)
// Startup: λχ Corp. (lambdachi)
// Repositório: https://github.com/mariusjabami/synap
//
// Descrição:
//   Código escrito como parte dos meus estudos sobre redes neurais.
//   Implementação de um modelo não-linear em C++ com gradiente
//   descendente manual para ajuste de dois pesos (w1, w2) e um bias (b).
//
// Conceitos abordados:
//   - Funções numéricas
//   - Função de erro quadrático (MSE)
//   - Gradiente descendente
//   - Atualização de pesos e bias
//   - Funções lineares vs. não-lineares
//
// Total de parâmetros: 3 (2 pesos + 1 bias)
// Licença: Open Source (créditos obrigatórios)


#include<iostream>
#include<cmath>
#include<vector>

std::vector<double> X = {-2, -1, -1, 0, 1, 1, 2, 2};
std::vector<double> Z = {-2, -1, 1, 0, -1, 1, -1, 2};
std::vector<double> y = {
    (-2 * -2 * 2) + (pow(-2 * -2, 2) * 0.5) + 1,
    (-1 * -1 * 2) + (pow(-1 * -1, 2) * 0.5) + 1,
    (-1 *  1 * 2) + (pow(-1 *  1, 2) * 0.5) + 1,
    ( 0  *  0 * 2) + (pow( 0 *  0, 2) * 0.5) + 1,
    ( 1  * -1 * 2) + (pow( 1 * -1, 2) * 0.5) + 1,
    ( 1  *  1 * 2) + (pow( 1 *  1, 2) * 0.5) + 1,
    ( 2  * -1 * 2) + (pow( 2 * -1, 2) * 0.5) + 1,
    ( 2  *  2 * 2) + (pow( 2 *  2, 2) * 0.5) + 1
};

// FUNÇÃO NUMÉRICA

template<typename Func>
double derivate(Func f, double x, double h) {
    return ( f(x + h) - f(x) ) / h;
}


// MSE
double loss(double w1, double w2, double b) {
    double total = 0;
    for(int i = 0; i < X.size(); i++) {
        double y_pred = ((X[i] * Z[i] * w1) + (pow(X[i] * Z[i], 2) * w2) + b);
        total += pow((y_pred - y[i]), 2);

    }
    return total / X.size();
}


int main() {

    double w1 = 0;
    double w2 = 0;
    double b = 0;
    double lr = 1e-2;
    double h = 1e-10;

    for(int epochs = 0; epochs < 2000; epochs++) {

        // GRADIENTES DESCENDENTES
        double grad_w1 = (loss(w1 + h, w2, b) - loss(w1, w2, b)) / h;
        double grad_w2 = (loss(w1, w2 + h, b) - loss(w1, w2, b)) / h;
        double grad_b = (loss(w1, w2, h + b) - loss(w1, w2, b)) / h;

        //ATUALIZAÇÃO DE PARÂMETROS 
        w1 -= lr * grad_w1;
        w2 -= lr * grad_w2;
        b -= lr * grad_b;

        system("clear");
        std::cout << "╔══════════════════════╗\n";
        std::cout << "   Época: " << epochs << "\n";
        std::cout << "   Peso 1 (w1): " << w1 << "\n";
        std::cout << "   Peso 2 (w2): " << w2 << "\n";
        std::cout << "   Bias (b): " << b << "\n";
        std::cout << "   Loss: " << loss(w1, w2, b) << "\n";
        std::cout << "╚══════════════════════╝\n";

        if(loss(w1, w2, b) < 1e-9) {
            std::cout << "Treinamento Finalizado!" << std::endl;
            break;
        }

    }


    // FASE DE TESTE

    std::cout << "Entrada | Saída Prevista\n";
    std::cout << "────────────────────────\n";

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            double y_pred = (pow(i * j, 2) * w2) + (i * j * w1) + b;
            std::cout << "x=" << i
                      << ", z=" << j
                      << "  →  y_pred = " << y_pred
                      << std::endl;
        }
    }

    std::cout << "────────────────────────\n";

    std::cout << "Sempre me esforcei para ser mais como eu - Marius Jabami" << std::endl;

}
