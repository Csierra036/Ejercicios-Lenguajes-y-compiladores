/*  
    Dado un número entero no negativo n, a) genere los coeficientes del polinomio (x+1)n, muestre el
    resultado del polinomio y b) muestre por pasos el cálculo para x dado, f(x) = (x+1)n ,según el
    polinomio generado. Implemente el algoritmo utilizando memoria dinámica.
*/
#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std; 

long long* generateCoefficients(int n) {
    if (n < 0){
        return nullptr;
    }

    long long* coefficients = new (nothrow) long long[n + 1]; 

    if (!coefficients) {
        return nullptr;
    }

    coefficients[0] = 1; // Coeficiente para x^0

    for (int k = 1; k <= n; ++k) {
        //C(n, k) = C(n, k-1) * (n - k + 1) / k
        coefficients[k] = coefficients[k - 1] * (n - k + 1) / k;
    }

    return coefficients;
}

void showPolynomial(const long long* coefficients, int n) {
    // Usa cout (resuelto por 'using namespace std;')
    cout << "\n Polinomio generado (x+1)^" << n << ":\n";

    for (int k = n; k >= 0; --k) {
        long long C = coefficients[k];

        if (k < n && C > 0) {
            cout << " + ";
        }

        if (C != 1 || k == 0) {
            cout << C;
        }

        if (k >= 1) {
            cout << "x";
        }

        if (k > 1) {
            cout << "^" << k;
        }
    }
    cout << "\n"; 
}


void evaluatePolinomyal(const long long* coefficients, int n, double x) {
    double result = 0.0;
    cout << "\n--- Calculo de f(x) para x = " << x << " (Paso a Paso) ---\n";

    for (int k = n; k >= 0; --k) {
        long long C = coefficients[k];
        
        double potencia_x = std::pow(x, k); 
        
        double term = C * potencia_x;

        // Mostrar paso del cálculo
        cout << "Termino x^" << k << ": (" << C << ") * (" << x << "^" << k << ") = " << term << "\n";

        result += term;
    }

    cout << "\nResultado final f(" << x << ") = " << result << "\n";
}


int main() {
    int n;
    double x_valor;
    long long* coeficientes = nullptr; 

    cout << "Ingrese el valor de n (entero no negativo, exponente): ";
    if (!(cin >> n) || n < 0) {
        cerr << "Error: El valor de n debe ser un entero no negativo.\n";
        return 1;
    }

    cout << "Ingrese el valor de x para la evaluacion: ";
    if (!(cin >> x_valor)) {
        cerr << "Error: Entrada de x no valida.\n";
        return 1;
    }

    coeficientes = generateCoefficients(n);
    if (coeficientes == nullptr) {
        cerr << "Error: Fallo la asignación de memoria dinamica.\n";
        return 1;
    }

    showPolynomial(coeficientes, n);
    evaluatePolinomyal(coeficientes, n, x_valor);

    // Liberación de Memoria Dinámica
    delete[] coeficientes;
    coeficientes = nullptr; 

    cout << "\nMemoria dinamica liberada exitosamente.\n";
    return 0;
}