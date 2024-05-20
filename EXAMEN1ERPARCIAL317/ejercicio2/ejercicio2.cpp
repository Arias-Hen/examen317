#include <iostream>

using namespace std;

// Función para sumar dos números
int sumar(int *a, int *b) {
    return (*a) + (*b);
}

// Función para restar dos números
int restar(int *a, int *b) {
    return (*a) - (*b);
}

// Función para multiplicar dos números utilizando sumas repetidas
int multiplicar(int *a, int *b) {
    int resultado = 0;
    for (int i = 0; i < (*b); i++) {
        resultado = sumar(&resultado, a);
    }
    return resultado;
}

// Función para dividir dos números utilizando restas repetidas
int dividir(int *a, int *b) {
    int cociente = 0;
    int dividendo = *a;
    int divisor = *b;

    while (dividendo >= divisor) {
        dividendo = restar(&dividendo, &divisor);
        cociente++;
    }

    return cociente;
}

int main() {
    int num1, num2;

    cout << "Ingrese el primer número: ";
    cin >> num1;

    cout << "Ingrese el segundo número: ";
    cin >> num2;

    cout << "Suma: " << sumar(&num1, &num2) << endl;
    cout << "Resta: " << restar(&num1, &num2) << endl;
    cout << "Multiplicación: " << multiplicar(&num1, &num2) << endl;
    cout << "División: " << dividir(&num1, &num2) << endl;

    return 0;
}
