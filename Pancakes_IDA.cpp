#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <stack>
using namespace std;

struct Estado {
    vector<int> orden;  // Orden actual de los pancakes
    int g;
    int h;
    string camino;

// Función que devuelve el número de pancakes que están en su lugar correcto
int calcular_heuristica(vector<int>& orden) {
    int n = orden.size();
    int h = n;
    for (int i = 0; i < n; i++) {
        if (orden[i] == i + 1) {
            h--;
        }
    }
    return h;
}

// Función que mueve los pancakes para obtener un nuevo estado
Estado mover_pancakes(Estado actual, int i, int j) {
    Estado siguiente = actual;
    reverse(siguiente.orden.begin() + i, siguiente.orden.begin() + j + 1);
    siguiente.h = calcular_heuristica(siguiente.orden);
    siguiente.g = actual.g + 1;
    siguiente.camino += to_string(i) + "-" + to_string(j) + " ";
    return siguiente;
}

// Función para realizar la búsqueda IDA*
bool ida_star(Estado actual, int limite, int& siguiente_limite) {
    if (actual.h == 0) {
        cout << actual.camino << endl;
        return true;
    }
    if (actual.g + actual.h > limite) {
        siguiente_limite = min(siguiente_limite, actual.g + actual.h);
        return false;
    }
    int n = actual.orden.size();
    bool encontrado = false;
    for (int i = 0; i < n && !encontrado; i++) {
        for (int j = i; j < n && !encontrado; j++) {
            if (i != j && i + j != n - 1) {
                Estado siguiente = mover_pancakes(actual, i, j);
                encontrado = ida_star(siguiente, limite, siguiente_limite);
            }
        }
    }
    return encontrado;
}

// Función principal para resolver el problema de los pancakes con IDA*
void jugar_pancakes_ida() {
    vector<int> orden_inicial = {5, 4, 1, 2, 3};
    Estado actual = {orden_inicial, 0, calcular_heuristica(orden_inicial), ""};
    int limite = actual.h;
    int siguiente_limite;
    while (true) {
        siguiente_limite = INT_MAX;
        bool encontrado = ida_star(actual, limite, siguiente_limite);
        if (encontrado) {
            return;
        }
        limite = siguiente_limite;
    }
}

// Función principal para ejecutar el programa
int main() {
    jugar_pancakes_ida();
    return 0;
}